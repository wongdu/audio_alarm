// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: alarm.proto

#include "alarm.pb.h"
#include "alarm.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace audioalarm {
namespace v1 {

static const char* AlarmService_method_names[] = {
  "/audioalarm.v1.AlarmService/SetAlarmMessage",
};

std::unique_ptr< AlarmService::Stub> AlarmService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< AlarmService::Stub> stub(new AlarmService::Stub(channel, options));
  return stub;
}

AlarmService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_SetAlarmMessage_(AlarmService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status AlarmService::Stub::SetAlarmMessage(::grpc::ClientContext* context, const ::audioalarm::v1::AlarmRequest& request, ::audioalarm::v1::AlarmReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::audioalarm::v1::AlarmRequest, ::audioalarm::v1::AlarmReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_SetAlarmMessage_, context, request, response);
}

void AlarmService::Stub::experimental_async::SetAlarmMessage(::grpc::ClientContext* context, const ::audioalarm::v1::AlarmRequest* request, ::audioalarm::v1::AlarmReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::audioalarm::v1::AlarmRequest, ::audioalarm::v1::AlarmReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SetAlarmMessage_, context, request, response, std::move(f));
}

void AlarmService::Stub::experimental_async::SetAlarmMessage(::grpc::ClientContext* context, const ::audioalarm::v1::AlarmRequest* request, ::audioalarm::v1::AlarmReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SetAlarmMessage_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::audioalarm::v1::AlarmReply>* AlarmService::Stub::PrepareAsyncSetAlarmMessageRaw(::grpc::ClientContext* context, const ::audioalarm::v1::AlarmRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::audioalarm::v1::AlarmReply, ::audioalarm::v1::AlarmRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_SetAlarmMessage_, context, request);
}

::grpc::ClientAsyncResponseReader< ::audioalarm::v1::AlarmReply>* AlarmService::Stub::AsyncSetAlarmMessageRaw(::grpc::ClientContext* context, const ::audioalarm::v1::AlarmRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncSetAlarmMessageRaw(context, request, cq);
  result->StartCall();
  return result;
}

AlarmService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      AlarmService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< AlarmService::Service, ::audioalarm::v1::AlarmRequest, ::audioalarm::v1::AlarmReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](AlarmService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::audioalarm::v1::AlarmRequest* req,
             ::audioalarm::v1::AlarmReply* resp) {
               return service->SetAlarmMessage(ctx, req, resp);
             }, this)));
}

AlarmService::Service::~Service() {
}

::grpc::Status AlarmService::Service::SetAlarmMessage(::grpc::ServerContext* context, const ::audioalarm::v1::AlarmRequest* request, ::audioalarm::v1::AlarmReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace audioalarm
}  // namespace v1
