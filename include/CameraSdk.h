#ifndef __Camera_Sdk_H__
#define __Camera_Sdk_H__

#include <string>

#include "Common.h"

using uint32 = unsigned int;

class CameraSdk {
public:
	CameraSdk();
	virtual ~CameraSdk();

public:
	virtual bool LoginDvr(const std::string& ip, const uint32 port, const std::string& name, const std::string& password) = 0;
	virtual void LogoutDvr() = 0;
	virtual void SetAudioFileName(const std::string& fileName, PlayTimeType type, uint32 size) = 0;
	virtual void UpdateAlarmInfo(const std::string& fileName, PlayTimeType type, uint32 size) = 0;
	virtual void StartAlarm() = 0;
	virtual std::string GetDevInfo() = 0;

protected:
	long lLoginID;
	long lVoiceHanle;

	std::string devIp;
	uint32 devPort;
	std::string userName;
	std::string usrPassword;

	std::string strAudioFileName;

	PlayTimeType playTimeType;
	uint32 playTime;
	uint32 playedTime;

private:

};

#endif
