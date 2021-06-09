#ifndef __Camera_Dh_H__
#define __Camera_Dh_H__

#include "CameraSdk.h"

class CameraDh : public CameraSdk {
public:
	CameraDh();
	virtual ~CameraDh();

public:
	virtual bool LoginDvr(const std::string& ip, const uint32 port, const std::string& name, const std::string& password) override;
	virtual void LogoutDvr() override;
	virtual void SetAudioFileName(const std::string& fileName, PlayTimeType type, uint32 size) override;
	virtual void UpdateAlarmInfo(const std::string& fileName, PlayTimeType type, uint32 size) override;
	virtual void StartAlarm() override;
	virtual std::string GetDevInfo() override;

private:

private:

};

#endif
