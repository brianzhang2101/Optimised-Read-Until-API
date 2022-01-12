#include <grpcpp/grpcpp.h>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <string>
#include <thread>

#include "minknow_api/data.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using minknow_api::data::DataService;
using minknow_api::data::GetLiveReadsRequest;
using minknow_api::data::GetLiveReadsResponse;
using minknow_api::data::GetLiveReadsRequest_StreamSetup;
using minknow_api::data::GetLiveReadsRequest_RawDataType;
using minknow_api::data::GetDataTypesRequest;
using minknow_api::data::GetDataTypesResponse;

GetLiveReadsRequest_StreamSetup MakeSetup(u_int32_t first_channel, u_int32_t last_channel, u_int64_t sample_minimum_chunk_size) {
  GetLiveReadsRequest_StreamSetup setup;
  setup.set_first_channel(first_channel);
  setup.set_last_channel(last_channel);
  setup.set_raw_data_type(GetLiveReadsRequest_RawDataType::GetLiveReadsRequest_RawDataType_CALIBRATED);
  setup.set_sample_minimum_chunk_size(sample_minimum_chunk_size);
  return setup;
}

GetLiveReadsRequest MakeRequest() {
  GetLiveReadsRequest result;
  result.mutable_setup()->CopyFrom(MakeSetup(1, 512, 1));
  return result;
}

class DataClient {
  public:
    ClientContext context;
    std::shared_ptr<ClientReaderWriter<GetLiveReadsRequest, GetLiveReadsResponse> > stream;

  public:
    DataClient(std::shared_ptr<Channel> channel) : stub_(DataService::NewStub(channel)) {}

  void GetLiveReads() {
      std::cout << "Getting live reads from MinKNOW..." << std::endl;
      stream = stub_->get_live_reads(&context);
      // Setup the connection and listen for actions
      std::thread writer([stream]() {
        stream->Write(MakeRequest());
        // std::vector<GetLiveReadsRequest> requests{MakeRequest()};
        // for (const GetLiveReadsRequest& req : requests) {
        //   std::cout << "Sending smth" << std::endl;
        //   stream->Write(req);
        // }
        stream->WritesDone();

        // TODO: Listen for incoming actions
      });

      GetLiveReadsResponse response;
      while(stream->Read(&response)) {
        std::cout << response.samples_since_start() << std::endl;
      }
      Status status = stream->Finish();
      writer.join();
      if(status.ok()) {
        std::cout << "Finished successfully!" << std::endl;
      } else {
        std::cout << "Failed: " << status.error_message() << std::endl;
      }
  }
  void GetDataTypes() {
    GetDataTypesRequest request;
    GetDataTypesResponse response;
    ClientContext context;
    Status status = stub_->get_data_types(&context, request, &response);
    if(status.ok()) {
      std::cout << response.calibrated_signal().size() << std::endl;
    } else {
      std::cout << status.error_code() << std::endl;
    }
  }
  private:
    std::unique_ptr<DataService::Stub> stub_;
};

int main(int argc, char* argv[]) {
  std::cout << "Connecting to MinKNOW API...\n";
  DataClient client(
      grpc::CreateChannel("127.0.0.1:8000",
                          grpc::InsecureChannelCredentials()));
  client.GetLiveReads();
  return 0;
}