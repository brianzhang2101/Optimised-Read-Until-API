// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: minknow_api/data.proto

#include "minknow_api/data.pb.h"
#include "minknow_api/data.grpc.pb.h"

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
namespace minknow_api {
namespace data {

static const char* DataService_method_names[] = {
  "/minknow_api.data.DataService/get_channel_states",
  "/minknow_api.data.DataService/get_data_types",
  "/minknow_api.data.DataService/get_signal_bytes",
  "/minknow_api.data.DataService/get_signal_min_max",
  "/minknow_api.data.DataService/reset_channel_states",
  "/minknow_api.data.DataService/lock_channel_states",
  "/minknow_api.data.DataService/unlock_channel_states",
  "/minknow_api.data.DataService/get_live_reads",
  "/minknow_api.data.DataService/get_read_statistics",
  "/minknow_api.data.DataService/get_experiment_yield_info",
};

std::unique_ptr< DataService::Stub> DataService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< DataService::Stub> stub(new DataService::Stub(channel, options));
  return stub;
}

DataService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_get_channel_states_(DataService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  , rpcmethod_get_data_types_(DataService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_get_signal_bytes_(DataService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  , rpcmethod_get_signal_min_max_(DataService_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  , rpcmethod_reset_channel_states_(DataService_method_names[4], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_lock_channel_states_(DataService_method_names[5], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_unlock_channel_states_(DataService_method_names[6], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_get_live_reads_(DataService_method_names[7], options.suffix_for_stats(),::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  , rpcmethod_get_read_statistics_(DataService_method_names[8], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_get_experiment_yield_info_(DataService_method_names[9], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::ClientReader< ::minknow_api::data::GetChannelStatesResponse>* DataService::Stub::get_channel_statesRaw(::grpc::ClientContext* context, const ::minknow_api::data::GetChannelStatesRequest& request) {
  return ::grpc::internal::ClientReaderFactory< ::minknow_api::data::GetChannelStatesResponse>::Create(channel_.get(), rpcmethod_get_channel_states_, context, request);
}

void DataService::Stub::async::get_channel_states(::grpc::ClientContext* context, const ::minknow_api::data::GetChannelStatesRequest* request, ::grpc::ClientReadReactor< ::minknow_api::data::GetChannelStatesResponse>* reactor) {
  ::grpc::internal::ClientCallbackReaderFactory< ::minknow_api::data::GetChannelStatesResponse>::Create(stub_->channel_.get(), stub_->rpcmethod_get_channel_states_, context, request, reactor);
}

::grpc::ClientAsyncReader< ::minknow_api::data::GetChannelStatesResponse>* DataService::Stub::Asyncget_channel_statesRaw(::grpc::ClientContext* context, const ::minknow_api::data::GetChannelStatesRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::minknow_api::data::GetChannelStatesResponse>::Create(channel_.get(), cq, rpcmethod_get_channel_states_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::minknow_api::data::GetChannelStatesResponse>* DataService::Stub::PrepareAsyncget_channel_statesRaw(::grpc::ClientContext* context, const ::minknow_api::data::GetChannelStatesRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::minknow_api::data::GetChannelStatesResponse>::Create(channel_.get(), cq, rpcmethod_get_channel_states_, context, request, false, nullptr);
}

::grpc::Status DataService::Stub::get_data_types(::grpc::ClientContext* context, const ::minknow_api::data::GetDataTypesRequest& request, ::minknow_api::data::GetDataTypesResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::minknow_api::data::GetDataTypesRequest, ::minknow_api::data::GetDataTypesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_get_data_types_, context, request, response);
}

void DataService::Stub::async::get_data_types(::grpc::ClientContext* context, const ::minknow_api::data::GetDataTypesRequest* request, ::minknow_api::data::GetDataTypesResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::minknow_api::data::GetDataTypesRequest, ::minknow_api::data::GetDataTypesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_get_data_types_, context, request, response, std::move(f));
}

void DataService::Stub::async::get_data_types(::grpc::ClientContext* context, const ::minknow_api::data::GetDataTypesRequest* request, ::minknow_api::data::GetDataTypesResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_get_data_types_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::minknow_api::data::GetDataTypesResponse>* DataService::Stub::PrepareAsyncget_data_typesRaw(::grpc::ClientContext* context, const ::minknow_api::data::GetDataTypesRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::minknow_api::data::GetDataTypesResponse, ::minknow_api::data::GetDataTypesRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_get_data_types_, context, request);
}

::grpc::ClientAsyncResponseReader< ::minknow_api::data::GetDataTypesResponse>* DataService::Stub::Asyncget_data_typesRaw(::grpc::ClientContext* context, const ::minknow_api::data::GetDataTypesRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncget_data_typesRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::ClientReader< ::minknow_api::data::GetSignalBytesResponse>* DataService::Stub::get_signal_bytesRaw(::grpc::ClientContext* context, const ::minknow_api::data::GetSignalBytesRequest& request) {
  return ::grpc::internal::ClientReaderFactory< ::minknow_api::data::GetSignalBytesResponse>::Create(channel_.get(), rpcmethod_get_signal_bytes_, context, request);
}

void DataService::Stub::async::get_signal_bytes(::grpc::ClientContext* context, const ::minknow_api::data::GetSignalBytesRequest* request, ::grpc::ClientReadReactor< ::minknow_api::data::GetSignalBytesResponse>* reactor) {
  ::grpc::internal::ClientCallbackReaderFactory< ::minknow_api::data::GetSignalBytesResponse>::Create(stub_->channel_.get(), stub_->rpcmethod_get_signal_bytes_, context, request, reactor);
}

::grpc::ClientAsyncReader< ::minknow_api::data::GetSignalBytesResponse>* DataService::Stub::Asyncget_signal_bytesRaw(::grpc::ClientContext* context, const ::minknow_api::data::GetSignalBytesRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::minknow_api::data::GetSignalBytesResponse>::Create(channel_.get(), cq, rpcmethod_get_signal_bytes_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::minknow_api::data::GetSignalBytesResponse>* DataService::Stub::PrepareAsyncget_signal_bytesRaw(::grpc::ClientContext* context, const ::minknow_api::data::GetSignalBytesRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::minknow_api::data::GetSignalBytesResponse>::Create(channel_.get(), cq, rpcmethod_get_signal_bytes_, context, request, false, nullptr);
}

::grpc::ClientReader< ::minknow_api::data::GetSignalMinMaxResponse>* DataService::Stub::get_signal_min_maxRaw(::grpc::ClientContext* context, const ::minknow_api::data::GetSignalMinMaxRequest& request) {
  return ::grpc::internal::ClientReaderFactory< ::minknow_api::data::GetSignalMinMaxResponse>::Create(channel_.get(), rpcmethod_get_signal_min_max_, context, request);
}

void DataService::Stub::async::get_signal_min_max(::grpc::ClientContext* context, const ::minknow_api::data::GetSignalMinMaxRequest* request, ::grpc::ClientReadReactor< ::minknow_api::data::GetSignalMinMaxResponse>* reactor) {
  ::grpc::internal::ClientCallbackReaderFactory< ::minknow_api::data::GetSignalMinMaxResponse>::Create(stub_->channel_.get(), stub_->rpcmethod_get_signal_min_max_, context, request, reactor);
}

::grpc::ClientAsyncReader< ::minknow_api::data::GetSignalMinMaxResponse>* DataService::Stub::Asyncget_signal_min_maxRaw(::grpc::ClientContext* context, const ::minknow_api::data::GetSignalMinMaxRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::minknow_api::data::GetSignalMinMaxResponse>::Create(channel_.get(), cq, rpcmethod_get_signal_min_max_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::minknow_api::data::GetSignalMinMaxResponse>* DataService::Stub::PrepareAsyncget_signal_min_maxRaw(::grpc::ClientContext* context, const ::minknow_api::data::GetSignalMinMaxRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::minknow_api::data::GetSignalMinMaxResponse>::Create(channel_.get(), cq, rpcmethod_get_signal_min_max_, context, request, false, nullptr);
}

::grpc::Status DataService::Stub::reset_channel_states(::grpc::ClientContext* context, const ::minknow_api::data::ResetChannelStatesRequest& request, ::minknow_api::data::ResetChannelStatesResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::minknow_api::data::ResetChannelStatesRequest, ::minknow_api::data::ResetChannelStatesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_reset_channel_states_, context, request, response);
}

void DataService::Stub::async::reset_channel_states(::grpc::ClientContext* context, const ::minknow_api::data::ResetChannelStatesRequest* request, ::minknow_api::data::ResetChannelStatesResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::minknow_api::data::ResetChannelStatesRequest, ::minknow_api::data::ResetChannelStatesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_reset_channel_states_, context, request, response, std::move(f));
}

void DataService::Stub::async::reset_channel_states(::grpc::ClientContext* context, const ::minknow_api::data::ResetChannelStatesRequest* request, ::minknow_api::data::ResetChannelStatesResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_reset_channel_states_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::minknow_api::data::ResetChannelStatesResponse>* DataService::Stub::PrepareAsyncreset_channel_statesRaw(::grpc::ClientContext* context, const ::minknow_api::data::ResetChannelStatesRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::minknow_api::data::ResetChannelStatesResponse, ::minknow_api::data::ResetChannelStatesRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_reset_channel_states_, context, request);
}

::grpc::ClientAsyncResponseReader< ::minknow_api::data::ResetChannelStatesResponse>* DataService::Stub::Asyncreset_channel_statesRaw(::grpc::ClientContext* context, const ::minknow_api::data::ResetChannelStatesRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncreset_channel_statesRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status DataService::Stub::lock_channel_states(::grpc::ClientContext* context, const ::minknow_api::data::LockChannelStatesRequest& request, ::minknow_api::data::LockChannelStatesResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::minknow_api::data::LockChannelStatesRequest, ::minknow_api::data::LockChannelStatesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_lock_channel_states_, context, request, response);
}

void DataService::Stub::async::lock_channel_states(::grpc::ClientContext* context, const ::minknow_api::data::LockChannelStatesRequest* request, ::minknow_api::data::LockChannelStatesResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::minknow_api::data::LockChannelStatesRequest, ::minknow_api::data::LockChannelStatesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_lock_channel_states_, context, request, response, std::move(f));
}

void DataService::Stub::async::lock_channel_states(::grpc::ClientContext* context, const ::minknow_api::data::LockChannelStatesRequest* request, ::minknow_api::data::LockChannelStatesResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_lock_channel_states_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::minknow_api::data::LockChannelStatesResponse>* DataService::Stub::PrepareAsynclock_channel_statesRaw(::grpc::ClientContext* context, const ::minknow_api::data::LockChannelStatesRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::minknow_api::data::LockChannelStatesResponse, ::minknow_api::data::LockChannelStatesRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_lock_channel_states_, context, request);
}

::grpc::ClientAsyncResponseReader< ::minknow_api::data::LockChannelStatesResponse>* DataService::Stub::Asynclock_channel_statesRaw(::grpc::ClientContext* context, const ::minknow_api::data::LockChannelStatesRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsynclock_channel_statesRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status DataService::Stub::unlock_channel_states(::grpc::ClientContext* context, const ::minknow_api::data::UnlockChannelStatesRequest& request, ::minknow_api::data::UnlockChannelStatesResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::minknow_api::data::UnlockChannelStatesRequest, ::minknow_api::data::UnlockChannelStatesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_unlock_channel_states_, context, request, response);
}

void DataService::Stub::async::unlock_channel_states(::grpc::ClientContext* context, const ::minknow_api::data::UnlockChannelStatesRequest* request, ::minknow_api::data::UnlockChannelStatesResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::minknow_api::data::UnlockChannelStatesRequest, ::minknow_api::data::UnlockChannelStatesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_unlock_channel_states_, context, request, response, std::move(f));
}

void DataService::Stub::async::unlock_channel_states(::grpc::ClientContext* context, const ::minknow_api::data::UnlockChannelStatesRequest* request, ::minknow_api::data::UnlockChannelStatesResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_unlock_channel_states_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::minknow_api::data::UnlockChannelStatesResponse>* DataService::Stub::PrepareAsyncunlock_channel_statesRaw(::grpc::ClientContext* context, const ::minknow_api::data::UnlockChannelStatesRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::minknow_api::data::UnlockChannelStatesResponse, ::minknow_api::data::UnlockChannelStatesRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_unlock_channel_states_, context, request);
}

::grpc::ClientAsyncResponseReader< ::minknow_api::data::UnlockChannelStatesResponse>* DataService::Stub::Asyncunlock_channel_statesRaw(::grpc::ClientContext* context, const ::minknow_api::data::UnlockChannelStatesRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncunlock_channel_statesRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::ClientReaderWriter< ::minknow_api::data::GetLiveReadsRequest, ::minknow_api::data::GetLiveReadsResponse>* DataService::Stub::get_live_readsRaw(::grpc::ClientContext* context) {
  return ::grpc::internal::ClientReaderWriterFactory< ::minknow_api::data::GetLiveReadsRequest, ::minknow_api::data::GetLiveReadsResponse>::Create(channel_.get(), rpcmethod_get_live_reads_, context);
}

void DataService::Stub::async::get_live_reads(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::minknow_api::data::GetLiveReadsRequest,::minknow_api::data::GetLiveReadsResponse>* reactor) {
  ::grpc::internal::ClientCallbackReaderWriterFactory< ::minknow_api::data::GetLiveReadsRequest,::minknow_api::data::GetLiveReadsResponse>::Create(stub_->channel_.get(), stub_->rpcmethod_get_live_reads_, context, reactor);
}

::grpc::ClientAsyncReaderWriter< ::minknow_api::data::GetLiveReadsRequest, ::minknow_api::data::GetLiveReadsResponse>* DataService::Stub::Asyncget_live_readsRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::minknow_api::data::GetLiveReadsRequest, ::minknow_api::data::GetLiveReadsResponse>::Create(channel_.get(), cq, rpcmethod_get_live_reads_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::minknow_api::data::GetLiveReadsRequest, ::minknow_api::data::GetLiveReadsResponse>* DataService::Stub::PrepareAsyncget_live_readsRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::minknow_api::data::GetLiveReadsRequest, ::minknow_api::data::GetLiveReadsResponse>::Create(channel_.get(), cq, rpcmethod_get_live_reads_, context, false, nullptr);
}

::grpc::Status DataService::Stub::get_read_statistics(::grpc::ClientContext* context, const ::minknow_api::data::GetReadStatisticsRequest& request, ::minknow_api::data::GetReadStatisticsResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::minknow_api::data::GetReadStatisticsRequest, ::minknow_api::data::GetReadStatisticsResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_get_read_statistics_, context, request, response);
}

void DataService::Stub::async::get_read_statistics(::grpc::ClientContext* context, const ::minknow_api::data::GetReadStatisticsRequest* request, ::minknow_api::data::GetReadStatisticsResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::minknow_api::data::GetReadStatisticsRequest, ::minknow_api::data::GetReadStatisticsResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_get_read_statistics_, context, request, response, std::move(f));
}

void DataService::Stub::async::get_read_statistics(::grpc::ClientContext* context, const ::minknow_api::data::GetReadStatisticsRequest* request, ::minknow_api::data::GetReadStatisticsResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_get_read_statistics_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::minknow_api::data::GetReadStatisticsResponse>* DataService::Stub::PrepareAsyncget_read_statisticsRaw(::grpc::ClientContext* context, const ::minknow_api::data::GetReadStatisticsRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::minknow_api::data::GetReadStatisticsResponse, ::minknow_api::data::GetReadStatisticsRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_get_read_statistics_, context, request);
}

::grpc::ClientAsyncResponseReader< ::minknow_api::data::GetReadStatisticsResponse>* DataService::Stub::Asyncget_read_statisticsRaw(::grpc::ClientContext* context, const ::minknow_api::data::GetReadStatisticsRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncget_read_statisticsRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status DataService::Stub::get_experiment_yield_info(::grpc::ClientContext* context, const ::minknow_api::data::GetExperimentYieldInfoRequest& request, ::minknow_api::data::GetExperimentYieldInfoResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::minknow_api::data::GetExperimentYieldInfoRequest, ::minknow_api::data::GetExperimentYieldInfoResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_get_experiment_yield_info_, context, request, response);
}

void DataService::Stub::async::get_experiment_yield_info(::grpc::ClientContext* context, const ::minknow_api::data::GetExperimentYieldInfoRequest* request, ::minknow_api::data::GetExperimentYieldInfoResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::minknow_api::data::GetExperimentYieldInfoRequest, ::minknow_api::data::GetExperimentYieldInfoResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_get_experiment_yield_info_, context, request, response, std::move(f));
}

void DataService::Stub::async::get_experiment_yield_info(::grpc::ClientContext* context, const ::minknow_api::data::GetExperimentYieldInfoRequest* request, ::minknow_api::data::GetExperimentYieldInfoResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_get_experiment_yield_info_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::minknow_api::data::GetExperimentYieldInfoResponse>* DataService::Stub::PrepareAsyncget_experiment_yield_infoRaw(::grpc::ClientContext* context, const ::minknow_api::data::GetExperimentYieldInfoRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::minknow_api::data::GetExperimentYieldInfoResponse, ::minknow_api::data::GetExperimentYieldInfoRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_get_experiment_yield_info_, context, request);
}

::grpc::ClientAsyncResponseReader< ::minknow_api::data::GetExperimentYieldInfoResponse>* DataService::Stub::Asyncget_experiment_yield_infoRaw(::grpc::ClientContext* context, const ::minknow_api::data::GetExperimentYieldInfoRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncget_experiment_yield_infoRaw(context, request, cq);
  result->StartCall();
  return result;
}

DataService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataService_method_names[0],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< DataService::Service, ::minknow_api::data::GetChannelStatesRequest, ::minknow_api::data::GetChannelStatesResponse>(
          [](DataService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::minknow_api::data::GetChannelStatesRequest* req,
             ::grpc::ServerWriter<::minknow_api::data::GetChannelStatesResponse>* writer) {
               return service->get_channel_states(ctx, req, writer);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataService::Service, ::minknow_api::data::GetDataTypesRequest, ::minknow_api::data::GetDataTypesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](DataService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::minknow_api::data::GetDataTypesRequest* req,
             ::minknow_api::data::GetDataTypesResponse* resp) {
               return service->get_data_types(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataService_method_names[2],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< DataService::Service, ::minknow_api::data::GetSignalBytesRequest, ::minknow_api::data::GetSignalBytesResponse>(
          [](DataService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::minknow_api::data::GetSignalBytesRequest* req,
             ::grpc::ServerWriter<::minknow_api::data::GetSignalBytesResponse>* writer) {
               return service->get_signal_bytes(ctx, req, writer);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataService_method_names[3],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< DataService::Service, ::minknow_api::data::GetSignalMinMaxRequest, ::minknow_api::data::GetSignalMinMaxResponse>(
          [](DataService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::minknow_api::data::GetSignalMinMaxRequest* req,
             ::grpc::ServerWriter<::minknow_api::data::GetSignalMinMaxResponse>* writer) {
               return service->get_signal_min_max(ctx, req, writer);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataService_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataService::Service, ::minknow_api::data::ResetChannelStatesRequest, ::minknow_api::data::ResetChannelStatesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](DataService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::minknow_api::data::ResetChannelStatesRequest* req,
             ::minknow_api::data::ResetChannelStatesResponse* resp) {
               return service->reset_channel_states(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataService_method_names[5],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataService::Service, ::minknow_api::data::LockChannelStatesRequest, ::minknow_api::data::LockChannelStatesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](DataService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::minknow_api::data::LockChannelStatesRequest* req,
             ::minknow_api::data::LockChannelStatesResponse* resp) {
               return service->lock_channel_states(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataService_method_names[6],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataService::Service, ::minknow_api::data::UnlockChannelStatesRequest, ::minknow_api::data::UnlockChannelStatesResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](DataService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::minknow_api::data::UnlockChannelStatesRequest* req,
             ::minknow_api::data::UnlockChannelStatesResponse* resp) {
               return service->unlock_channel_states(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataService_method_names[7],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< DataService::Service, ::minknow_api::data::GetLiveReadsRequest, ::minknow_api::data::GetLiveReadsResponse>(
          [](DataService::Service* service,
             ::grpc::ServerContext* ctx,
             ::grpc::ServerReaderWriter<::minknow_api::data::GetLiveReadsResponse,
             ::minknow_api::data::GetLiveReadsRequest>* stream) {
               return service->get_live_reads(ctx, stream);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataService_method_names[8],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataService::Service, ::minknow_api::data::GetReadStatisticsRequest, ::minknow_api::data::GetReadStatisticsResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](DataService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::minknow_api::data::GetReadStatisticsRequest* req,
             ::minknow_api::data::GetReadStatisticsResponse* resp) {
               return service->get_read_statistics(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DataService_method_names[9],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DataService::Service, ::minknow_api::data::GetExperimentYieldInfoRequest, ::minknow_api::data::GetExperimentYieldInfoResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](DataService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::minknow_api::data::GetExperimentYieldInfoRequest* req,
             ::minknow_api::data::GetExperimentYieldInfoResponse* resp) {
               return service->get_experiment_yield_info(ctx, req, resp);
             }, this)));
}

DataService::Service::~Service() {
}

::grpc::Status DataService::Service::get_channel_states(::grpc::ServerContext* context, const ::minknow_api::data::GetChannelStatesRequest* request, ::grpc::ServerWriter< ::minknow_api::data::GetChannelStatesResponse>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataService::Service::get_data_types(::grpc::ServerContext* context, const ::minknow_api::data::GetDataTypesRequest* request, ::minknow_api::data::GetDataTypesResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataService::Service::get_signal_bytes(::grpc::ServerContext* context, const ::minknow_api::data::GetSignalBytesRequest* request, ::grpc::ServerWriter< ::minknow_api::data::GetSignalBytesResponse>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataService::Service::get_signal_min_max(::grpc::ServerContext* context, const ::minknow_api::data::GetSignalMinMaxRequest* request, ::grpc::ServerWriter< ::minknow_api::data::GetSignalMinMaxResponse>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataService::Service::reset_channel_states(::grpc::ServerContext* context, const ::minknow_api::data::ResetChannelStatesRequest* request, ::minknow_api::data::ResetChannelStatesResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataService::Service::lock_channel_states(::grpc::ServerContext* context, const ::minknow_api::data::LockChannelStatesRequest* request, ::minknow_api::data::LockChannelStatesResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataService::Service::unlock_channel_states(::grpc::ServerContext* context, const ::minknow_api::data::UnlockChannelStatesRequest* request, ::minknow_api::data::UnlockChannelStatesResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataService::Service::get_live_reads(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::minknow_api::data::GetLiveReadsResponse, ::minknow_api::data::GetLiveReadsRequest>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataService::Service::get_read_statistics(::grpc::ServerContext* context, const ::minknow_api::data::GetReadStatisticsRequest* request, ::minknow_api::data::GetReadStatisticsResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DataService::Service::get_experiment_yield_info(::grpc::ServerContext* context, const ::minknow_api::data::GetExperimentYieldInfoRequest* request, ::minknow_api::data::GetExperimentYieldInfoResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace minknow_api
}  // namespace data
