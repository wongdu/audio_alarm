#ifndef __Camera_Hik_H__
#define __Camera_Hik_H__

#include "CameraSdk.h"

class CameraHik : public CameraSdk {
public:
	CameraHik();
	virtual ~CameraHik();
	
public:
	virtual void InitNetsdk() override;
	virtual void SetAudioFileName(const std::string fileName) override;
	virtual void UpdateAlarmInfo(const std::string fileName, uint32 duration) override;
	virtual void StartAlarm() override;

private:

private:


};

#endif
