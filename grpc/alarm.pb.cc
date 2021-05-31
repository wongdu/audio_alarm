// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: alarm.proto

#include "alarm.pb.h"

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
namespace audioalarm {
namespace v1 {
constexpr AlarmRequest::AlarmRequest(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : dev_ip_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , user_name_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , password_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , download_url_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , file_name_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , md5_value_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , msg_id_(0u)
  , camera_type_(0)

  , dev_port_(0u)
  , play_duration_(0u){}
struct AlarmRequestDefaultTypeInternal {
  constexpr AlarmRequestDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~AlarmRequestDefaultTypeInternal() {}
  union {
    AlarmRequest _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT AlarmRequestDefaultTypeInternal _AlarmRequest_default_instance_;
constexpr AlarmReply::AlarmReply(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : message_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , code_(0)
{}
struct AlarmReplyDefaultTypeInternal {
  constexpr AlarmReplyDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~AlarmReplyDefaultTypeInternal() {}
  union {
    AlarmReply _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT AlarmReplyDefaultTypeInternal _AlarmReply_default_instance_;
}  // namespace v1
}  // namespace audioalarm
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_alarm_2eproto[2];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_alarm_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_alarm_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_alarm_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::audioalarm::v1::AlarmRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::audioalarm::v1::AlarmRequest, msg_id_),
  PROTOBUF_FIELD_OFFSET(::audioalarm::v1::AlarmRequest, camera_type_),
  PROTOBUF_FIELD_OFFSET(::audioalarm::v1::AlarmRequest, dev_ip_),
  PROTOBUF_FIELD_OFFSET(::audioalarm::v1::AlarmRequest, dev_port_),
  PROTOBUF_FIELD_OFFSET(::audioalarm::v1::AlarmRequest, user_name_),
  PROTOBUF_FIELD_OFFSET(::audioalarm::v1::AlarmRequest, password_),
  PROTOBUF_FIELD_OFFSET(::audioalarm::v1::AlarmRequest, download_url_),
  PROTOBUF_FIELD_OFFSET(::audioalarm::v1::AlarmRequest, file_name_),
  PROTOBUF_FIELD_OFFSET(::audioalarm::v1::AlarmRequest, md5_value_),
  PROTOBUF_FIELD_OFFSET(::audioalarm::v1::AlarmRequest, play_duration_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::audioalarm::v1::AlarmReply, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::audioalarm::v1::AlarmReply, code_),
  PROTOBUF_FIELD_OFFSET(::audioalarm::v1::AlarmReply, message_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::audioalarm::v1::AlarmRequest)},
  { 15, -1, sizeof(::audioalarm::v1::AlarmReply)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::audioalarm::v1::_AlarmRequest_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::audioalarm::v1::_AlarmReply_default_instance_),
};

const char descriptor_table_protodef_alarm_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\013alarm.proto\022\raudioalarm.v1\"\350\001\n\014AlarmRe"
  "quest\022\016\n\006msg_id\030\001 \001(\r\022.\n\013camera_type\030\002 \001"
  "(\0162\031.audioalarm.v1.CameraType\022\016\n\006dev_ip\030"
  "\003 \001(\t\022\020\n\010dev_port\030\004 \001(\r\022\021\n\tuser_name\030\005 \001"
  "(\t\022\020\n\010password\030\006 \001(\t\022\024\n\014download_url\030\007 \001"
  "(\t\022\021\n\tfile_name\030\010 \001(\t\022\021\n\tmd5_value\030\t \001(\t"
  "\022\025\n\rplay_duration\030\n \001(\r\"H\n\nAlarmReply\022)\n"
  "\004code\030\001 \001(\0162\033.audioalarm.v1.ResponseCode"
  "\022\017\n\007message\030\002 \001(\t*-\n\nCameraType\022\013\n\007Unkno"
  "wn\020\000\022\t\n\005DaHua\020\001\022\007\n\003HiK\020\002*\274\001\n\014ResponseCod"
  "e\022\n\n\006Ok_200\020\000\022\032\n\026Err_Camera_Unsupported\020"
  "\001\022\030\n\024Err_Device_Not_Found\020\002\022\037\n\033Err_Devic"
  "e_Login_Incomplete\020\003\022\035\n\031Err_Audio_File_I"
  "ncomplete\020\004\022\035\n\031Err_Play_Duration_Not_Set"
  "\020\005\022\013\n\007Err_500\020\0062[\n\014AlarmService\022K\n\017SetAl"
  "armMessage\022\033.audioalarm.v1.AlarmRequest\032"
  "\031.audioalarm.v1.AlarmReply\"\000b\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_alarm_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_alarm_2eproto = {
  false, false, 676, descriptor_table_protodef_alarm_2eproto, "alarm.proto", 
  &descriptor_table_alarm_2eproto_once, nullptr, 0, 2,
  schemas, file_default_instances, TableStruct_alarm_2eproto::offsets,
  file_level_metadata_alarm_2eproto, file_level_enum_descriptors_alarm_2eproto, file_level_service_descriptors_alarm_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK ::PROTOBUF_NAMESPACE_ID::Metadata
descriptor_table_alarm_2eproto_metadata_getter(int index) {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_alarm_2eproto);
  return descriptor_table_alarm_2eproto.file_level_metadata[index];
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_alarm_2eproto(&descriptor_table_alarm_2eproto);
namespace audioalarm {
namespace v1 {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* CameraType_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_alarm_2eproto);
  return file_level_enum_descriptors_alarm_2eproto[0];
}
bool CameraType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
      return true;
    default:
      return false;
  }
}

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ResponseCode_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_alarm_2eproto);
  return file_level_enum_descriptors_alarm_2eproto[1];
}
bool ResponseCode_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      return true;
    default:
      return false;
  }
}


// ===================================================================

class AlarmRequest::_Internal {
 public:
};

AlarmRequest::AlarmRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:audioalarm.v1.AlarmRequest)
}
AlarmRequest::AlarmRequest(const AlarmRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  dev_ip_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_dev_ip().empty()) {
    dev_ip_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_dev_ip(), 
      GetArena());
  }
  user_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_user_name().empty()) {
    user_name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_user_name(), 
      GetArena());
  }
  password_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_password().empty()) {
    password_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_password(), 
      GetArena());
  }
  download_url_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_download_url().empty()) {
    download_url_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_download_url(), 
      GetArena());
  }
  file_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_file_name().empty()) {
    file_name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_file_name(), 
      GetArena());
  }
  md5_value_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_md5_value().empty()) {
    md5_value_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_md5_value(), 
      GetArena());
  }
  ::memcpy(&msg_id_, &from.msg_id_,
    static_cast<size_t>(reinterpret_cast<char*>(&play_duration_) -
    reinterpret_cast<char*>(&msg_id_)) + sizeof(play_duration_));
  // @@protoc_insertion_point(copy_constructor:audioalarm.v1.AlarmRequest)
}

void AlarmRequest::SharedCtor() {
dev_ip_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
user_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
password_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
download_url_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
file_name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
md5_value_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&msg_id_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&play_duration_) -
    reinterpret_cast<char*>(&msg_id_)) + sizeof(play_duration_));
}

AlarmRequest::~AlarmRequest() {
  // @@protoc_insertion_point(destructor:audioalarm.v1.AlarmRequest)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void AlarmRequest::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  dev_ip_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  user_name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  password_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  download_url_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  file_name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  md5_value_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void AlarmRequest::ArenaDtor(void* object) {
  AlarmRequest* _this = reinterpret_cast< AlarmRequest* >(object);
  (void)_this;
}
void AlarmRequest::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void AlarmRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void AlarmRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:audioalarm.v1.AlarmRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  dev_ip_.ClearToEmpty();
  user_name_.ClearToEmpty();
  password_.ClearToEmpty();
  download_url_.ClearToEmpty();
  file_name_.ClearToEmpty();
  md5_value_.ClearToEmpty();
  ::memset(&msg_id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&play_duration_) -
      reinterpret_cast<char*>(&msg_id_)) + sizeof(play_duration_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* AlarmRequest::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // uint32 msg_id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          msg_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // .audioalarm.v1.CameraType camera_type = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_camera_type(static_cast<::audioalarm::v1::CameraType>(val));
        } else goto handle_unusual;
        continue;
      // string dev_ip = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          auto str = _internal_mutable_dev_ip();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "audioalarm.v1.AlarmRequest.dev_ip"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 dev_port = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          dev_port_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string user_name = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 42)) {
          auto str = _internal_mutable_user_name();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "audioalarm.v1.AlarmRequest.user_name"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string password = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 50)) {
          auto str = _internal_mutable_password();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "audioalarm.v1.AlarmRequest.password"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string download_url = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 58)) {
          auto str = _internal_mutable_download_url();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "audioalarm.v1.AlarmRequest.download_url"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string file_name = 8;
      case 8:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 66)) {
          auto str = _internal_mutable_file_name();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "audioalarm.v1.AlarmRequest.file_name"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string md5_value = 9;
      case 9:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 74)) {
          auto str = _internal_mutable_md5_value();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "audioalarm.v1.AlarmRequest.md5_value"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint32 play_duration = 10;
      case 10:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 80)) {
          play_duration_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* AlarmRequest::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:audioalarm.v1.AlarmRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 msg_id = 1;
  if (this->msg_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(1, this->_internal_msg_id(), target);
  }

  // .audioalarm.v1.CameraType camera_type = 2;
  if (this->camera_type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      2, this->_internal_camera_type(), target);
  }

  // string dev_ip = 3;
  if (this->dev_ip().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_dev_ip().data(), static_cast<int>(this->_internal_dev_ip().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "audioalarm.v1.AlarmRequest.dev_ip");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_dev_ip(), target);
  }

  // uint32 dev_port = 4;
  if (this->dev_port() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(4, this->_internal_dev_port(), target);
  }

  // string user_name = 5;
  if (this->user_name().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_user_name().data(), static_cast<int>(this->_internal_user_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "audioalarm.v1.AlarmRequest.user_name");
    target = stream->WriteStringMaybeAliased(
        5, this->_internal_user_name(), target);
  }

  // string password = 6;
  if (this->password().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_password().data(), static_cast<int>(this->_internal_password().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "audioalarm.v1.AlarmRequest.password");
    target = stream->WriteStringMaybeAliased(
        6, this->_internal_password(), target);
  }

  // string download_url = 7;
  if (this->download_url().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_download_url().data(), static_cast<int>(this->_internal_download_url().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "audioalarm.v1.AlarmRequest.download_url");
    target = stream->WriteStringMaybeAliased(
        7, this->_internal_download_url(), target);
  }

  // string file_name = 8;
  if (this->file_name().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_file_name().data(), static_cast<int>(this->_internal_file_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "audioalarm.v1.AlarmRequest.file_name");
    target = stream->WriteStringMaybeAliased(
        8, this->_internal_file_name(), target);
  }

  // string md5_value = 9;
  if (this->md5_value().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_md5_value().data(), static_cast<int>(this->_internal_md5_value().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "audioalarm.v1.AlarmRequest.md5_value");
    target = stream->WriteStringMaybeAliased(
        9, this->_internal_md5_value(), target);
  }

  // uint32 play_duration = 10;
  if (this->play_duration() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(10, this->_internal_play_duration(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:audioalarm.v1.AlarmRequest)
  return target;
}

size_t AlarmRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:audioalarm.v1.AlarmRequest)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string dev_ip = 3;
  if (this->dev_ip().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_dev_ip());
  }

  // string user_name = 5;
  if (this->user_name().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_user_name());
  }

  // string password = 6;
  if (this->password().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_password());
  }

  // string download_url = 7;
  if (this->download_url().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_download_url());
  }

  // string file_name = 8;
  if (this->file_name().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_file_name());
  }

  // string md5_value = 9;
  if (this->md5_value().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_md5_value());
  }

  // uint32 msg_id = 1;
  if (this->msg_id() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_msg_id());
  }

  // .audioalarm.v1.CameraType camera_type = 2;
  if (this->camera_type() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_camera_type());
  }

  // uint32 dev_port = 4;
  if (this->dev_port() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_dev_port());
  }

  // uint32 play_duration = 10;
  if (this->play_duration() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_play_duration());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void AlarmRequest::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:audioalarm.v1.AlarmRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const AlarmRequest* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<AlarmRequest>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:audioalarm.v1.AlarmRequest)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:audioalarm.v1.AlarmRequest)
    MergeFrom(*source);
  }
}

void AlarmRequest::MergeFrom(const AlarmRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:audioalarm.v1.AlarmRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.dev_ip().size() > 0) {
    _internal_set_dev_ip(from._internal_dev_ip());
  }
  if (from.user_name().size() > 0) {
    _internal_set_user_name(from._internal_user_name());
  }
  if (from.password().size() > 0) {
    _internal_set_password(from._internal_password());
  }
  if (from.download_url().size() > 0) {
    _internal_set_download_url(from._internal_download_url());
  }
  if (from.file_name().size() > 0) {
    _internal_set_file_name(from._internal_file_name());
  }
  if (from.md5_value().size() > 0) {
    _internal_set_md5_value(from._internal_md5_value());
  }
  if (from.msg_id() != 0) {
    _internal_set_msg_id(from._internal_msg_id());
  }
  if (from.camera_type() != 0) {
    _internal_set_camera_type(from._internal_camera_type());
  }
  if (from.dev_port() != 0) {
    _internal_set_dev_port(from._internal_dev_port());
  }
  if (from.play_duration() != 0) {
    _internal_set_play_duration(from._internal_play_duration());
  }
}

void AlarmRequest::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:audioalarm.v1.AlarmRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AlarmRequest::CopyFrom(const AlarmRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:audioalarm.v1.AlarmRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AlarmRequest::IsInitialized() const {
  return true;
}

void AlarmRequest::InternalSwap(AlarmRequest* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  dev_ip_.Swap(&other->dev_ip_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  user_name_.Swap(&other->user_name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  password_.Swap(&other->password_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  download_url_.Swap(&other->download_url_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  file_name_.Swap(&other->file_name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  md5_value_.Swap(&other->md5_value_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(AlarmRequest, play_duration_)
      + sizeof(AlarmRequest::play_duration_)
      - PROTOBUF_FIELD_OFFSET(AlarmRequest, msg_id_)>(
          reinterpret_cast<char*>(&msg_id_),
          reinterpret_cast<char*>(&other->msg_id_));
}

::PROTOBUF_NAMESPACE_ID::Metadata AlarmRequest::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

class AlarmReply::_Internal {
 public:
};

AlarmReply::AlarmReply(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:audioalarm.v1.AlarmReply)
}
AlarmReply::AlarmReply(const AlarmReply& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  message_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_message().empty()) {
    message_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_message(), 
      GetArena());
  }
  code_ = from.code_;
  // @@protoc_insertion_point(copy_constructor:audioalarm.v1.AlarmReply)
}

void AlarmReply::SharedCtor() {
message_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
code_ = 0;
}

AlarmReply::~AlarmReply() {
  // @@protoc_insertion_point(destructor:audioalarm.v1.AlarmReply)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void AlarmReply::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  message_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void AlarmReply::ArenaDtor(void* object) {
  AlarmReply* _this = reinterpret_cast< AlarmReply* >(object);
  (void)_this;
}
void AlarmReply::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void AlarmReply::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void AlarmReply::Clear() {
// @@protoc_insertion_point(message_clear_start:audioalarm.v1.AlarmReply)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  message_.ClearToEmpty();
  code_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* AlarmReply::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // .audioalarm.v1.ResponseCode code = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_code(static_cast<::audioalarm::v1::ResponseCode>(val));
        } else goto handle_unusual;
        continue;
      // string message = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_message();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "audioalarm.v1.AlarmReply.message"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* AlarmReply::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:audioalarm.v1.AlarmReply)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .audioalarm.v1.ResponseCode code = 1;
  if (this->code() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_code(), target);
  }

  // string message = 2;
  if (this->message().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_message().data(), static_cast<int>(this->_internal_message().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "audioalarm.v1.AlarmReply.message");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_message(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:audioalarm.v1.AlarmReply)
  return target;
}

size_t AlarmReply::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:audioalarm.v1.AlarmReply)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string message = 2;
  if (this->message().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_message());
  }

  // .audioalarm.v1.ResponseCode code = 1;
  if (this->code() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_code());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void AlarmReply::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:audioalarm.v1.AlarmReply)
  GOOGLE_DCHECK_NE(&from, this);
  const AlarmReply* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<AlarmReply>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:audioalarm.v1.AlarmReply)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:audioalarm.v1.AlarmReply)
    MergeFrom(*source);
  }
}

void AlarmReply::MergeFrom(const AlarmReply& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:audioalarm.v1.AlarmReply)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.message().size() > 0) {
    _internal_set_message(from._internal_message());
  }
  if (from.code() != 0) {
    _internal_set_code(from._internal_code());
  }
}

void AlarmReply::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:audioalarm.v1.AlarmReply)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AlarmReply::CopyFrom(const AlarmReply& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:audioalarm.v1.AlarmReply)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AlarmReply::IsInitialized() const {
  return true;
}

void AlarmReply::InternalSwap(AlarmReply* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  message_.Swap(&other->message_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  swap(code_, other->code_);
}

::PROTOBUF_NAMESPACE_ID::Metadata AlarmReply::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace v1
}  // namespace audioalarm
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::audioalarm::v1::AlarmRequest* Arena::CreateMaybeMessage< ::audioalarm::v1::AlarmRequest >(Arena* arena) {
  return Arena::CreateMessageInternal< ::audioalarm::v1::AlarmRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::audioalarm::v1::AlarmReply* Arena::CreateMaybeMessage< ::audioalarm::v1::AlarmReply >(Arena* arena) {
  return Arena::CreateMessageInternal< ::audioalarm::v1::AlarmReply >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>