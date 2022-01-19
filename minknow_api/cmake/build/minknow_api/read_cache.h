#pragma once

#ifndef READ_CACHE_H
#define READ_CACHE_H

#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "minknow_api/data_client.h"

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
using minknow_api::data::GetLiveReadsResponse_ReadData;

class ReadCache {
 public:
  ReadCache() {}
  GetLiveReadsResponse_ReadData get_item(u_int32_t channel);
  void set_item(u_int32_t channel, GetLiveReadsResponse_ReadData data);

 private:
  std::unordered_map<uint32_t, GetLiveReadsResponse_ReadData> dict;
  std::queue<u_int32_t> insertion_order;
  int size;
  int missed;
  int replaced;
};

#endif