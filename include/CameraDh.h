#ifndef __Camera_Dh_H__
#define __Camera_Dh_H__

#include "CameraSdk.h"

class CameraDh : public CameraSdk {
public:
	CameraDh();
	virtual ~CameraDh();

public:
	virtual void InitNetsdk() override;
	virtual void SetAudioFileName(const std::string fileName) override;
	virtual void UpdateAlarmInfo(const std::string fileName, uint32 duration) override;
	virtual void StartAlarm() override;

private:

private:

};

#endif
