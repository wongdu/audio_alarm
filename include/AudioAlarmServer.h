#ifndef __Audio_Alarm_Server_H__
#define __Audio_Alarm_Server_H__

#include <memory>

#include "AudioAlarmService.h"
#include "Common.h"
#include "LockFreeQueueCpp11.h"
#include "ThreadPool.h"

class AudioAlarmServer : public std::enable_shared_from_this<AudioAlarmServer> {
public:
	AudioAlarmServer();
	virtual ~AudioAlarmServer();

public:
	void Initialize(size_t maxMsgQueueSize, size_t thdPoolSize = 4);
	void Start();
	void Stop();

public:
	void AddAlarmMsg(const AlarmMsg&& msg);
	void ProcAlarmMsg();

private:
	std::shared_ptr<AudioAlarmService> ptrAlarmService;
	std::unique_ptr<grpc::Server> ptrAlarmServer;

	std::shared_ptr<audio_alarm::LockFreeQueueCpp11<AlarmMsg>> ptrMsgQueue;
	std::unique_ptr<audio_alarm::ThreadPool> ptrThreadPool;
};

#endif
