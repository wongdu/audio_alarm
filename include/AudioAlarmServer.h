#ifndef __Audio_Alarm_Server_H__
#define __Audio_Alarm_Server_H__

#include <map>
#include <string>
#include <mutex>
#include <memory>
#include <chrono>

#include "AudioAlarmService.h"
#include "Common.h"
#include "LockFreeQueueCpp11.h"
#include "ThreadPool.h"
#include "CameraSdk.h"

class AudioAlarmServer : public std::enable_shared_from_this<AudioAlarmServer> {
public:
	AudioAlarmServer();
	virtual ~AudioAlarmServer();

public:
	void Initialize(size_t maxMsgQueueSize, size_t thdPoolSize = 4);
	void RegisterService();
	void Start();
	void Stop();

public:
	void ClearCameraMsg(const std::string& devIp, const std::string& devPort); // new camera information,clear the old alarm message

public:
	void AddAlarmMsg(const AlarmMsg&& msg);
	void TaskAlarmMsg();

private:
	void procAlarmMsg(const AlarmMsg&& msg);
	bool getAudioFile(const std::string& url, const std::string& name, const std::string& value);
	bool downloadFile(const std::string& url, const std::string& name);
	bool checkExists(const std::string& name, const std::string& value);
	std::string getFileMd5sumValue(const std::string& strFilePath);
	LatestMsgResult procLatestAlarmMsg(const AlarmMsg&& msg);
	bool pcmRateDownSample(const std::string& name, const std::string& value);

private:
	struct InterruptMsg {
		bool bValid;
		uint32 flagTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> timePoint;

		InterruptMsg() {
			bValid = false;
			flagTime = 0;
			timePoint = std::chrono::high_resolution_clock::now();
		}
	};

private:

	std::shared_ptr<AudioAlarmService> ptrAlarmService;
	std::unique_ptr<grpc::Server> ptrAlarmServer;

	std::shared_ptr<audio_alarm::LockFreeQueueCpp11<AlarmMsg>> ptrMsgQueue;
	std::unique_ptr<audio_alarm::ThreadPool> ptrThreadPool;

	std::mutex mutexGetAudioFile;

	std::mutex mutexInter;
	std::map<std::string, std::map<uint32, InterruptMsg>> mapInter;

	std::mutex mutexAlarming;
	std::map<uint32, std::shared_ptr<CameraSdk>> mapAlarmingCameraSdk;
	std::map<std::string, uint32> mapAlarmingMsgId;

};

#endif
