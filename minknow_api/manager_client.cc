#include <grpcpp/grpcpp.h>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <string>

#include "minknow_api/manager.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientReader;
using minknow_api::manager::ManagerService;
using minknow_api::manager::FlowCellPositionsRequest;
using minknow_api::manager::FlowCellPositionsResponse;


class ManagerClient {
  public:
    ManagerClient(std::shared_ptr<Channel> channel) : stub_(ManagerService::NewStub(channel)) {}

  void GetDesc() {
      std::cout << "Getting description of the MinKNOW Machine\n";
      ClientContext context;
      FlowCellPositionsRequest request;
      FlowCellPositionsResponse feature;
      std::unique_ptr<ClientReader<FlowCellPositionsResponse>> reader = stub_->flow_cell_positions(&context, request);
      while(reader->Read(&feature)) {
        std::cout << feature.positions(0).name() << std::endl;
        std::cout << feature.positions(0).rpc_ports().insecure() << std::endl;
      }
      Status status = reader->Finish();
      if(status.ok()) {
        std::cout << "Finished successfully!" << std::endl;
      } else {
        std::cout << "Failed " << status.error_code() << std::endl;
      }
  }
  private:
    std::unique_ptr<ManagerService::Stub> stub_;
};

int main(int argc, char* argv[]) {
  std::cout << "Connecting to MinKNOW API...\n";
  ManagerClient client(
      grpc::CreateChannel("127.0.0.1:9501",
                          grpc::InsecureChannelCredentials()));
  client.GetDesc();
  return 0;
}