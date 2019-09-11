#ifndef YEALINK_RTVC_BINDING_CONVERTER_H_
#define YEALINK_RTVC_BINDING_CONVERTER_H_

#include "base/optional.h"
#include "yealink/native_mate/converter.h"
#include "yealink/native_mate/dictionary.h"
#include "yealink/rtvc/api/account_info.h"
#include "yealink/rtvc/api/audio_manager.h"
#include "yealink/rtvc/api/channel.h"
#include "yealink/rtvc/api/conference_desc.h"
#include "yealink/rtvc/api/conference_state.h"
#include "yealink/rtvc/api/conference_user.h"
#include "yealink/rtvc/api/conference_view.h"
#include "yealink/rtvc/api/conference.h"
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
struct Converter<yealink::rtvc::AudioMode> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::AudioMode val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::AudioMode* out);
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

// description
template <>
struct Converter<yealink::rtvc::DescProfile> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::DescProfile val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescProfile* out);
};

template <>
struct Converter<yealink::rtvc::DescPosition> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::DescPosition val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescPosition* out);
};
template <>
struct Converter<yealink::rtvc::DescBanner> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::DescBanner& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescBanner* out);
};

template <>
struct Converter<yealink::rtvc::DescRtmpSessionType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::DescRtmpSessionType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescRtmpSessionType* out);
};
template <>
struct Converter<yealink::rtvc::DescRtmpFsType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::DescRtmpFsType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescRtmpFsType* out);
};
template <>
struct Converter<yealink::rtvc::DescDefaultRtmp> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::DescDefaultRtmp& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescDefaultRtmp* out);
};

template <>
struct Converter<yealink::rtvc::DescUriPurpose> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::DescUriPurpose val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescUriPurpose* out);
};

template <>
struct Converter<yealink::rtvc::DescConfUriInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::DescConfUriInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescConfUriInfo* out);
};

template <>
struct Converter<yealink::rtvc::DescOrganizerInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::DescOrganizerInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescOrganizerInfo* out);
};

template <>
struct Converter<yealink::rtvc::DescConferenceType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::DescConferenceType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescConferenceType* out);
};

template <>
struct Converter<yealink::rtvc::DescNumberType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::DescNumberType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescNumberType* out);
};

template <>
struct Converter<yealink::rtvc::DescAdmissionPolicy> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::DescAdmissionPolicy val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescAdmissionPolicy* out);
};

template <>
struct Converter<yealink::rtvc::DescAttendeeByPass> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::DescAttendeeByPass val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescAttendeeByPass* out);
};

template <>
struct Converter<yealink::rtvc::DescAutoPromote> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::DescAutoPromote val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescAutoPromote* out);
};

template <>
struct Converter<yealink::rtvc::DescRecordType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::DescRecordType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescRecordType* out);
};

template <>
struct Converter<yealink::rtvc::DescRecordPrivilege> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::DescRecordPrivilege val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescRecordPrivilege* out);
};

template <>
struct Converter<yealink::rtvc::DescSetLockInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::DescSetLockInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescSetLockInfo* out);
};

template <>
struct Converter<yealink::rtvc::DescGetLockInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::DescGetLockInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescGetLockInfo* out);
};

template <>
struct Converter<yealink::rtvc::DescInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::DescInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::DescInfo* out);
};

// state

// user
template <>
struct Converter<yealink::rtvc::RequesrResult> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::RequesrResult val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::RequesrResult* out);
};

template <>
struct Converter<yealink::rtvc::ResponseInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::ResponseInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ResponseInfo* out);
};

template <>
struct Converter<yealink::rtvc::UserProtocolType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::UserProtocolType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UserProtocolType* out);
};

template <>
struct Converter<yealink::rtvc::UserPermissionType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::UserPermissionType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UserPermissionType* out);
};

template <>
struct Converter<yealink::rtvc::UserDemoStateType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::UserDemoStateType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UserDemoStateType* out);
};

template <>
struct Converter<yealink::rtvc::PresenterDemoStateType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::PresenterDemoStateType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::PresenterDemoStateType* out);
};

template <>
struct Converter<yealink::rtvc::UserRolesInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::UserRolesInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UserRolesInfo* out);
};

template <>
struct Converter<yealink::rtvc::UserEndpointSeesionType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::UserEndpointSeesionType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UserEndpointSeesionType* out);
};

template <>
struct Converter<yealink::rtvc::UserEndpointStatusType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::UserEndpointStatusType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UserEndpointStatusType* out);
};

template <>
struct Converter<yealink::rtvc::UserJoinMethod> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::UserJoinMethod val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UserJoinMethod* out);
};

template <>
struct Converter<yealink::rtvc::UserMediaType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::UserMediaType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UserMediaType* out);
};

template <>
struct Converter<yealink::rtvc::UserMediaLabelType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::UserMediaLabelType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UserMediaLabelType* out);
};

template <>
struct Converter<yealink::rtvc::UserMediaDirectionType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::UserMediaDirectionType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UserMediaDirectionType* out);
};

template <>
struct Converter<yealink::rtvc::UserMediafilterType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::UserMediafilterType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UserMediafilterType* out);
};

template <>
struct Converter<yealink::rtvc::UserMediaBlockByType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::UserMediaBlockByType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UserMediaBlockByType* out);
};

template <>
struct Converter<yealink::rtvc::UserMediaInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::UserMediaInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UserMediaInfo* out);
};

template <>
struct Converter<yealink::rtvc::UserMediaFilterInfo> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      const yealink::rtvc::UserMediaFilterInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UserMediaFilterInfo* out);
};

template <>
struct Converter<yealink::rtvc::UserEndpointInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::UserEndpointInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UserEndpointInfo* out);
};

template <>
struct Converter<yealink::rtvc::UserInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::UserInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UserInfo* out);
};

template <>
struct Converter<yealink::rtvc::UserMediaDataInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::UserMediaDataInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UserMediaDataInfo* out);
};

template <>
struct Converter<yealink::rtvc::UserStatisticsInfo> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      const yealink::rtvc::UserStatisticsInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::UserStatisticsInfo* out);
};

// view
template <>
struct Converter<yealink::rtvc::ViewSpeakMode> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::ViewSpeakMode val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ViewSpeakMode* out);
};

template <>
struct Converter<yealink::rtvc::ViewLayoutType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::ViewLayoutType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ViewLayoutType* out);
};

template <>
struct Converter<yealink::rtvc::ViewPresenterLayoutType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::ViewPresenterLayoutType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ViewPresenterLayoutType* out);
};

template <>
struct Converter<yealink::rtvc::GetLayoutInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::GetLayoutInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::GetLayoutInfo* out);
};

template <>
struct Converter<yealink::rtvc::SetLayoutInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::SetLayoutInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::SetLayoutInfo* out);
};

template <>
struct Converter<yealink::rtvc::ViewFilterRoleType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::ViewFilterRoleType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ViewFilterRoleType* out);
};

template <>
struct Converter<yealink::rtvc::ViewFilterType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::ViewFilterType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ViewFilterType* out);
};

template <>
struct Converter<yealink::rtvc::ViewFilterRuleInfo> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      const yealink::rtvc::ViewFilterRuleInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ViewFilterRuleInfo* out);
};

template <>
struct Converter<yealink::rtvc::StatsAudioCodecType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::StatsAudioCodecType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::StatsAudioCodecType* out);
};

template <>
struct Converter<yealink::rtvc::StatsVideoCodecType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::StatsVideoCodecType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::StatsVideoCodecType* out);
};

template <>
struct Converter<yealink::rtvc::StatsVideoProfileType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   yealink::rtvc::StatsVideoProfileType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::StatsVideoProfileType* out);
};

template <>
struct Converter<yealink::rtvc::AudioStatsInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::AudioStatsInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::AudioStatsInfo* out);
};

template <>
struct Converter<yealink::rtvc::VideoStatsInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::VideoStatsInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::VideoStatsInfo* out);
};

template <>
struct Converter<yealink::rtvc::RTCVideoStats> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::RTCVideoStats& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::RTCVideoStats* out);
};

template <>
struct Converter<yealink::rtvc::RTCAudioStats> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::RTCAudioStats& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::RTCAudioStats* out);
};

template <>
struct Converter<yealink::rtvc::RTCStats> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::RTCStats& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::RTCStats* out);
};

}  // namespace mate

#endif  // YEALINK_RTVC_BINDING_CONVERTER_H_
