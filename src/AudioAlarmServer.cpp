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

#include "HCNetSDK.h"

#include "AudioAlarmServer.h"
#include "CameraDh.h"
#include "CameraHik.h"

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
static constexpr int PcmDataBufferLength = 4;

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

	//hikNetSdk initialize
	NET_DVR_Init();

	//dahuaNetSdk initialize

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

	//hikNetSdk unInitialize
	NET_DVR_Cleanup();

	//dahuaNetSdk unInitialize

}

void AudioAlarmServer::ClearCameraMsg(const std::string& devIp, const std::string& devPort) {

}

void AudioAlarmServer::AddAlarmMsg(const AlarmMsg&& msg) {
	LOG(INFO) << "add alarm message id:" << msg.msgId;
	ptrMsgQueue->push(msg);

	std::string strDev = msg.devIp + "_" + std::to_string(msg.devPort);
	uint32 msgId = msg.msgId;

	{
		std::lock_guard<std::mutex> lk(mutexAlarming);
		uint32 processingId = mapAlarmingMsgId[strDev];
		if (processingId) {
			//the current device is processing old alarm message
			LatestMsgResult msgResult = procLatestAlarmMsg(std::move(msg));
			if (LatestMsgResult::DownLoadOnly != msgResult) {
				return;
			}
		}
		else {
			mapAlarmingMsgId.erase(strDev);
		}
	}

	LOG(INFO) << "add alarm message into the thread poll,message id:" << msg.msgId;
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

	LOG(INFO) << "one thread pool work start,message id:" << alarmMsg.msgId;
	uint32 msgId = alarmMsg.msgId;
	std::string strDev = alarmMsg.devIp + "_" + std::to_string(alarmMsg.devPort);

	{
		std::lock_guard<std::mutex> lk(mutexInter);
		std::map<uint32, InterruptMsg> mapDev = mapInter[strDev];
		if (mapDev.size() == 0) {
			mapInter.erase(strDev);
			procAlarmMsg(std::move(alarmMsg));
			return;
		}
		InterruptMsg interMsg = mapDev[msgId];
		mapDev.erase(msgId);
		if (mapDev.size() == 0) {
			mapInter.erase(strDev);
		}
		if (interMsg.playDuration && !interMsg.bValid) {
			return;
		}
	}

	procAlarmMsg(std::move(alarmMsg));
}

void AudioAlarmServer::procAlarmMsg(const AlarmMsg&& msg) {
	if (!getAudioFile(msg.downloadUrl, msg.fileName, msg.md5Value)) {
		LOG(ERROR) << "download the audio file failed,message id:" << msg.msgId << ",url:" << msg.downloadUrl;
		return;
	}

	if (!pcmRateDownSample(msg.fileName, msg.md5Value)) {
		LOG(ERROR) << "down sample failed,message id:" << msg.msgId << ",url:" << msg.downloadUrl;
		return;
	}

	LOG(INFO) << "get audio file successful,message id:" << msg.msgId << ",camera type:" << (CameraType::DaHua == msg.cameraType ? "daHua" : "hiK");
	std::shared_ptr<CameraSdk> ptrCamera;
	if (CameraType::DaHua == msg.cameraType) {
		ptrCamera.reset(new CameraDh);
	}
	else {
		ptrCamera.reset(new CameraHik);
	}

	std::string strDev = msg.devIp + "_" + std::to_string(msg.devPort);
	{
		std::lock_guard<std::mutex> lk(mutexAlarming);
		mapAlarmingMsgId[strDev] = msg.msgId;
		mapAlarmingCameraSdk[msg.msgId] = ptrCamera;
	}

	if (!ptrCamera->LoginDvr(msg.devIp, msg.devPort, msg.userName, msg.userPassword)) {
		LOG(ERROR) << "login the camera failed";
		std::lock_guard<std::mutex> lk(mutexAlarming);
		mapAlarmingMsgId.erase(strDev);
		mapAlarmingCameraSdk.erase(msg.msgId);
		return;
	}

	LOG(INFO) << "set the audio file name:" << msg.fileName << ",play duration:" << msg.playDuration;
	std::string strOutputPcmName = msg.fileName.substr(0, msg.fileName.find_last_of("."));
	strOutputPcmName = strOutputPcmName + "_" + msg.md5Value + ".pcm";
	ptrCamera->SetAudioFileName(strOutputPcmName, msg.playDuration);

	ptrCamera->StartAlarm();
	ptrCamera->LogoutDvr();

	std::lock_guard<std::mutex> lk(mutexAlarming);
	mapAlarmingMsgId.erase(strDev);
	mapAlarmingCameraSdk.erase(msg.msgId);
}

bool AudioAlarmServer::getAudioFile(const std::string& url, const std::string& name, const std::string& value) {
	if (url.empty() || name.empty() || value.empty()) {
		LOG(ERROR) << "download the audio file information is incomplete,url:" << url << ",file name:" << name << ",md5Value:" << value;
		return false;
	}

	if (checkExists(name, value)) {
		LOG(INFO) << "the audio file is already exists";
		return true;
	}

	if (!downloadFile(url, name)) {
		LOG(ERROR) << "download failed";
		return false;
	}
	std::string strMd5Value = getFileMd5sumValue(name);
	LOG(INFO) << "start check the md5Value:" << value << ",current value:" << strMd5Value;

	return value == strMd5Value;
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
	ifile.close();

	MD5_Final(MD5result, &md5_ctx);  //got the MD5 value
	char resArr[Md5HexResultLength] = { 0 };
	int ilen = sizeof(MD5result) / sizeof(MD5result[0]);
	std::vector<char> buf(3);
	for (size_t i = 0; i < ilen; i++) {
		std::snprintf(&buf[0], buf.size(), "%02x", MD5result[i]);
		strcat(resArr, &buf[0]);
	}
	return std::string(resArr);
}

LatestMsgResult AudioAlarmServer::procLatestAlarmMsg(const AlarmMsg&& msg) {
	LOG(INFO) << "process the latest alarm message,message id:" << msg.msgId;

	if (!getAudioFile(msg.downloadUrl, msg.fileName, msg.md5Value)) {
		LOG(ERROR) << "download failed when process the latest alarm message,message id:" << msg.msgId << ",url:" << msg.downloadUrl;
		return LatestMsgResult::DownLoadFailed;
	}

	if (!pcmRateDownSample(msg.fileName, msg.md5Value)) {
		LOG(ERROR) << "down sample failed when process the latest alarm message,message id:" << msg.msgId << ",url:" << msg.downloadUrl;
		return LatestMsgResult::DownSampleFailed;
	}

	std::string strDev = msg.devIp + "_" + std::to_string(msg.devPort);
	{
		std::lock_guard<std::mutex> lk(mutexAlarming);

		uint32 id = mapAlarmingMsgId[strDev];
		if (id) {
			std::shared_ptr<CameraSdk> ptrCamera = mapAlarmingCameraSdk[id];
			std::string strOutputPcmName = msg.fileName.substr(0, msg.fileName.find_last_of("."));
			strOutputPcmName = strOutputPcmName + "_" + msg.md5Value + ".pcm";
			ptrCamera->UpdateAlarmInfo(strOutputPcmName, msg.playDuration);
			return LatestMsgResult::Processed;
		}
		else {
			mapAlarmingMsgId.erase(strDev);
			LOG(INFO) << "just download sussessfully";
		}

		return LatestMsgResult::DownLoadOnly;
	}
}

bool AudioAlarmServer::pcmRateDownSample(const std::string& name, const std::string& value) {
	std::string strOutputPcmName = name.substr(0, name.find_last_of("."));
	strOutputPcmName = strOutputPcmName + "_" + value + ".pcm";

	std::string strSuffix = name.substr(name.find_last_of(".") + 1);
	if ("wav" != strSuffix) {
		LOG(ERROR) << name << " is not supported,just support wav file format";
		return true;
	}

	struct stat st;
	if (!stat(strOutputPcmName.c_str(), &st)) {
		LOG(ERROR) << "the pcm file alread exists";
		return true;
	}

	std::ifstream ifile(name.c_str(), std::ios::in | std::ios::binary);
	if (ifile.fail() || !ifile.is_open()) {
		LOG(ERROR) << "open the source audio file failed when down sample pcm file";
		return false;
	}

	std::ofstream outputFile(strOutputPcmName.c_str(), std::ios::binary);
	if (!outputFile.is_open()) {
		LOG(ERROR) << "open the destination audio file failed when down sample pcm file";
		return false;
	}

	char pcmDataBuff[PcmDataBufferLength];
	int halfPcmDataBuffLen = PcmDataBufferLength / 2;
	while (!ifile.eof()) {
		ifile.read(pcmDataBuff, PcmDataBufferLength);
		for (int idx = 0; idx < halfPcmDataBuffLen; idx++) {
			pcmDataBuff[idx] = pcmDataBuff[idx] / 2 + pcmDataBuff[idx + halfPcmDataBuffLen] / 2;
		}

		outputFile.write(pcmDataBuff, PcmDataBufferLength / 2);
	}

	outputFile.flush();
	ifile.close();
	outputFile.close();

	return true;
}
