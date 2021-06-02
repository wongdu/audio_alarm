#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <string>
#include <future>
#include <atomic>
#include <fstream>
#include <vector>
#include <openssl/md5.h>

#include <glog/logging.h>

#include "AudioAlarmServer.h"

#include "teemo/teemo.h"

using grpc::Server;
using grpc::ServerBuilder;

using audio_alarm::ThreadPool;
using namespace audio_alarm;
using namespace teemo;

static constexpr size_t kMinMsgQueueSize = 100;
static constexpr size_t kMaxMsgQueueSize = 10000;
static constexpr size_t kDownloadPolicyValue = 1024000 * 5;


static constexpr int MaxDataBuff = 1024;
static constexpr int Md5Length = 16;
static constexpr int Md5HexResultLength = 64;

//static LockFreeQueueCpp11<AlarmMsg> queueMsg(1000);

AudioAlarmServer::AudioAlarmServer() {

}

AudioAlarmServer::~AudioAlarmServer() {

}

void AudioAlarmServer::Initialize(size_t maxMsgQueueSize, size_t thdPoolSize) {
	if (maxMsgQueueSize <= kMinMsgQueueSize) {
		maxMsgQueueSize = kMinMsgQueueSize;
	}

	if (maxMsgQueueSize >= kMaxMsgQueueSize) {
		maxMsgQueueSize = kMaxMsgQueueSize;
	}

	ptrMsgQueue = std::make_shared<LockFreeQueueCpp11<AlarmMsg>>(maxMsgQueueSize);

	ptrAlarmService = std::make_shared<AudioAlarmService>();

	std::string server_address("0.0.0.0:50051");
	ServerBuilder builder;
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(ptrAlarmService.get());

	std::unique_ptr<Server> ptrServer(builder.BuildAndStart());
	//ptrAlarmServer = std::move(std::make_unique<Server>());
	ptrAlarmServer = std::move(ptrServer);

	Teemo::GlobalInit();
	//ptrThreadPool = std::make_shared<ThreadPool>();
	ptrThreadPool = std::move(std::unique_ptr<ThreadPool>(new ThreadPool));
	ptrThreadPool->Start(thdPoolSize);
}

void AudioAlarmServer::RegisterService() {
	if (ptrAlarmService) {
		ptrAlarmService->Initialize(shared_from_this());
	}
}

void AudioAlarmServer::Start() {
	LOG(INFO) << "AudioAlarmServer::Start";
	if (ptrAlarmServer) {
		ptrAlarmServer->Wait();
	}
}

void AudioAlarmServer::Stop() {
	if (ptrAlarmServer) {
		ptrAlarmServer->Shutdown();
	}

	ptrThreadPool->Stop();

	//clear the alarm message queue
	AlarmMsg msg;
	while (ptrMsgQueue->pop(msg)) {

	}
}

void AudioAlarmServer::AddAlarmMsg(const AlarmMsg&& msg) {
	LOG(INFO) << "add alarm message id:" << msg.msgId;
	ptrMsgQueue->push(msg);

	std::string strDev = msg.devIp + "_" + std::to_string(msg.devPort);
	uint32 msgId = msg.msgId;

	InterruptMsg interMsg;
	interMsg.bValid = true;
	interMsg.playDuration = msg.playDuration;
	interMsg.timePoint = std::chrono::high_resolution_clock::now();

	{
		std::lock_guard<std::mutex> lk(mutexInter); //insert the current alarm message into map
		std::map<uint32, InterruptMsg> mapDev = mapInter[strDev];
		auto lastIter = mapDev.rbegin();
		if (lastIter != mapDev.rend()) {
			InterruptMsg lastMsg = lastIter->second;
			std::chrono::duration<double> diff = interMsg.timePoint - lastMsg.timePoint;
			if (diff.count() < lastMsg.playDuration) {
				lastIter->second.bValid = false;
			}
		}

		mapDev[msgId] = interMsg;
	}

	ptrThreadPool->AddTask(std::bind(&AudioAlarmServer::TaskAlarmMsg, this));
}

void AudioAlarmServer::TaskAlarmMsg() {
	AlarmMsg alarmMsg;
	ptrMsgQueue->pop(alarmMsg);

	uint32 msgId = alarmMsg.msgId;
	std::string strDev = alarmMsg.devIp + "_" + std::to_string(alarmMsg.devPort);

	{
		std::lock_guard<std::mutex> lk(mutexInter);
		std::map<uint32, InterruptMsg> mapDev = mapInter[strDev];
		InterruptMsg interMsg = mapDev[msgId];
		mapDev.erase(msgId);
		if (mapDev.size() == 0) {
			mapInter.erase(strDev);
		}
		if (!interMsg.bValid) {
			return;
		}
	}

	procAlarmMsg(std::move(alarmMsg));
}

void AudioAlarmServer::procAlarmMsg(const AlarmMsg&& msg) {

}

bool AudioAlarmServer::getAudioFile(const std::string& url, const std::string& name, const std::string& value) {
	if (url.empty() || name.empty() || value.empty()) {
		return false;
	}

	if (checkExists(name, value)) {
		return true;
	}

	if (!downloadFile(url, name)) {
		return false;
	}

	return value == getFileMd5sumValue(name);;
}

bool AudioAlarmServer::downloadFile(const std::string& url, const std::string& name) {
	Teemo efd;
	efd.setSlicePolicy(SlicePolicy::FixedSize, kDownloadPolicyValue);

	std::atomic_bool bResult;
	bResult = true;
	std::shared_future<Result> resFuture = efd.start(url, name,
		[&bResult](Result result) {
			//EXPECT_TRUE(result == SUCCESSED || result == CANCELED);
			if (result != SUCCESSED) {
				bResult = false;
			}
		},
		nullptr, nullptr);

	resFuture.wait();

	return bResult;
}

bool AudioAlarmServer::checkExists(const std::string& name, const std::string& value) {
	struct stat st;
	//return stat(_path.c_str(), &st) == 0;
	if (stat(name.c_str(), &st)) {
		return false;
	}

	return value == getFileMd5sumValue(name);
}

std::string AudioAlarmServer::getFileMd5sumValue(const std::string& strFilePath) {
	if (strFilePath.empty()) {
		return std::string("");
	}
	std::ifstream ifile(strFilePath.c_str(), std::ios::in | std::ios::binary);
	if (ifile.fail()) {
		return std::string("");
	}

	MD5_CTX md5_ctx;
	MD5_Init(&md5_ctx);
	char DataBuff[MaxDataBuff];
	unsigned char MD5result[Md5Length];
	while (!ifile.eof())
	{
		ifile.read(DataBuff, MaxDataBuff);   //read file content
		int length = ifile.gcount();
		if (length)
		{
			MD5_Update(&md5_ctx, DataBuff, length);
		}
	}
	MD5_Final(MD5result, &md5_ctx);  //got the MD5 value
	char resArr[Md5HexResultLength] = { 0 };
	int ilen = sizeof(MD5result) / sizeof(MD5result[0]);
	std::vector<char> buf(3);
	for (size_t i = 0; i < ilen; i++) {
		std::snprintf(&buf[0], buf.size(), "%02x", MD5result[i]);
		strcat_s(resArr, &buf[0]);
	}
	return std::string(resArr);
}
