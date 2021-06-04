#include <cassert>
#include <thread>
#include <chrono>

#include <glog/logging.h>

#include "CameraHik.h"

void CALLBACK  fDVRVoiceDataCallBack(LONG  lVoiceComHandle, char* pRecvDataBuffer, DWORD  dwBufSize, BYTE  byAudioFlag, void* pUser);

CameraHik::CameraHik() {
	lLoginID = -1;
	lVoiceHanle = -1;
	m_pG711Enc = nullptr;
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
		LOG(ERROR) << "the camera login failed,error code:" << NET_DVR_GetLastError() << ",message:" << NET_DVR_GetErrorMsg();
		return false;
	}

	NET_DVR_AUDIOENC_INFO struEncInfo711 = { 0 };
	m_pG711Enc = NET_DVR_InitG711Encoder(&struEncInfo711);
	if ((long)m_pG711Enc == -1) {
		LOG(ERROR) << "initialize audio encoder failed:" << NET_DVR_GetLastError() << ",message:" << NET_DVR_GetErrorMsg();
		return false;	
	}

	return true;
}

void CameraHik::LogoutDvr() {
	if (lVoiceHanle>=0) {
		NET_DVR_StopVoiceCom(lVoiceHanle);
	}
	if (m_pG711Enc) {
		NET_DVR_ReleaseG711Encoder(m_pG711Enc);
		m_pG711Enc = nullptr;
	}
	NET_DVR_Logout(lLoginID);
}

void CameraHik::SetAudioFileName(const std::string& fileName, uint32 duration) {
	strAudioFileName = fileName;
	playDuration = duration;
}

void CameraHik::UpdateAlarmInfo(const std::string& fileName, uint32 duration) {	
	{
		std::lock_guard<std::mutex> lk(mutexAudioFile);
		strAudioFileName = fileName;
		playDuration = duration;

		if (audioFile.is_open()) {
			LOG(INFO) << "update the audio file name:" << fileName <<" failed";
			audioFile.close();
		}

		std::ifstream file(strAudioFileName, std::ios::binary);
		audioFile = std::move(file);
	}
	//todo

}

void CameraHik::StartAlarm() {
	assert(lVoiceHanle<0);
	assert(lLoginID >=0);

	lVoiceHanle = NET_DVR_StartVoiceCom_MR_V30(lLoginID,1, fDVRVoiceDataCallBack,(void*)this);
	if (lVoiceHanle == -1) {
		LOG(ERROR) << "start voice communication failed,error code:"<< NET_DVR_GetLastError()<<",message:"<< NET_DVR_GetErrorMsg();
		return;
	}

	sendAudioAlarmData();
}

std::string CameraHik::GetDevInfo() {
	return devIp + "_" + std::to_string(devPort);
}

void CameraHik::sendAudioAlarmData() {	
	{
		std::lock_guard<std::mutex> lk(mutexAudioFile);
		if (audioFile.is_open()) {
			audioFile.close();
		}

		std::ifstream file(strAudioFileName, std::ios::binary);
		audioFile = std::move(file);
	}

	if (!audioFile.is_open()) {
		LOG(INFO) << "open the audio file name:" << strAudioFileName << " failed when start send file content";
		return;
	}

	timePointStart= std::chrono::high_resolution_clock::now();
	while (true)
	{
		timePointCurrent = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = timePointCurrent - timePointStart;
		if (diff.count() >= playDuration) {
			break;		
		}
		memset(G711EncBufA, 0, G711_AUDDECSIZE);

		{
			std::lock_guard<std::mutex> lk(mutexAudioFile);
			if (audioFile.eof())
			{
				audioFile.clear();
				audioFile.seekg(0, std::ios::beg);
			}
			
			memset(fileContentBuff, 0, G711_AUDDECSIZE);
			audioFile.read(fileContentBuff, G711_AUDDECSIZE);
		}
				
		//NET_DVR_EncodeG711Frame(1, (BYTE*)fileContentBuff, G711EncBufA);

		NET_DVR_AUDIOENC_PROCESS_PARAM struEncProcParam = { 0 };
		struEncProcParam.g711_type = 1;
		struEncProcParam.in_buf = (BYTE*)fileContentBuff;
		struEncProcParam.out_buf = G711EncBufA;

		NET_DVR_EncodeG711Frame(m_pG711Enc, &struEncProcParam);

		if (!NET_DVR_VoiceComSendData(lVoiceHanle, (char*)G711EncBufA, G711_AUDDECSIZE/2)) {
			LOG(ERROR) << "start voice communication failed,error code:" << NET_DVR_GetLastError() << ",message:" << NET_DVR_GetErrorMsg();
			continue;		
		}
		//std::this_thread::sleep_for(20ms);
		//std::this_thread::sleep_for(std::chrono::microseconds(20));
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	LOG(INFO) << "send audio alarm data complete";
}

void CALLBACK  fDVRVoiceDataCallBack(LONG  lVoiceComHandle, char* pRecvDataBuffer, DWORD  dwBufSize, BYTE  byAudioFlag, void* pUser)
{
	assert(pRecvDataBuffer);	
	switch (byAudioFlag)
	{
	case 0:
		LOG(INFO) << "local audio data" ;
		break;
	case 1:
		LOG(INFO) << "Input data size:"<< dwBufSize;
		break;
	case 2:
		LOG(INFO) << "audio sending and receiving thread exit";
		break;
	default:
		break;
	}
}
