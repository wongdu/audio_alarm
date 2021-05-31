#include <string>

#include <glog/logging.h>
#include "AudioAlarmServer.h"

using grpc::Server;
using grpc::ServerBuilder;

using namespace audio_alarm;
using audio_alarm::ThreadPool;

static constexpr size_t kMinMsgQueueSize = 100;
static constexpr size_t kMaxMsgQueueSize = 10000;

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
	LOG(INFO) <<"AudioAlarmServer::Start";
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
	AlarmMsg val;
	while (ptrMsgQueue->pop(val)) {

	}
}

void AudioAlarmServer::AddAlarmMsg(const AlarmMsg&& msg) {
	LOG(INFO) << "add alarm message id:" << msg.msgId;
	ptrMsgQueue->push(msg);

	ptrThreadPool->AddTask(std::bind(&AudioAlarmServer::ProcAlarmMsg, this));
}

void AudioAlarmServer::ProcAlarmMsg() {
	AlarmMsg alarmMsg;
	ptrMsgQueue->pop(alarmMsg);


}
