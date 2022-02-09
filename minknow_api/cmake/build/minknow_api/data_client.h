#pragma once

#ifndef DATA_CLIENT_H
#define DATA_CLIENT_H

#include <chrono>
#include <ctime>
#include <memory>
#include <mutex>
#include <optional>
#include <queue>
#include <string>
#include <thread>
#include <vector>

#include "acquisition_client.h"
#include "minknow_api/data.grpc.pb.h"

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/credentials.h>

using Acquisition::AcquisitionClient;
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
  ReadCache(int max_size);
  GetLiveReadsResponse_ReadData get_item(u_int32_t channel);
  void set_item(u_int32_t channel, GetLiveReadsResponse_ReadData data);
  std::pair<u_int32_t, GetLiveReadsResponse_ReadData> pop_item(bool safe);
  std::vector<std::pair<u_int32_t, GetLiveReadsResponse_ReadData>> pop_items(
      int count);
  void delete_item(u_int32_t channel);
  int get_size(bool safe);
  int get_missed();
  int get_replaced();

 private:
  std::unordered_map<uint32_t, GetLiveReadsResponse_ReadData> dict;
  std::vector<u_int32_t> insertion_order;
  int max_size;
  int missed;
  int replaced;
  std::mutex cache_mtx;
};

class DataClient {
 public:
  DataClient(std::shared_ptr<Channel> channel, int cache_size, int action_batch,
             bool filter_strands, bool one_chunk,
             std::unordered_set<std::string> prefilter_classes);
  void run();
  void get_live_reads(u_int32_t first_channel, u_int32_t last_channel,
                      u_int64_t sample_minimum_chunk_size);
  void send_live_reqs();
  void read_live_results();
  void make_setup();
  void put_action(u_int32_t read_channel, u_int32_t read_number,
                  double duration, std::string action);
  GetLiveReadsRequest_Action pop_action();
  int get_action_queue_size();
  ReadCache* get_read_cache();
  std::queue<GetLiveReadsRequest_Action>* get_action_queue();
  bool* get_client_running();
  void get_data_types();

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
  int curr_action_id;
  std::unordered_map<std::string, std::string> sent_actions;
  // All accepted read types
  const std::unordered_map<u_int32_t, std::string> read_classification_map = {
      {83, "strand"},   {67, "strand1"},     {77, "multiple"},
      {90, "zero"},     {65, "adapter"},     {66, "mux_uncertain"},
      {70, "user2"},    {68, "user1"},       {69, "event"},
      {80, "pore"},     {85, "unavailable"}, {84, "transition"},
      {78, "unclassed"}};
  bool filter_strands;
  bool one_chunk;
  std::unordered_set<std::string> prefilter_classes;
  AcquisitionClient acq_client;
  bool client_running;
  std::unordered_map<
      u_int32_t,
      std::unordered_map<u_int32_t, std::chrono::system_clock::time_point>>
      sent_time;
  long aggregated_time;
  bool print_result = true;
};
}  // namespace Data
#endif
