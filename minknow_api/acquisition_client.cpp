#include "minknow_api/acquisition_client.h"

#include <memory>
#include <string>

#include "minknow_api/acquisition.grpc.pb.h"

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
using minknow_api::acquisition::AcquisitionService;
using minknow_api::acquisition::GetProgressRequest;
using minknow_api::acquisition::GetProgressResponse;

using namespace Acquisition;

AcquisitionClient::AcquisitionClient(std::shared_ptr<Channel> channel)
    : stub_(AcquisitionService::NewStub(channel)) {}

std::pair<u_int64_t, u_int64_t> AcquisitionClient::get_raw_per_channel() {
  ClientContext context;
  GetProgressRequest request;
  GetProgressResponse response;
  Status status = stub_->get_progress(&context, request, &response);
  if (status.ok()) {
    return std::make_pair(response.raw_per_channel().acquired(),
                          response.raw_per_channel().processed());
  } else {
    std::cout << "AcquisitionClient error: " << status.error_message()
              << std::endl;
    return std::make_pair(0, 0);
  }
}