#ifndef YEALINK_RTVC_BINDING_CONVERTER_H_
#define YEALINK_RTVC_BINDING_CONVERTER_H_

#include "base/optional.h"
#include "yealink/native_mate/converter.h"
#include "yealink/native_mate/dictionary.h"
#include "yealink/rtvc/api/account_info.h"
#include "yealink/rtvc/api/contact.h"
#include "yealink/rtvc/api/device_type.h"
#include "yealink/rtvc/api/schedule_item.h"
#include "yealink/rtvc/api/video/video_frame_buffer.h"
#include "yealink/rtvc/api/video/video_rotation.h"
#include "yealink/rtvc/api/video/video_sink.h"
#include "yealink/rtvc/api/video/video_source.h"
#include "yealink/rtvc/api/ytms_info.h"

#include "yealink/libvc/include/components/base/simplelib/simple_array.hpp"
#include "yealink/libvc/include/components/base/simplelib/simple_string.hpp"

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
struct Converter<yealink::SStringA> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::SStringA& val) {
    return Converter<base::StringPiece>::ToV8(isolate,
                                              std::string(val.ConstData()));
  }

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::SStringA* out) {
    std::string str;
    Converter<std::string>::FromV8(isolate, val, &str);
    *out = yealink::SStringA(str.c_str());
    return true;
  }
};

template <typename T>
struct Converter<yealink::Array<T>> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::Array<T>& val) {
    v8::Local<v8::Array> result(
        v8::Array::New(isolate, static_cast<int>(val.Size())));
    auto context = isolate->GetCurrentContext();
    for (size_t i = 0; i < val.Size(); ++i) {
      result
          ->Set(context, static_cast<int>(i),
                Converter<T>::ToV8(isolate, val[i]))
          .ToChecked();
    }
    return result;
  }

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::Array<T>* out) {
    if (!val->IsArray())
      return false;

    auto context = isolate->GetCurrentContext();
    yealink::Array<T> result;
    v8::Local<v8::Array> array(v8::Local<v8::Array>::Cast(val));
    uint32_t length = array->Length();
    for (uint32_t i = 0; i < length; ++i) {
      T item;
      if (!Converter<T>::FromV8(isolate,
                                array->Get(context, i).ToLocalChecked(), &item))
        return false;
      out->Append(item);
    }
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

template <>
struct Converter<yealink::rtvc::ScheduleItemProfile> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::ScheduleItemProfile val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ScheduleItemProfile* out);
};

template <>
struct Converter<yealink::rtvc::ScheduleRecurrenceType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::ScheduleRecurrenceType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ScheduleRecurrenceType* out);
};

template <>
struct Converter<yealink::rtvc::ScheduleRecurrenceDailyType> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      yealink::rtvc::ScheduleRecurrenceDailyType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ScheduleRecurrenceDailyType* out);
};

template <>
struct Converter<yealink::rtvc::ScheduleRecurrence> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      const yealink::rtvc::ScheduleRecurrence& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ScheduleRecurrence* out);
};

template <>
struct Converter<yealink::rtvc::ScheduleDaylightStrategy> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      const yealink::rtvc::ScheduleDaylightStrategy& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ScheduleDaylightStrategy* out);
};

template <>
struct Converter<yealink::rtvc::ScheduleTimeZoneRule> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      const yealink::rtvc::ScheduleTimeZoneRule& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ScheduleTimeZoneRule* out);
};

template <>
struct Converter<yealink::rtvc::ScheduleTimeZone> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::ScheduleTimeZone& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ScheduleTimeZone* out);
};

template <>
struct Converter<yealink::rtvc::ScheduleMemberRole> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::ScheduleMemberRole val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ScheduleMemberRole* out);
};

template <>
struct Converter<yealink::rtvc::ScheduleMemberType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::ScheduleMemberType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ScheduleMemberType* out);
};

template <>
struct Converter<yealink::rtvc::ScheduleMember> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::ScheduleMember& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ScheduleMember* out);
};

template <>
struct Converter<yealink::rtvc::ScheduleRoom> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::ScheduleRoom& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ScheduleRoom* out);
};

template <>
struct Converter<yealink::rtvc::ScheduleRTMPLimitType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::ScheduleRTMPLimitType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ScheduleRTMPLimitType* out);
};

template <>
struct Converter<yealink::rtvc::ScheduleRTMP> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::ScheduleRTMP& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ScheduleRTMP* out);
};

template <>
struct Converter<yealink::rtvc::ScheduleItemDetail> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      const yealink::rtvc::ScheduleItemDetail& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ScheduleItemDetail* out);
};

template <>
struct Converter<yealink::rtvc::ContactLoadMode> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::ContactLoadMode val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ContactLoadMode* out);
};

template <>
struct Converter<yealink::rtvc::ContactNodeType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::ContactNodeType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ContactNodeType* out);
};

// template <>
// struct Converter<yealink::rtvc::ContactNode> {
//   static v8::Local<v8::Value> ToV8(
//       v8::Isolate* isolate,
//       const yealink::rtvc::ContactNode& val);

//   static bool FromV8(v8::Isolate* isolate,
//                      v8::Local<v8::Value> val,
//                      yealink::rtvc::ContactNode* out);
// };

template <>
struct Converter<yealink::rtvc::TerminalInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::TerminalInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::TerminalInfo* out);
};

template <>
struct Converter<yealink::rtvc::AlarmInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::AlarmInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::AlarmInfo* out);
};

template <>
struct Converter<yealink::rtvc::FeedbackInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::FeedbackInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::FeedbackInfo* out);
};

template <>
struct Converter<yealink::rtvc::PackageInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::PackageInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::PackageInfo* out);
};

template <>
struct Converter<yealink::rtvc::ConfigurationInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::ConfigurationInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ConfigurationInfo* out);
};

template <>
struct Converter<yealink::rtvc::DownloadInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::DownloadInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DownloadInfo* out);
};

template <>
struct Converter<yealink::rtvc::UploadLogInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::UploadLogInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UploadLogInfo* out);
};

template <>
struct Converter<yealink::rtvc::NetCaptureInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::NetCaptureInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::NetCaptureInfo* out);
};

template <>
struct Converter<yealink::rtvc::EventInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::EventInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::EventInfo* out);
};

}  // namespace mate

#endif  // YEALINK_RTVC_BINDING_CONVERTER_H_
