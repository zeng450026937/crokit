#ifndef YEALINK_RTVC_BINDING_CONVERTER_H_
#define YEALINK_RTVC_BINDING_CONVERTER_H_

#include "base/optional.h"
#include "yealink/native_mate/converter.h"
#include "yealink/native_mate/dictionary.h"
#include "yealink/rtvc/api/device_type.h"
#include "yealink/rtvc/api/video/video_frame_buffer.h"
#include "yealink/rtvc/api/video/video_rotation.h"
#include "yealink/rtvc/api/video/video_sink.h"
#include "yealink/rtvc/api/video/video_source.h"

namespace mate {

template <typename Type1, typename Type2>
struct Converter<std::pair<Type1, Type2>> {
  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     std::pair<Type1, Type2>* out) {
    if (!val->IsArray())
      return false;

    v8::Local<v8::Array> array(v8::Local<v8::Array>::Cast(val));
    if (array->Length() != 2)
      return false;

    auto context = isolate->GetCurrentContext();
    return Converter<Type1>::FromV8(
               isolate, array->Get(context, 0).ToLocalChecked(), &out->first) &&
           Converter<Type2>::FromV8(
               isolate, array->Get(context, 1).ToLocalChecked(), &out->second);
  }
};

template <typename T>
struct Converter<base::Optional<T>> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const base::Optional<T>& val) {
    if (!val.has_value())
      return v8::Null(isolate);
    return ConvertToV8(isolate, val.value());
  }

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     base::Optional<T>* out) {
    T dict;
    if (!ConvertFromV8(isolate, val, &dict))
      *out = base::nullopt;
    else
      *out = base::Optional<T>(dict);
    return true;
  }
};

template <>
struct Converter<yealink::rtvc::DeviceType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
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

  static bool FromV8(v8::Isolate* isolate,
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
};

template <>
struct Converter<yealink::rtvc::Device> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::Device& val) {
    Dictionary dict = Dictionary::CreateEmpty(isolate);
    dict.Set("deviceId", val.deviceId);
    dict.Set("label", val.label);
    dict.Set("type", val.type);
    return dict.GetHandle();
  }

  static bool FromV8(v8::Isolate* isolate,
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
};

template <>
struct Converter<yealink::rtvc::VideoFrameBuffer::Type> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
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

  static bool FromV8(v8::Isolate* isolate,
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
};

template <>
struct Converter<yealink::rtvc::VideoRotation> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
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

  static bool FromV8(v8::Isolate* isolate,
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
};

}  // namespace mate

#endif  // YEALINK_RTVC_BINDING_CONVERTER_H_
