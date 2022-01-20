#pragma once

#ifndef DATA_CLIENT_H
#define DATA_CLIENT_H

#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "minknow_api/data.grpc.pb.h"

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/credentials.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::Status;
using minknow_api::data::DataService;
using minknow_api::data::GetDataTypesRequest;
using minknow_api::data::GetDataTypesResponse;
using minknow_api::data::GetLiveReadsRequest;
using minknow_api::data::GetLiveReadsRequest_Action;
using minknow_api::data::GetLiveReadsRequest_RawDataType;
using minknow_api::data::GetLiveReadsRequest_StreamSetup;
using minknow_api::data::GetLiveReadsResponse;
using minknow_api::data::GetLiveReadsResponse_ReadData;

namespace Data {

class ReadCache;

class ReadCache {
 public:
  ReadCache(int max_size) : max_size(max_size){};
  GetLiveReadsResponse_ReadData get_item(u_int32_t channel);
  void set_item(u_int32_t channel, GetLiveReadsResponse_ReadData data);
  std::pair<u_int32_t, GetLiveReadsResponse_ReadData> pop_item();
  int get_size();

 private:
  std::unordered_map<uint32_t, GetLiveReadsResponse_ReadData> dict;
  std::queue<u_int32_t> insertion_order;
  int max_size;
  int missed;
  int replaced;
  std::mutex cache_mtx;
};

class DataClient {
 public:
  DataClient(std::shared_ptr<Channel> channel, int size, int action_batch);
  void run();
  void get_live_reads(u_int32_t first_channel, u_int32_t last_channel,
                      u_int64_t sample_minimum_chunk_size);
  void send_live_reqs();
  void read_live_results();
  void make_setup();
  void put_action(u_int32_t read_channel, u_int32_t read_number,
                  std::string action);
  GetLiveReadsRequest_Action pop_action();
  int get_action_queue_size();
  ReadCache* get_read_cache();
  std::queue<GetLiveReadsRequest_Action>* get_action_queue();

 private:
  std::thread spawn_read_thread();
  std::thread spawn_send_thread();
  std::unique_ptr<DataService::Stub> stub_;
  std::shared_ptr<ClientReaderWriter<GetLiveReadsRequest, GetLiveReadsResponse>>
      stream;
  GetLiveReadsRequest_StreamSetup setup;
  u_int32_t first_channel;
  u_int32_t last_channel;
  u_int64_t sample_minimum_chunk_size;
  ReadCache data_queue;
  std::queue<GetLiveReadsRequest_Action> action_queue;
  std::mutex action_mtx;
  int action_batch;
};
}  // namespace Data
#endif