#pragma once

#ifndef ACQUISITION_CLIENT_H
#define ACQUISITION_CLIENT_H

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

namespace Acquisition {
class AcquisitionClient {
 public:
  AcquisitionClient(std::shared_ptr<Channel> channel);
  std::pair<u_int64_t, u_int64_t> get_raw_per_channel();

 private:
  std::unique_ptr<AcquisitionService::Stub> stub_;
};
}  // namespace Acquisition

#endif