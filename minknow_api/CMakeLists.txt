# Copyright 2018 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# cmake build file for C++ route_guide example.
# Assumes protobuf and gRPC have been installed using cmake.
# See cmake_externalproject/CMakeLists.txt for all-in-one cmake build
# that automatically builds all the dependencies before building route_guide.

cmake_minimum_required(VERSION 3.5.1)

project(MinknowAPI CXX)

include(../cmake/common.cmake)

set(CMAKE_CXX_STANDARD 20)

# Protos file
get_filename_component(man_proto "../../proto/minknow_api/manager.proto" ABSOLUTE)
get_filename_component(rpc_proto "../../proto/minknow_api/rpc_options.proto" ABSOLUTE)
get_filename_component(analysis_proto "../../proto/minknow_api/analysis_configuration.proto" ABSOLUTE)
get_filename_component(base_proto "../../proto/minknow_api/basecaller.proto" ABSOLUTE)
get_filename_component(settings_proto "../../proto/minknow_api/protocol_settings.proto" ABSOLUTE)
get_filename_component(protocol_proto "../../proto/minknow_api/protocol.proto" ABSOLUTE)
get_filename_component(acq_proto "../../proto/minknow_api/acquisition.proto" ABSOLUTE)
get_filename_component(device_proto "../../proto/minknow_api/device.proto" ABSOLUTE)
get_filename_component(instance_proto "../../proto/minknow_api/instance.proto" ABSOLUTE)
get_filename_component(data_proto "../../proto/minknow_api/data.proto" ABSOLUTE)

# This command gets the parent directory, protoc only compiles based off parent directories
get_filename_component(rg_proto_path "/Users/brianzhang/Documents/grpc/examples/proto/minknow_api" PATH)

# Generated server/client code, .pb.X is client and .grpc.pb.X is server
set(man_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/manager.pb.cc")
set(man_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/manager.pb.h")
set(man_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/manager.grpc.pb.cc")
set(man_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/manager.grpc.pb.h")
set(rpc_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/rpc_options.pb.cc")
set(rpc_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/rpc_options.pb.h")
set(rpc_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/rpc_options.grpc.pb.cc")
set(rpc_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/rpc_options.grpc.pb.h")
set(analysis_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/analysis_configuration.pb.cc")
set(analysis_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/analysis_configuration.pb.h")
set(analysis_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/analysis_configuration.grpc.pb.cc")
set(analysis_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/analysis_configuration.grpc.pb.h")
set(settings_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/protocol_settings.pb.cc")
set(settings_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/protocol_settings.pb.h")
set(settings_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/protocol_settings.grpc.pb.cc")
set(settings_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/protocol_settings.grpc.pb.h")
set(protocol_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/protocol.pb.cc")
set(protocol_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/protocol.pb.h")
set(protocol_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/protocol.grpc.pb.cc")
set(protocol_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/protocol.grpc.pb.h")
set(base_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/basecaller.pb.cc")
set(base_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/basecaller.pb.h")
set(base_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/basecaller.grpc.pb.cc")
set(base_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/basecaller.grpc.pb.h")
set(acq_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/acquisition.pb.cc")
set(acq_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/acquisition.pb.h")
set(acq_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/acquisition.grpc.pb.cc")
set(acq_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/acquisition.grpc.pb.h")
set(instance_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/instance.pb.cc")
set(instance_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/instance.pb.h")
set(instance_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/instance.grpc.pb.cc")
set(instance_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/instance.grpc.pb.h")
set(device_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/device.pb.cc")
set(device_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/device.pb.h")
set(device_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/device.grpc.pb.cc")
set(device_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/device.grpc.pb.h")
set(data_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/data.pb.cc")
set(data_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/data.pb.h")
set(data_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/data.grpc.pb.cc")
set(data_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/data.grpc.pb.h")
set(manager_client_hdrs "${CMAKE_CURRENT_BINARY_DIR}/minknow_api/manager_client.h")
# ORDER TO COMPILE BASED ON DEPENDENCY:
# rpc_options
# analysis_configuration
# protocol_settings
# basecaller
# acquisition
# device
# data (this isn't required by manager, but we need it to get live reads)
# protocol
# instance
# manager (file we most care about)

# Using protoc to compile all files, make sure they are compiled in correct order
add_custom_command(
    OUTPUT "${rpc_proto_srcs}" "${rpc_proto_hdrs}" "${rpc_grpc_srcs}" "${rpc_grpc_hdrs}" 
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${rg_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${rpc_proto}" 
    DEPENDS "${rpc_proto}")

add_custom_command(
    OUTPUT "${analysis_proto_srcs}" "${analysis_proto_hdrs}" "${analysis_grpc_srcs}" "${analysis_grpc_hdrs}" 
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${rg_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${analysis_proto}"
    DEPENDS "${rpc_proto}")

SET(settings_deps ${analysis_proto} ${rpc_proto})
add_custom_command(
    OUTPUT "${settings_proto_srcs}" "${settings_proto_hdrs}" "${settings_grpc_srcs}" "${setting_grpc_hdrs}" 
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${rg_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${settings_proto}"
    DEPENDS "${settings_deps}")

SET(base_deps ${analysis_proto} ${settings_proto})
add_custom_command(
    OUTPUT "${base_proto_srcs}" "${base_proto_hdrs}" "${base_grpc_srcs}" "${base_grpc_hdrs}" 
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${rg_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${base_proto}"
    DEPENDS "${base_deps}")

add_custom_command(
    OUTPUT "${acq_proto_srcs}" "${acq_proto_hdrs}" "${acq_grpc_srcs}" "${acq_grpc_hdrs}"
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${rg_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${acq_proto}"
    DEPENDS "${rpc_proto}")  

add_custom_command(
    OUTPUT "${device_proto_srcs}" "${device_proto_hdrs}" "${device_grpc_srcs}" "${device_grpc_hdrs}"
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${rg_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${device_proto}"
    DEPENDS "${rpc_proto}")

SET(data_deps ${device_proto} ${rpc_proto})
add_custom_command(
    OUTPUT "${data_proto_srcs}" "${data_proto_hdrs}" "${data_grpc_srcs}" "${data_grpc_hdrs}"
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${rg_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${data_proto}"
    DEPENDS "${data_deps}")

SET(protocol_deps ${acq_proto} ${base_proto} ${device_proto} ${settings_proto} ${rpc_proto})
add_custom_command(
    OUTPUT "${protocol_proto_srcs}" "${protocol_proto_hdrs}" "${protocol_grpc_srcs}" "${protocol_grpc_hdrs}" "${protocol_proto_srcs}" 
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${rg_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${protocol_proto}"
    DEPENDS "${protocol_deps}")

SET(instance_deps ${acq_proto} ${device_proto} ${protocol_proto})
add_custom_command(
    OUTPUT "${instance_proto_srcs}" "${instance_proto_hdrs}" "${instance_grpc_srcs}" "${instance_grpc_hdrs}" 
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${rg_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${instance_proto}"
    DEPENDS "${instance_deps}")

SET(man_deps ${device_proto} ${instance_proto} ${rpc_proto})
add_custom_command(
    OUTPUT "${man_proto_srcs}" "${man_proto_hdrs}" "${man_grpc_srcs}" "${man_grpc_hdrs}"
    COMMAND ${_PROTOBUF_PROTOC}
    ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${rg_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${man_proto}"
    DEPENDS "${man_deps}")
    
# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# Adding necessary libraries to each output file
add_library(rg_grpc_proto
  ${rpc_grpc_srcs}
  ${rpc_grpc_hdrs}
  ${rpc_proto_srcs}
  ${rpc_proto_hdrs}
  ${analysis_grpc_srcs}
  ${analysis_grpc_hdrs}
  ${analysis_proto_srcs}
  ${analysis_proto_hdrs}
  ${settings_grpc_srcs}
  ${settings_grpc_hdrs}
  ${settings_proto_srcs}
  ${settings_proto_hdrs}
  ${base_grpc_srcs}
  ${base_grpc_hdrs}
  ${base_proto_srcs}
  ${base_proto_hdrs}
  ${acq_grpc_srcs}
  ${acq_grpc_hdrs}
  ${acq_proto_srcs}
  ${acq_proto_hdrs}
  ${device_grpc_srcs}
  ${device_grpc_hdrs}
  ${device_proto_srcs}
  ${device_proto_hdrs}
  ${data_grpc_srcs}
  ${data_grpc_hdrs}
  ${data_proto_srcs}
  ${data_proto_hdrs}
  ${protocol_grpc_srcs}
  ${protocol_grpc_hdrs}
  ${protocol_proto_srcs}
  ${protocol_proto_hdrs}
  ${instance_grpc_srcs}
  ${instance_grpc_hdrs}
  ${instance_proto_srcs}
  ${instance_proto_hdrs}
  ${man_grpc_srcs}
  ${man_grpc_hdrs}
  ${man_proto_srcs}
  ${man_proto_hdrs}
  ${manager_client_hdrs})
target_link_libraries(rg_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# Targets - concrete file for to use generated cpp code. Meant to have written these before compiling, so use stub code if not compiled yet.
# Also make sure you use a main() or else compiler complains
# foreach(_target
#   rpc_options_client 
#   analysis_configuration_client 
#   protocol_settings_client 
#   basecaller_client 
#   acquisition_client
#   device_client
#   data_client
#   protocol_client 
#   instance_client
#   manager_client
#   base)
#   add_executable(${_target}
#     "${_target}.cpp")
#   target_link_libraries(${_target}
#     rg_grpc_proto
#     ${_REFLECTION}
#     ${_GRPC_GRPCPP}
#     ${_PROTOBUF_LIBPROTOBUF})
# endforeach()

add_executable(read_until base.cpp manager_client.cpp data_client.cpp acquisition_client.cpp)
target_link_libraries(read_until
rg_grpc_proto
${_REFLECTION}
${_GRPC_GRPCPP}
${_PROTOBUF_LIBPROTOBUF})