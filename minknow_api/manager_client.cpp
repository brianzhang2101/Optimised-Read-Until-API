#include <grpcpp/grpcpp.h>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <string>
#include <memory>

#include "minknow_api/manager.grpc.pb.h"
#include "minknow_api/manager_client.h"
#include "minknow_api/data_client.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientReader;
using minknow_api::manager::ManagerService;
using minknow_api::manager::FlowCellPositionsRequest;
using minknow_api::manager::FlowCellPositionsResponse;
using Data::DataClient;

using namespace Manager;

ManagerClient::ManagerClient(std::shared_ptr<Channel> channel) 
              : stub_(ManagerService::NewStub(channel)) {
  std::cout << "Connected to ManagerClient on: ";
  ManagerClient::flow_cell_positions();
}

// Returns the name of the first position in the MinKNOW network
void ManagerClient::flow_cell_positions() {
  ClientContext context;
  FlowCellPositionsRequest request;
  FlowCellPositionsResponse response;
  std::unique_ptr<ClientReader<FlowCellPositionsResponse> > reader = stub_->flow_cell_positions(&context, request);
  while(reader->Read(&response)) {
    std::cout << response.positions(0).name() << std::endl;
  }
  Status status = reader->Finish();
  if(!status.ok()) {
    std::cout << "Getting flow cell positions error: " << status.error_code() << std::endl;
  }
}