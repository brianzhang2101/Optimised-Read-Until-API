// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: minknow_api/rpc_options.proto

#include "minknow_api/rpc_options.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace minknow_api {
}  // namespace minknow_api
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_minknow_5fapi_2frpc_5foptions_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_minknow_5fapi_2frpc_5foptions_2eproto = nullptr;
const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_minknow_5fapi_2frpc_5foptions_2eproto::offsets[1] = {};
static constexpr ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema* schemas = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::Message* const* file_default_instances = nullptr;

const char descriptor_table_protodef_minknow_5fapi_2frpc_5foptions_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\035minknow_api/rpc_options.proto\022\013minknow"
  "_api\032 google/protobuf/descriptor.proto:5"
  "\n\014rpc_required\022\035.google.protobuf.FieldOp"
  "tions\030\321\206\003 \001(\010:3\n\nrpc_unwrap\022\035.google.pro"
  "tobuf.FieldOptions\030\322\206\003 \001(\010:6\n\014experiment"
  "al\022\036.google.protobuf.MethodOptions\030\323\206\003 \001"
  "(\010B&\n\034com.nanoporetech.minknow_api\242\002\005MKA"
  "PIb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_minknow_5fapi_2frpc_5foptions_2eproto_deps[1] = {
  &::descriptor_table_google_2fprotobuf_2fdescriptor_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_minknow_5fapi_2frpc_5foptions_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_minknow_5fapi_2frpc_5foptions_2eproto = {
  false, false, 290, descriptor_table_protodef_minknow_5fapi_2frpc_5foptions_2eproto, "minknow_api/rpc_options.proto", 
  &descriptor_table_minknow_5fapi_2frpc_5foptions_2eproto_once, descriptor_table_minknow_5fapi_2frpc_5foptions_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_minknow_5fapi_2frpc_5foptions_2eproto::offsets,
  nullptr, file_level_enum_descriptors_minknow_5fapi_2frpc_5foptions_2eproto, file_level_service_descriptors_minknow_5fapi_2frpc_5foptions_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_minknow_5fapi_2frpc_5foptions_2eproto_getter() {
  return &descriptor_table_minknow_5fapi_2frpc_5foptions_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_minknow_5fapi_2frpc_5foptions_2eproto(&descriptor_table_minknow_5fapi_2frpc_5foptions_2eproto);
namespace minknow_api {
PROTOBUF_ATTRIBUTE_INIT_PRIORITY ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::PROTOBUF_NAMESPACE_ID::internal::PrimitiveTypeTraits< bool >, 8, false >
  rpc_required(kRpcRequiredFieldNumber, false);
PROTOBUF_ATTRIBUTE_INIT_PRIORITY ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier< ::google::protobuf::FieldOptions,
    ::PROTOBUF_NAMESPACE_ID::internal::PrimitiveTypeTraits< bool >, 8, false >
  rpc_unwrap(kRpcUnwrapFieldNumber, false);
PROTOBUF_ATTRIBUTE_INIT_PRIORITY ::PROTOBUF_NAMESPACE_ID::internal::ExtensionIdentifier< ::google::protobuf::MethodOptions,
    ::PROTOBUF_NAMESPACE_ID::internal::PrimitiveTypeTraits< bool >, 8, false >
  experimental(kExperimentalFieldNumber, false);

// @@protoc_insertion_point(namespace_scope)
}  // namespace minknow_api
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
