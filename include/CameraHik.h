#ifndef __Camera_Hik_H__
#define __Camera_Hik_H__

#include <chrono>
#include <mutex>
#include <fstream>
//#include <memory>

#include "CameraSdk.h"
#include "HCNetSDK.h"

class CameraHik : public CameraSdk {
public:
	CameraHik();
	virtual ~CameraHik();

public:
	virtual bool LoginDvr(const std::string& ip, const uint32 port, const std::string& name, const std::string& password) override;
	virtual void LogoutDvr() override;
	virtual void SetAudioFileName(const std::string& fileName, PlayTimeType type, uint32 size) override;
	virtual void UpdateAlarmInfo(const std::string& fileName, PlayTimeType type, uint32 size) override;
	virtual void StartAlarm() override;
	virtual std::string GetDevInfo() override;

private:
	void sendAudioAlarmData();

private:
	static constexpr uint32 G711_AUDDECSIZE = 320;
	//long lLoginID;

	//void* m_pEncoder;//g722 encoder
	void* m_pG711Enc;
	std::mutex mutexAudioFile;
	//std::unique_ptr<std::ifstream> ptrAudioFile;
	std::ifstream audioFile;

	BYTE G711EncBufA[G711_AUDDECSIZE];
	char fileContentBuff[G711_AUDDECSIZE];
	std::chrono::time_point<std::chrono::high_resolution_clock> timePointStart;
	std::chrono::time_point<std::chrono::high_resolution_clock> timePointCurrent;
};

#endif
