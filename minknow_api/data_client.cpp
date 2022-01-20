#include "minknow_api/data_client.h"

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
using minknow_api::data::GetLiveReadsRequest_Actions;
using minknow_api::data::GetLiveReadsRequest_RawDataType;
using minknow_api::data::GetLiveReadsRequest_StopFurtherData;
using minknow_api::data::GetLiveReadsRequest_StreamSetup;
using minknow_api::data::GetLiveReadsRequest_UnblockAction;
using minknow_api::data::GetLiveReadsResponse;

using namespace Data;

// TODO: Create a centralised and thread safe boolean to dictate if the client
// is running

/*
  ReadCache is an ordered and keyed data structure made up of:
  - an unordered map (dict) which maps from channel_id to data
  - a queue (insertion_order) with channel_id to maintain insertion order
*/

// Append a new entry to data_queue by channel_id as key and data as value
void ReadCache::set_item(u_int32_t channel,
                         GetLiveReadsResponse_ReadData data) {
  cache_mtx.lock();
  dict[channel] = data;
  insertion_order.push(channel);
  cache_mtx.unlock();
}

// Thread safe method to retrieve data by channel_id key
GetLiveReadsResponse_ReadData ReadCache::get_item(u_int32_t channel) {
  cache_mtx.lock();
  GetLiveReadsResponse_ReadData data = dict[channel];
  cache_mtx.unlock();
  return data;
}

// Thread safe method to pop the oldest entry in the data_queue
std::pair<u_int32_t, GetLiveReadsResponse_ReadData> ReadCache::pop_item() {
  cache_mtx.lock();
  u_int32_t channel = insertion_order.front();
  insertion_order.pop();
  GetLiveReadsResponse_ReadData data = dict[channel];
  dict.erase(channel);
  cache_mtx.unlock();
  return std::make_pair(channel, data);
}

// Return size of ReadCache, both dict and insertion_order are same size
int ReadCache::get_size() {
  cache_mtx.lock();
  int result = insertion_order.size();
  cache_mtx.unlock();
  return result;
}

DataClient::DataClient(std::shared_ptr<Channel> channel, int size,
                       int action_batch)
    : stub_(DataService::NewStub(channel)),
      data_queue(size),
      action_batch(action_batch) {
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
  std::thread reader = spawn_read_thread();
  writer.join();
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

// Listens for incoming actions and sends them to be processed
void DataClient::send_live_reqs() {
  // Create setup request and send it
  make_setup();
  GetLiveReadsRequest request;
  request.mutable_setup()->CopyFrom(setup);
  stream->Write(request);
  request.clear_setup();

  while (true) {
    int length = get_action_queue_size();
    if (length > 0) {
      // Get maximum number of actions to process
      int max_actions = action_batch;
      if (length < action_batch) {
        max_actions = length;
      }
      GetLiveReadsRequest_Actions actions;
      for (int i = 0; i < max_actions; i++) {
        actions.add_actions()->CopyFrom(pop_action());
      }
      std::cout << "Sending " << max_actions << " actions." << std::endl;
      request.mutable_actions()->CopyFrom(actions);
      stream->Write(request);
    }
  }
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

// TODO: Figure out what action_id is meant to do and also unblock duration
// parameter?
// Create an action and place into action_queue (thread safe)
void DataClient::put_action(u_int32_t read_channel, u_int32_t read_number,
                            std::string action) {
  GetLiveReadsRequest_Action action_request;
  action_request.set_channel(read_channel);
  action_request.set_number(read_number);

  if (action.compare("unblock") == 0) {
    GetLiveReadsRequest_UnblockAction unblock;
    // unblock.set_duration()
    action_request.mutable_unblock()->CopyFrom(unblock);
  } else if (action.compare("stop_further_data") == 0) {
    GetLiveReadsRequest_StopFurtherData stop_data;
    action_request.mutable_stop_further_data()->CopyFrom(stop_data);
  } else {
    std::cout << "Action must be 'unblock' or 'stop_further_data'."
              << std::endl;
  }
  action_mtx.lock();
  action_queue.push(action_request);
  action_mtx.unlock();
}

// Thread safe method to get the first value in the data_queue
GetLiveReadsRequest_Action DataClient::pop_action() {
  action_mtx.lock();
  GetLiveReadsRequest_Action result = action_queue.front();
  action_queue.pop();
  action_mtx.unlock();
  return result;
}

int DataClient::get_action_queue_size() {
  action_mtx.lock();
  int result = action_queue.size();
  action_mtx.unlock();
  return result;
}

// Return a pointer to the data queue
ReadCache* DataClient::get_read_cache() { return &data_queue; }

// Return a pointer to the action queue
std::queue<GetLiveReadsRequest_Action>* DataClient::get_action_queue() {
  return &action_queue;
}

// Spawn a new reading thread
std::thread DataClient::spawn_read_thread() {
  return std::thread([this] { this->read_live_results(); });
}

// Spawn a new writing thread
std::thread DataClient::spawn_send_thread() {
  return std::thread([this] { this->send_live_reqs(); });
}