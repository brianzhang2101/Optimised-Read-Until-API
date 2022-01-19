#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "minknow_api/data_client.h"
#include "minknow_api/manager.grpc.pb.h"
#include "minknow_api/manager_client.h"
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
using grpc::Status;
using minknow_api::manager::FlowCellPositionsRequest;
using minknow_api::manager::FlowCellPositionsResponse;

using namespace Manager;

class ReadUntilClient {
 public:
  /*
  Port 9501 is insecure for Manager
  Port 8000 is insecure for all other services
  int size - represents the max size of the data_queue
  */
  ReadUntilClient()
      : manager(grpc::CreateChannel("127.0.0.1:9501",
                                    grpc::InsecureChannelCredentials())),
        data(grpc::CreateChannel("127.0.0.1:8000",
                                 grpc::InsecureChannelCredentials()),
             100) {}

  // Creates a thread to listen to responses from data_queue, make decisions
  // here and add actions to action_queue
  void run() {
    client_running = true;
    data_queue = data.get_read_cache();
    std::thread runner([this]() {
      while (client_running) {
        int length = data_queue->pop_item().chunk_length();
        if (length > 0) {
          std::cout << length << std::endl;
        }
      }
    });
    data.get_live_reads(1, 512, 1);
    runner.join();
  }

 private:
  bool client_running = false;
  ManagerClient manager;
  DataClient data;
  Data::ReadCache* data_queue;
};

int main(int argc, char* argv[]) {
  std::cout << "Connecting to MinKNOW API..." << std::endl;
  ReadUntilClient client;
  client.run();
  return 0;
}
