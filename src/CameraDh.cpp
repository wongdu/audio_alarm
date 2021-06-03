#include "CameraDh.h"

CameraDh::CameraDh() :lLoginID(-1), lVoiceHanle(-1) {

}

CameraDh::~CameraDh() {

}

bool CameraDh::LoginDvr(const std::string& ip, const uint32 port, const std::string& name, const std::string& password) {

}

void CameraDh::LogoutDvr() {

}

void CameraDh::SetAudioFileName(const std::string& fileName, uint32 duration) {

}

void CameraDh::UpdateAlarmInfo(const std::string& fileName, uint32 duration) {

}

void CameraDh::StartAlarm() {

}

std::string CameraDh::GetDevInfo() {
	return devIp + "_" + std::to_string(devPort);
}
