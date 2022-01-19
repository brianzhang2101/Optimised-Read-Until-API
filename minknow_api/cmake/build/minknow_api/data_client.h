#pragma once

#ifndef DATA_CLIENT_H
#define DATA_CLIENT_H

#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

#include "minknow_api/data.grpc.pb.h"
#include "minknow_api/read_cache.h"

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
using minknow_api::data::GetLiveReadsRequest_RawDataType;
using minknow_api::data::GetLiveReadsRequest_StreamSetup;
using minknow_api::data::GetLiveReadsResponse;
using minknow_api::data::GetLiveReadsResponse_ReadData;

namespace Data {

class ReadCache;

class ReadCache {
 public:
  ReadCache(int size) : size(size){};
  GetLiveReadsResponse_ReadData get_item(u_int32_t channel);
  void set_item(u_int32_t channel, GetLiveReadsResponse_ReadData data);
  GetLiveReadsResponse_ReadData pop_item();

 private:
  std::unordered_map<uint32_t, GetLiveReadsResponse_ReadData> dict;
  std::queue<u_int32_t> insertion_order;
  int size;
  int missed;
  int replaced;
  std::mutex mtx;
};

class DataClient {
 public:
  DataClient(std::shared_ptr<Channel> channel, int size);
  void run();
  void get_live_reads(u_int32_t first_channel, u_int32_t last_channel,
                      u_int64_t sample_minimum_chunk_size);
  void send_live_reqs();
  void read_live_results();
  void make_setup();
  ReadCache* get_read_cache();

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
};
}  // namespace Data
#endif