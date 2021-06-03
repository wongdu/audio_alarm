#include <glog/logging.h>

#include "Common.h"
#include "AudioAlarmService.h"
#include "AudioAlarmServer.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using audioalarm::v1::AlarmService;
using audioalarm::v1::AlarmRequest;
using audioalarm::v1::AlarmReply;

//using namespace audio_alarm;

AudioAlarmService::AudioAlarmService() {

}

AudioAlarmService::~AudioAlarmService() {

}

void AudioAlarmService::Initialize(std::weak_ptr<AudioAlarmServer> alarmServer) {
	weakPtrAlarmServer = alarmServer;
}

::grpc::Status AudioAlarmService::SetAlarmMessage(::grpc::ServerContext* context,
	const ::audioalarm::v1::AlarmRequest* request, ::audioalarm::v1::AlarmReply* response) {
	audioalarm::v1::CameraType cameraType = request->camera_type();
	if (cameraType != audioalarm::v1::CameraType::DaHua && cameraType != audioalarm::v1::CameraType::HiK) {
		LOG(ERROR) << "the request camera type is invalid,unsupported type:" << cameraType;
		response->set_code(audioalarm::v1::Err_Camera_Unsupported);
		response->set_message("camera type is invalid");
		return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT, "");
	}

	AlarmMsg alarmMsg;
	alarmMsg.msgId = request->msg_id();
	alarmMsg.cameraType = static_cast<CameraType>(cameraType);
	alarmMsg.devIp = request->dev_ip();
	alarmMsg.devPort = request->dev_port();
	alarmMsg.playDuration = request->play_duration();
	alarmMsg.userName = request->user_name();
	alarmMsg.userPassword = request->user_password();
	alarmMsg.downloadUrl = request->download_url();
	alarmMsg.fileName = request->file_name();
	alarmMsg.md5Value = request->md5_value();

	if (alarmMsg.msgId == 0) {
		LOG(ERROR) << "messageId should not be zero";
		response->set_code(audioalarm::v1::Err_Message_Id_Not_Set);
		response->set_message("messageId should not be zero");
		return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT, "");
	}

	if (alarmMsg.devIp.empty() || alarmMsg.devPort == 0) {
		LOG(ERROR) << "camera information is incomplete, can not find the device";
		response->set_code(audioalarm::v1::Err_Device_Not_Found);
		response->set_message("camera information is incomplete,can not find the device");
		return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT, "");
	}

	if (alarmMsg.userName.empty() || alarmMsg.userPassword.empty()) {
		LOG(ERROR) << "user information is incomplete";
		response->set_code(audioalarm::v1::Err_Device_Login_Incomplete);
		response->set_message("user information is incomplete");
		return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT, "");
	}

	if (alarmMsg.downloadUrl.empty() || alarmMsg.fileName.empty() || alarmMsg.md5Value.empty()) {
		LOG(ERROR) << "audio file information is incomplete";
		response->set_code(audioalarm::v1::Err_Audio_File_Incomplete);
		response->set_message("audio file information is incomplete");
		return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT, "");
	}

	if (alarmMsg.playDuration == 0) {
		LOG(ERROR) << "play duration should not be zero";
		response->set_code(audioalarm::v1::Err_Play_Duration_Not_Set);
		response->set_message("play duration should not be zero");
		return ::grpc::Status(::grpc::StatusCode::INVALID_ARGUMENT, "");
	}

	if (auto spt = weakPtrAlarmServer.lock()) {
		spt->AddAlarmMsg(std::move(alarmMsg));
	}

	return Status::OK;
}
