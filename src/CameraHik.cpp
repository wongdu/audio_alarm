#include <glog/logging.h>

#include "CameraHik.h"

CameraHik::CameraHik() :lLoginID(-1), lVoiceHanle(-1) {

}

CameraHik::~CameraHik() {

}

bool CameraHik::LoginDvr(const std::string& ip, const uint32 port, const std::string& name, const std::string& password) {
	devIp = ip;
	devPort = port;
	userName = name;
	usrPassword = password;

	//login
	NET_DVR_USER_LOGIN_INFO struLoginInfo = { 0 };
	NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = { 0 };
	struLoginInfo.bUseAsynLogin = false;

	struLoginInfo.wPort = port;
	memcpy(struLoginInfo.sDeviceAddress, ip.c_str(), NET_DVR_DEV_ADDRESS_MAX_LEN);
	memcpy(struLoginInfo.sUserName, name.c_str(), NAME_LEN);
	memcpy(struLoginInfo.sPassword, password.c_str(), NAME_LEN);

	lLoginID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
	if (lLoginID < 0) {
		LOG(ERROR) << "the camera login failed";
		return false;
	}

	return true;
}

void CameraHik::LogoutDvr() {
	if (lVoiceHanle>=0) {
		NET_DVR_StopVoiceCom(lVoiceHanle);
	}
	
	NET_DVR_Logout(lLoginID);
}

void CameraHik::SetAudioFileName(const std::string& fileName, uint32 duration) {
	strAudioFileName = fileName;
	playDuration = duration;
}

void CameraHik::UpdateAlarmInfo(const std::string& fileName, uint32 duration) {
	strAudioFileName = fileName;
	playDuration = duration;
	//todo

}

void CameraHik::StartAlarm() {
	assert(lVoiceHanle<0);
	assert(lLoginID >=0);

	lVoiceHanle = NET_DVR_StartVoiceCom_MR_V30(lLoginID,, (void*)this);

}

std::string CameraHik::GetDevInfo() {
	return devIp + "_" + std::to_string(devPort);
}

void CameraHik::sendAudioAlarmData() {

}
