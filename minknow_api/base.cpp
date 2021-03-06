#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <thread>

#include "minknow_api/data_client.h"
#include "minknow_api/manager.grpc.pb.h"
#include "minknow_api/manager_client.h"

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/security/credentials.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::Status;
using minknow_api::data::GetLiveReadsRequest_Action;
using minknow_api::manager::FlowCellPositionsRequest;
using minknow_api::manager::FlowCellPositionsResponse;

using namespace Manager;

class ReadUntilClient {
 public:
  /*
  Port 9501 is insecure for Manager
  Port 8000 is insecure for all other services
  int size - represents the max size of the data_queue
  int action_batch - maximum number of actions to send per request
  */
  ReadUntilClient()
      : manager(grpc::CreateChannel("127.0.0.1:9501",
                                    grpc::InsecureChannelCredentials())),
        data(grpc::CreateChannel("127.0.0.1:8000",
                                 grpc::InsecureChannelCredentials()),
             512, 1000, true, true,
             std::unordered_set<std::string>{"strand", "adapter"}) {
    client_running = data.get_client_running();
  }

  // Creates a thread to listen to responses from data_queue, make decisions
  // here and add actions to action_queue
  void run(int action_batch) {
    data_queue = data.get_read_cache();
    action_queue = data.get_action_queue();
    std::thread runner([this, action_batch]() {
      while (client_running) {
        std::vector<std::pair<u_int32_t, GetLiveReadsResponse_ReadData>> batch =
            data_queue->pop_items(action_batch);
        auto last_msg_time =
            std::chrono::system_clock::now() + std::chrono::milliseconds(100);

        // Pop up to action_batch data items and process them
        for (std::pair<u_int32_t, GetLiveReadsResponse_ReadData> read_batch :
             batch) {
          u_int32_t channel = read_batch.first;
          GetLiveReadsResponse_ReadData read = read_batch.second;
          if (read.median_before() > read.median() &&
              read.median_before() - read.median() > 60) {
            data.put_action(channel, read.number(), 0, "stop_further_data");
          }
          data.put_action(channel, read.number(), 0.1, "unblock");
        }

        auto curr_time = std::chrono::system_clock::now();
        if (last_msg_time > curr_time) {
          std::this_thread::sleep_for(last_msg_time - curr_time);
        }
      }
    });
    data.get_live_reads(1, 512, 1);
    runner.join();
  }

 private:
  bool* client_running;
  ManagerClient manager;
  DataClient data;
  Data::ReadCache* data_queue;
  std::queue<GetLiveReadsRequest_Action>* action_queue;
};

int main(int argc, char* argv[]) {
  std::cout << "Connecting to MinKNOW API..." << std::endl;
  ReadUntilClient client;
  client.run(10);
  return 0;
}