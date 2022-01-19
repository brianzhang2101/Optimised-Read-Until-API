#pragma once

#ifndef MANAGER_CLIENT_H
#define MANAGER_CLIENT_H

#include <grpcpp/grpcpp.h>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <string>
#include <memory>

#include "minknow_api/manager.grpc.pb.h"
#include "minknow_api/data_client.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientReader;
using minknow_api::manager::ManagerService;
using minknow_api::manager::FlowCellPositionsRequest;
using minknow_api::manager::FlowCellPositionsResponse;
using Data::DataClient;

namespace Manager {
  class ManagerClient {
    public:
      ManagerClient(std::shared_ptr<Channel> channel);
      void flow_cell_positions();
    private:
      std::unique_ptr<ManagerService::Stub> stub_;
  };
}

#endif