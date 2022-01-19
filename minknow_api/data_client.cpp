#include "minknow_api/data_client.h"

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

using namespace Data;

/*
  ReadCache is an ordered and keyed data structure made up of:
  - an unordered map (dict) which maps from channel_id to data
  - a queue (insertion_order) with channel_id to maintain insertion order
*/

// Append a new entry to data_queue by channel_id as key and data as value
void Data::ReadCache::set_item(u_int32_t channel,
                               GetLiveReadsResponse_ReadData data) {
  mtx.lock();
  dict[channel] = data;
  insertion_order.push(channel);
  mtx.unlock();
}

// Thread safe method to retrieve data by channel_id key
GetLiveReadsResponse_ReadData Data::ReadCache::get_item(u_int32_t channel) {
  mtx.lock();
  GetLiveReadsResponse_ReadData data = dict[channel];
  mtx.unlock();
  return data;
}

// Thread safe method to pop the oldest entry in the data_queue
GetLiveReadsResponse_ReadData Data::ReadCache::pop_item() {
  mtx.lock();
  if (insertion_order.size() == 0) {
    GetLiveReadsResponse_ReadData basic;
    mtx.unlock();
    return basic;
  }
  u_int32_t channel = insertion_order.front();
  insertion_order.pop();
  GetLiveReadsResponse_ReadData data = dict[channel];
  dict.erase(channel);
  mtx.unlock();
  return data;
}

DataClient::DataClient(std::shared_ptr<Channel> channel, int size)
    : stub_(DataService::NewStub(channel)), data_queue(size) {
  std::cout << "Connected to DataService" << std::endl;
}

// Creates a stream instance of get_live_reads() and a reader + writer thread
void DataClient::get_live_reads(u_int32_t first_channel, u_int32_t last_channel,
                                u_int64_t sample_minimum_chunk_size) {
  this->first_channel = first_channel;
  this->last_channel = last_channel;
  this->sample_minimum_chunk_size = sample_minimum_chunk_size;
  ClientContext context;
  stream = stub_->get_live_reads(&context);
  std::thread writer = spawn_send_thread();
  writer.join();
  std::thread reader = spawn_read_thread();
  reader.join();
}

// Listens to incoming stream responses and appends to the data_queue
void DataClient::read_live_results() {
  // Never close the stream
  GetLiveReadsResponse response;
  while (stream->Read(&response)) {
    for (auto entry : response.channels()) {  // .first refers to channel id
      data_queue.set_item(entry.first, entry.second);
    }
  }
}

// TODO: Complete the action_queue so that this can start listening
// Listens for incoming actions and sends them to be processed
void DataClient::send_live_reqs() {
  // Create setup request and send it
  make_setup();
  GetLiveReadsRequest request;
  request.mutable_setup()->CopyFrom(setup);
  stream->Write(request);
}

// Create an empty GetLiveReadsRequest for the purpose to setup the connection
void DataClient::make_setup() {
  GetLiveReadsRequest_StreamSetup new_setup;
  setup = new_setup;
  setup.set_first_channel(first_channel);
  setup.set_last_channel(last_channel);
  setup.set_raw_data_type(GetLiveReadsRequest_RawDataType::
                              GetLiveReadsRequest_RawDataType_CALIBRATED);
  setup.set_sample_minimum_chunk_size(sample_minimum_chunk_size);
}

// Return a pointer to the data queue
Data::ReadCache* DataClient::get_read_cache() { return &data_queue; }

// Spawn a new reading thread
std::thread DataClient::spawn_read_thread() {
  return std::thread([this] { this->read_live_results(); });
}

// Spawn a new writing thread
std::thread DataClient::spawn_send_thread() {
  return std::thread([this] { this->send_live_reqs(); });
}