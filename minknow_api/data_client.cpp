#include "minknow_api/data_client.h"

#include <ctime>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

#include "minknow_api/data.grpc.pb.h"

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/credentials.h>

#define ALLOWED_MIN_CHUNK_SIZE 0

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
using minknow_api::data::GetLiveReadsResponse_ActionResponse;
using minknow_api::data::GetLiveReadsResponse_ActionResponse_Response;

using namespace Data;

// TODO: Create a centralised and thread safe boolean to dictate if the client
// is running

/*
  ReadCache is an ordered and keyed data structure made up of:
  - an unordered map (dict) which maps from channel_id to data
  - a queue (insertion_order) with channel_id to maintain insertion order
*/

ReadCache::ReadCache(int max_size) : max_size(max_size) {
  missed = 0;
  replaced = 0;
}

// Append a new entry to data_queue by channel_id as key and data as value
void ReadCache::set_item(u_int32_t channel,
                         GetLiveReadsResponse_ReadData data) {
  cache_mtx.lock();
  bool counted = false;
  // ReadCache exceeding limit
  while (get_size(false) > max_size) {
    counted = true;
    // Mutex locked, so use the unsafe thread version
    std::pair<u_int32_t, GetLiveReadsResponse_ReadData> read_batch =
        pop_item(false);
    u_int32_t read_channel = read_batch.first;
    GetLiveReadsResponse_ReadData read_data = read_batch.second;
    if (read_channel == channel && read_data.number() == data.number()) {
      replaced++;
    } else {
      missed++;
    }
  }
  // Channels must be unique in ReadCache
  if (dict.contains(channel)) {
    if (!counted) {
      if (dict[channel].number() == data.number()) {
        replaced++;
      } else {
        missed++;
      }
    }
    // Similarly, mutex locked so delete without concern for thread safety
    delete_item(channel);
  }

  // After filtering, we append the new entry
  dict[channel] = data;
  insertion_order.push_back(channel);
  cache_mtx.unlock();
}

int ReadCache::get_missed() { return missed; }

int ReadCache::get_replaced() { return replaced; }

// Thread safe method to retrieve data by channel_id key
GetLiveReadsResponse_ReadData ReadCache::get_item(u_int32_t channel) {
  cache_mtx.lock();
  GetLiveReadsResponse_ReadData data = dict[channel];
  cache_mtx.unlock();
  return data;
}

// Thread safe method to pop the oldest entry in the data_queue
std::pair<u_int32_t, GetLiveReadsResponse_ReadData> ReadCache::pop_item(
    bool safe) {
  if (safe) {
    cache_mtx.lock();
  }
  u_int32_t channel = insertion_order[0];
  insertion_order.erase(insertion_order.begin());
  GetLiveReadsResponse_ReadData data = dict[channel];
  dict.erase(channel);
  if (safe) {
    cache_mtx.unlock();
  }
  return std::make_pair(channel, data);
}

// Delete a channel and its data from ReadCache, not thread safe due to its
// application
void ReadCache::delete_item(u_int32_t channel) {
  dict.erase(channel);
  for (int i = 0; i < insertion_order.size(); i++) {
    if (insertion_order[i] == channel) {
      insertion_order.erase(insertion_order.begin() + i);
      return;
    }
  }
}

// Return size of ReadCache, both dict and insertion_order are same size
int ReadCache::get_size(bool safe) {
  if (safe) {
    cache_mtx.lock();
  }
  int result = insertion_order.size();
  if (safe) {
    cache_mtx.unlock();
  }
  return result;
}

DataClient::DataClient(std::shared_ptr<Channel> channel, int cache_size,
                       int action_batch, bool filter_strands, bool one_chunk,
                       std::unordered_set<std::string> prefilter_classes)
    : stub_(DataService::NewStub(channel)),
      data_queue(cache_size),
      action_batch(action_batch),
      filter_strands(filter_strands),
      one_chunk(one_chunk),
      prefilter_classes(prefilter_classes),
      acq_client(channel) {
  std::cout << "Connected to DataService" << std::endl;
}

// Creates a stream instance of get_live_reads() and a reader + writer thread
void DataClient::get_live_reads(u_int32_t first_channel, u_int32_t last_channel,
                                u_int64_t sample_minimum_chunk_size) {
  this->first_channel = first_channel;
  this->last_channel = last_channel;
  if (sample_minimum_chunk_size > ALLOWED_MIN_CHUNK_SIZE) {
    std::cout << "Reducing min_chunk_size to " << ALLOWED_MIN_CHUNK_SIZE
              << std::endl;
    sample_minimum_chunk_size = ALLOWED_MIN_CHUNK_SIZE;
  }
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
  std::unordered_map<
      std::string,
      std::unordered_map<GetLiveReadsResponse_ActionResponse_Response, int>>
      response_counter;

  GetLiveReadsResponse response;
  std::unordered_set<std::string> unique_reads;
  int read_count = 0;
  int samples_behind = 0;
  int raw_data_bytes = 0;

  // Decide whether you need prefiltering
  if (filter_strands) {
    if (prefilter_classes.size() == 0) {
      std::cout << "Read filtering set but no filter classes given."
                << std::endl;
    }
  }

  // Never close the stream
  while (stream->Read(&response)) {
    if (response.action_responses().size() > 0) {
      for (GetLiveReadsResponse_ActionResponse action_response :
           response.action_responses()) {
        // Get the action via ID
        std::string action_type = sent_actions[action_response.action_id()];
        response_counter[action_type][action_response.response()]++;
      }
    }
    // .first refers to channel id and .second refers to read data
    for (auto entry : response.channels()) {
      std::pair<u_int64_t, u_int64_t> progress =
          acq_client.get_raw_per_channel();
      u_int32_t channel = entry.first;
      GetLiveReadsResponse_ReadData read_data = entry.second;
      read_count++;
      if (one_chunk) {
        if (unique_reads.contains(read_data.id())) {
          std::cout << "Rereceived " << channel << ":" << read_data.number()
                    << " after stop request." << std::endl;
          continue;
        }
        put_action(channel, read_data.number(), "stop_further_data");
      }
      unique_reads.insert(read_data.id());
      samples_behind += progress.first - read_data.chunk_start_sample();
      raw_data_bytes += read_data.raw_data().size();

      bool strand_like = false;
      for (u_int32_t classification : read_data.chunk_classifications()) {
        if (!read_classification_map.contains(classification)) {
          continue;
        }
        if (prefilter_classes.contains(
                read_classification_map.at(classification))) {
          strand_like = true;
          break;
        }
      }
      if (!filter_strands || strand_like) {
        data_queue.set_item(channel, read_data);
      }
    }

    time_t tmNow = time(0);
    char* dt = ctime(&tmNow);
    std::cout << dt << ": Interval update: " << read_count << " read sections, "
              << unique_reads.size() << " unique reads (ever), average "
              << samples_behind / read_count << " samples behind."
              << (float)raw_data_bytes / 1024 / 1024 << " MB raw data, "
              << data_queue.get_size(true) << " reads in queue, "
              << data_queue.get_missed() << " reads missed, "
              << data_queue.get_replaced() << " chunks replaced." << std::endl;

    read_count = 0;
    samples_behind = 0;
    raw_data_bytes = 0;
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
      int max_actions = std::min(action_batch, length);
      GetLiveReadsRequest_Actions actions;
      for (int i = 0; i < max_actions; i++) {
        actions.add_actions()->CopyFrom(pop_action());
      }
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
// TODO: Figure out how to throw an exception
// Create an action and place into action_queue (thread safe)
void DataClient::put_action(u_int32_t read_channel, u_int32_t read_number,
                            std::string action) {
  GetLiveReadsRequest_Action action_request;
  std::string action_id = std::to_string(++curr_action_id);
  action_request.set_action_id(action_id);
  action_request.set_channel(read_channel);
  action_request.set_number(read_number);
  sent_actions[action_id] = action;

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
