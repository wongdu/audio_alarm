#ifndef __Audio_Alarm_Service_H__
#define __Audio_Alarm_Service_H__

#include <memory>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include "alarm.grpc.pb.h"

class AudioAlarmServer;

class AudioAlarmService final : public audioalarm::v1::AlarmService::Service {
public:
	AudioAlarmService();
	virtual ~AudioAlarmService();

public:
	void Initialize(std::weak_ptr<AudioAlarmServer> alarmServer);

public:
	virtual ::grpc::Status SetAlarmMessage(::grpc::ServerContext* context,
		const ::audioalarm::v1::AlarmRequest* request, ::audioalarm::v1::AlarmReply* response);

private:
	std::weak_ptr<AudioAlarmServer> weakPtrAlarmServer;
};

#endif
