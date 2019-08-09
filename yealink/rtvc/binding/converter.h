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
#include "yealink/rtvc/api/account_info.h"

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
                                   yealink::rtvc::DeviceType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DeviceType* out);
};

template <>
struct Converter<yealink::rtvc::Device> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::Device& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::Device* out);
};

template <>
struct Converter<yealink::rtvc::VideoFrameBuffer::Type> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::VideoFrameBuffer::Type val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::VideoFrameBuffer::Type* out);
};

template <>
struct Converter<yealink::rtvc::VideoRotation> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::VideoRotation val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::VideoRotation* out);
};

template <>
struct Converter<yealink::rtvc::AccountInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::AccountInfo& val);
};

}  // namespace mate

#endif  // YEALINK_RTVC_BINDING_CONVERTER_H_
