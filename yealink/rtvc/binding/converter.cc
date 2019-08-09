#include "yealink/rtvc/binding/converter.h"

namespace mate {

v8::Local<v8::Value> Converter<yealink::rtvc::DeviceType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::DeviceType val) {
  std::string device_type;
  switch (val) {
    case yealink::rtvc::DeviceType::kAudioInput:
      device_type = "kAudioInput";
      break;
    case yealink::rtvc::DeviceType::kAudioOutput:
      device_type = "kAudioOutput";
      break;
    case yealink::rtvc::DeviceType::kVideoInput:
      device_type = "kVideoInput";
      break;
    case yealink::rtvc::DeviceType::kScreen:
      device_type = "kScreen";
      break;
    case yealink::rtvc::DeviceType::kWindow:
      device_type = "kWindow";
      break;
    case yealink::rtvc::DeviceType::kImageFile:
      device_type = "kImageFile";
      break;
  }
  return ConvertToV8(isolate, device_type);
}

bool Converter<yealink::rtvc::DeviceType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DeviceType* out) {
  std::string device_type;
  if (!ConvertFromV8(isolate, val, &device_type))
    return false;

  if (device_type == "kAudioInput")
    *out = yealink::rtvc::DeviceType::kAudioInput;
  else if (device_type == "kAudioOutput")
    *out = yealink::rtvc::DeviceType::kAudioOutput;
  else if (device_type == "kAudioOutput")
    *out = yealink::rtvc::DeviceType::kAudioOutput;
  else if (device_type == "kVideoInput")
    *out = yealink::rtvc::DeviceType::kVideoInput;
  else if (device_type == "kScreen")
    *out = yealink::rtvc::DeviceType::kScreen;
  else if (device_type == "kWindow")
    *out = yealink::rtvc::DeviceType::kWindow;
  else if (device_type == "kImageFile")
    *out = yealink::rtvc::DeviceType::kImageFile;
  else
    return false;

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::Device>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::Device& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("deviceId", val.deviceId);
  dict.Set("label", val.label);
  dict.Set("type", val.type);
  return dict.GetHandle();
}

bool Converter<yealink::rtvc::Device>::FromV8(v8::Isolate* isolate,
                                              v8::Local<v8::Value> val,
                                              yealink::rtvc::Device* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("deviceId", &(out->deviceId));
  dict.Get("label", &(out->label));
  dict.Get("type", &(out->type));
  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::VideoFrameBuffer::Type>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::VideoFrameBuffer::Type val) {
  std::string buffer_type;
  switch (val) {
    case yealink::rtvc::VideoFrameBuffer::Type::kI010:
      buffer_type = "kI010";
      break;
    case yealink::rtvc::VideoFrameBuffer::Type::kI420:
      buffer_type = "kI420";
      break;
    case yealink::rtvc::VideoFrameBuffer::Type::kI420A:
      buffer_type = "kI420A";
      break;
    case yealink::rtvc::VideoFrameBuffer::Type::kI444:
      buffer_type = "kI444";
      break;
    case yealink::rtvc::VideoFrameBuffer::Type::kNative:
      buffer_type = "kNative";
      break;
  }
  return ConvertToV8(isolate, buffer_type);
}

bool Converter<yealink::rtvc::VideoFrameBuffer::Type>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::VideoFrameBuffer::Type* out) {
  std::string buffer_type;
  if (!ConvertFromV8(isolate, val, &buffer_type))
    return false;

  if (buffer_type == "kI010")
    *out = yealink::rtvc::VideoFrameBuffer::Type::kI010;
  else if (buffer_type == "kI420")
    *out = yealink::rtvc::VideoFrameBuffer::Type::kI420;
  else if (buffer_type == "kI420A")
    *out = yealink::rtvc::VideoFrameBuffer::Type::kI420A;
  else if (buffer_type == "kI444")
    *out = yealink::rtvc::VideoFrameBuffer::Type::kI444;
  else if (buffer_type == "kNative")
    *out = yealink::rtvc::VideoFrameBuffer::Type::kNative;
  else
    return false;

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::VideoRotation>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::VideoRotation val) {
  std::string rotation;
  switch (val) {
    case yealink::rtvc::VideoRotation::kVideoRotation_0:
      rotation = "kVideoRotation_0";
      break;
    case yealink::rtvc::VideoRotation::kVideoRotation_180:
      rotation = "kVideoRotation_180";
      break;
    case yealink::rtvc::VideoRotation::kVideoRotation_270:
      rotation = "kVideoRotation_270";
      break;
    case yealink::rtvc::VideoRotation::kVideoRotation_90:
      rotation = "kVideoRotation_90";
      break;
    default:
      rotation = "kVideoRotation_0";
      break;
  }
  return ConvertToV8(isolate, rotation);
}

bool Converter<yealink::rtvc::VideoRotation>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::VideoRotation* out) {
  std::string buffer_type;
  if (!ConvertFromV8(isolate, val, &buffer_type))
    return false;

  if (buffer_type == "kVideoRotation_0")
    *out = yealink::rtvc::VideoRotation::kVideoRotation_0;
  else if (buffer_type == "kVideoRotation_180")
    *out = yealink::rtvc::VideoRotation::kVideoRotation_180;
  else if (buffer_type == "kVideoRotation_270")
    *out = yealink::rtvc::VideoRotation::kVideoRotation_270;
  else if (buffer_type == "kVideoRotation_90")
    *out = yealink::rtvc::VideoRotation::kVideoRotation_90;
  else
    return false;

  return true;
}

// static
v8::Local<v8::Value> Converter<yealink::rtvc::AccountInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::AccountInfo& val) {
  Dictionary enterprise = Dictionary::CreateEmpty(isolate);
  enterprise.Set("area", val.enterprise.area);
  enterprise.Set("country", val.enterprise.country);
  enterprise.Set("domain", val.enterprise.domain);
  enterprise.Set("frozen", val.enterprise.frozen);
  enterprise.Set("name", val.enterprise.name);
  enterprise.Set("number", val.enterprise.number);
  enterprise.Set("realm", val.enterprise.realm);
  enterprise.Set("slot", val.enterprise.slot);
  enterprise.Set("status", val.enterprise.status);
  enterprise.Set("subtype", val.enterprise.subtype);
  enterprise.Set("uid", val.enterprise.uid);
  enterprise.Set("zone", val.enterprise.zone);

  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("enterprise", enterprise);
  dict.Set("uid", val.uid);
  dict.Set("number", val.number);
  dict.Set("fullNumber", val.full_number);
  dict.Set("name", val.name);
  dict.Set("namePinyin", val.name_pinyin);
  dict.Set("groupInfo", val.group_info);
  dict.Set("token", val.token);
  dict.Set("type", val.type);
  dict.Set("meetnow", val.meetnow);

  return dict.GetHandle();
}

}  // namespace mate
