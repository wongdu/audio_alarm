#ifndef __Camera_Sdk_H__
#define __Camera_Sdk_H__

#include <string>

using uint32 = unsigned int;

class CameraSdk {
public:
	CameraSdk();
	virtual ~CameraSdk();

public:
	virtual void InitNetsdk() = 0;
	virtual void SetAudioFileName(const std::string fileName) = 0;
	virtual void UpdateAlarmInfo(const std::string fileName, uint32 duration) = 0;
	virtual void StartAlarm() = 0;

protected:
	std::string devIp;
	uint32 devPort;
	std::string userName;
	std::string password;
	std::string strAudioFileName;
	uint32 playDuration;

private:

};

#endif
