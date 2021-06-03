#ifndef __Camera_Hik_H__
#define __Camera_Hik_H__

#include "CameraSdk.h"
#include "HCNetSDK.h"

class CameraHik : public CameraSdk {
public:
	CameraHik();
	virtual ~CameraHik();

public:
	virtual bool LoginDvr(const std::string& ip, const uint32 port, const std::string& name, const std::string& password) override;
	virtual void LogoutDvr() override;
	virtual void SetAudioFileName(const std::string& fileName, uint32 duration) override;
	virtual void UpdateAlarmInfo(const std::string& fileName, uint32 duration) override;
	virtual void StartAlarm() override;
	virtual std::string GetDevInfo() override;

private:
	void sendAudioAlarmData();

private:
	//long lLoginID;

	void* m_pEncoder;//g722 encoder

};

#endif
