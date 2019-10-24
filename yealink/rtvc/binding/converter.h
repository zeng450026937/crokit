#ifndef YEALINK_RTVC_BINDING_CONVERTER_H_
#define YEALINK_RTVC_BINDING_CONVERTER_H_

#include "base/optional.h"
#include "yealink/native_mate/converter.h"
#include "yealink/native_mate/dictionary.h"
#include "yealink/rtvc/api/account_info.h"
#include "yealink/rtvc/api/audio_manager.h"
#include "yealink/rtvc/api/channel.h"
#include "yealink/rtvc/api/conference.h"
#include "yealink/rtvc/api/conference_desc.h"
#include "yealink/rtvc/api/conference_record.h"
#include "yealink/rtvc/api/conference_rtmp.h"
#include "yealink/rtvc/api/conference_state.h"
#include "yealink/rtvc/api/conference_user.h"
#include "yealink/rtvc/api/conference_view.h"
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
struct Converter<rtvc::AudioMode> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::AudioMode val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::AudioMode* out);
};

template <>
struct Converter<rtvc::DeviceType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::DeviceType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DeviceType* out);
};

template <>
struct Converter<rtvc::Device> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::Device& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::Device* out);
};

template <>
struct Converter<rtvc::VideoFrameBuffer::Type> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::VideoFrameBuffer::Type val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::VideoFrameBuffer::Type* out);
};

template <>
struct Converter<rtvc::VideoRotation> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::VideoRotation val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::VideoRotation* out);
};

template <>
struct Converter<rtvc::AccountInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::AccountInfo& val);
};

template <>
struct Converter<rtvc::ScheduleItemProfile> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::ScheduleItemProfile val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ScheduleItemProfile* out);
};

template <>
struct Converter<rtvc::ScheduleRecurrenceType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::ScheduleRecurrenceType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ScheduleRecurrenceType* out);
};

template <>
struct Converter<rtvc::ScheduleRecurrenceDailyType> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      rtvc::ScheduleRecurrenceDailyType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ScheduleRecurrenceDailyType* out);
};

template <>
struct Converter<rtvc::ScheduleRecurrence> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      const rtvc::ScheduleRecurrence& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ScheduleRecurrence* out);
};

template <>
struct Converter<rtvc::ScheduleDaylightStrategy> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      const rtvc::ScheduleDaylightStrategy& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ScheduleDaylightStrategy* out);
};

template <>
struct Converter<rtvc::ScheduleTimeZoneRule> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      const rtvc::ScheduleTimeZoneRule& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ScheduleTimeZoneRule* out);
};

template <>
struct Converter<rtvc::ScheduleTimeZone> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::ScheduleTimeZone& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ScheduleTimeZone* out);
};

template <>
struct Converter<rtvc::ScheduleMemberRole> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::ScheduleMemberRole val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ScheduleMemberRole* out);
};

template <>
struct Converter<rtvc::ScheduleMemberType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::ScheduleMemberType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ScheduleMemberType* out);
};

template <>
struct Converter<rtvc::ScheduleMember> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::ScheduleMember& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ScheduleMember* out);
};

template <>
struct Converter<rtvc::ScheduleRoom> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::ScheduleRoom& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ScheduleRoom* out);
};

template <>
struct Converter<rtvc::ScheduleRTMPLimitType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::ScheduleRTMPLimitType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ScheduleRTMPLimitType* out);
};

template <>
struct Converter<rtvc::ScheduleRTMP> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::ScheduleRTMP& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ScheduleRTMP* out);
};

template <>
struct Converter<rtvc::ScheduleItemDetail> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      const rtvc::ScheduleItemDetail& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ScheduleItemDetail* out);
};

template <>
struct Converter<rtvc::ContactLoadMode> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::ContactLoadMode val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ContactLoadMode* out);
};

template <>
struct Converter<rtvc::ContactNodeType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::ContactNodeType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ContactNodeType* out);
};

// template <>
// struct Converter<rtvc::ContactNode> {
//   static v8::Local<v8::Value> ToV8(
//       v8::Isolate* isolate,
//       const rtvc::ContactNode& val);

//   static bool FromV8(v8::Isolate* isolate,
//                      v8::Local<v8::Value> val,
//                      rtvc::ContactNode* out);
// };

template <>
struct Converter<rtvc::TerminalInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::TerminalInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::TerminalInfo* out);
};

template <>
struct Converter<rtvc::AlarmInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::AlarmInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::AlarmInfo* out);
};

template <>
struct Converter<rtvc::FeedbackInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::FeedbackInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::FeedbackInfo* out);
};

template <>
struct Converter<rtvc::PackageInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::PackageInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::PackageInfo* out);
};

template <>
struct Converter<rtvc::ConfigurationInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::ConfigurationInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ConfigurationInfo* out);
};

template <>
struct Converter<rtvc::DownloadInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::DownloadInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DownloadInfo* out);
};

template <>
struct Converter<rtvc::UploadLogInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::UploadLogInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UploadLogInfo* out);
};

template <>
struct Converter<rtvc::NetCaptureInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::NetCaptureInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::NetCaptureInfo* out);
};

template <>
struct Converter<rtvc::EventInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::EventInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::EventInfo* out);
};

// description
template <>
struct Converter<rtvc::DescProfile> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::DescProfile val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescProfile* out);
};

template <>
struct Converter<rtvc::DescPosition> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::DescPosition val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescPosition* out);
};
template <>
struct Converter<rtvc::DescBanner> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::DescBanner& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescBanner* out);
};

template <>
struct Converter<rtvc::DescRtmpSessionType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::DescRtmpSessionType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescRtmpSessionType* out);
};
template <>
struct Converter<rtvc::DescRtmpFsType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::DescRtmpFsType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescRtmpFsType* out);
};
template <>
struct Converter<rtvc::DescDefaultRtmp> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::DescDefaultRtmp& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescDefaultRtmp* out);
};

template <>
struct Converter<rtvc::DescUriPurpose> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::DescUriPurpose val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescUriPurpose* out);
};

template <>
struct Converter<rtvc::DescConfUriInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::DescConfUriInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescConfUriInfo* out);
};

template <>
struct Converter<rtvc::DescOrganizerInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::DescOrganizerInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescOrganizerInfo* out);
};

template <>
struct Converter<rtvc::DescConferenceType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::DescConferenceType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescConferenceType* out);
};

template <>
struct Converter<rtvc::DescNumberType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::DescNumberType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescNumberType* out);
};

template <>
struct Converter<rtvc::DescAdmissionPolicy> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::DescAdmissionPolicy val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescAdmissionPolicy* out);
};

template <>
struct Converter<rtvc::DescAttendeeByPass> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::DescAttendeeByPass val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescAttendeeByPass* out);
};

template <>
struct Converter<rtvc::DescAutoPromote> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::DescAutoPromote val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescAutoPromote* out);
};

template <>
struct Converter<rtvc::DescRecordType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::DescRecordType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescRecordType* out);
};

template <>
struct Converter<rtvc::DescRecordPrivilege> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::DescRecordPrivilege val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescRecordPrivilege* out);
};

template <>
struct Converter<rtvc::DescSetLockInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::DescSetLockInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescSetLockInfo* out);
};

template <>
struct Converter<rtvc::DescGetLockInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::DescGetLockInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescGetLockInfo* out);
};

template <>
struct Converter<rtvc::DescInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::DescInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::DescInfo* out);
};

// state

// user
template <>
struct Converter<rtvc::RequesrResult> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::RequesrResult val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::RequesrResult* out);
};

template <>
struct Converter<rtvc::ResponseInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::ResponseInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ResponseInfo* out);
};

template <>
struct Converter<rtvc::HttpResponseInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::HttpResponseInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::HttpResponseInfo* out);
};

template <>
struct Converter<rtvc::ImResponseInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::ImResponseInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ImResponseInfo* out);
};

template <>
struct Converter<rtvc::ImMessageInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::ImMessageInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ImMessageInfo* out);
};

template <>
struct Converter<rtvc::ImMessageList> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::ImMessageList& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ImMessageList* out);
};

template <>
struct Converter<rtvc::UserProtocolType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::UserProtocolType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UserProtocolType* out);
};

template <>
struct Converter<rtvc::UserPermissionType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::UserPermissionType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UserPermissionType* out);
};

template <>
struct Converter<rtvc::UserDemoStateType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::UserDemoStateType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UserDemoStateType* out);
};

template <>
struct Converter<rtvc::PresenterDemoStateType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::PresenterDemoStateType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::PresenterDemoStateType* out);
};

template <>
struct Converter<rtvc::UserRolesInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::UserRolesInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UserRolesInfo* out);
};

template <>
struct Converter<rtvc::UserEndpointSeesionType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::UserEndpointSeesionType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UserEndpointSeesionType* out);
};

template <>
struct Converter<rtvc::UserEndpointStatusType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::UserEndpointStatusType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UserEndpointStatusType* out);
};

template <>
struct Converter<rtvc::UserJoinMethod> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::UserJoinMethod val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UserJoinMethod* out);
};

template <>
struct Converter<rtvc::UserMediaType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::UserMediaType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UserMediaType* out);
};

template <>
struct Converter<rtvc::UserMediaLabelType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::UserMediaLabelType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UserMediaLabelType* out);
};

template <>
struct Converter<rtvc::UserMediaDirectionType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::UserMediaDirectionType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UserMediaDirectionType* out);
};

template <>
struct Converter<rtvc::UserMediafilterType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::UserMediafilterType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UserMediafilterType* out);
};

template <>
struct Converter<rtvc::UserMediaBlockByType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::UserMediaBlockByType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UserMediaBlockByType* out);
};

template <>
struct Converter<rtvc::UserMediaInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::UserMediaInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UserMediaInfo* out);
};

template <>
struct Converter<rtvc::UserMediaFilterInfo> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      const rtvc::UserMediaFilterInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UserMediaFilterInfo* out);
};

template <>
struct Converter<rtvc::UserEndpointInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::UserEndpointInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UserEndpointInfo* out);
};

template <>
struct Converter<rtvc::UserInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::UserInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UserInfo* out);
};

template <>
struct Converter<rtvc::UserMediaDataInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::UserMediaDataInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UserMediaDataInfo* out);
};

template <>
struct Converter<rtvc::UserStatisticsInfo> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      const rtvc::UserStatisticsInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::UserStatisticsInfo* out);
};

template <>
struct Converter<rtvc::RecordStatusType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::RecordStatusType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::RecordStatusType* out);
};

template <>
struct Converter<rtvc::RecordUserInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::RecordUserInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::RecordUserInfo* out);
};

template <>
struct Converter<rtvc::RecordUsers> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::RecordUsers& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::RecordUsers* out);
};

template <>
struct Converter<rtvc::RtmpStatusType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::RtmpStatusType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::RtmpStatusType* out);
};

template <>
struct Converter<rtvc::RtmpUserInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::RtmpUserInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::RtmpUserInfo* out);
};

template <>
struct Converter<rtvc::RtmpInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::RtmpInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::RtmpInfo* out);
};

// view
template <>
struct Converter<rtvc::ViewSpeakMode> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::ViewSpeakMode val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ViewSpeakMode* out);
};

template <>
struct Converter<rtvc::ViewLayoutType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::ViewLayoutType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ViewLayoutType* out);
};

template <>
struct Converter<rtvc::ViewPresenterLayoutType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::ViewPresenterLayoutType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ViewPresenterLayoutType* out);
};

template <>
struct Converter<rtvc::GetLayoutInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::GetLayoutInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::GetLayoutInfo* out);
};

template <>
struct Converter<rtvc::SetLayoutInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::SetLayoutInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::SetLayoutInfo* out);
};

template <>
struct Converter<rtvc::ViewFilterRoleType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::ViewFilterRoleType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ViewFilterRoleType* out);
};

template <>
struct Converter<rtvc::ViewFilterType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::ViewFilterType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ViewFilterType* out);
};

template <>
struct Converter<rtvc::ViewFilterRuleInfo> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      const rtvc::ViewFilterRuleInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::ViewFilterRuleInfo* out);
};

template <>
struct Converter<rtvc::StatsAudioCodecType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::StatsAudioCodecType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::StatsAudioCodecType* out);
};

template <>
struct Converter<rtvc::StatsVideoCodecType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::StatsVideoCodecType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::StatsVideoCodecType* out);
};

template <>
struct Converter<rtvc::StatsVideoProfileType> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   rtvc::StatsVideoProfileType val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::StatsVideoProfileType* out);
};

template <>
struct Converter<rtvc::AudioStatsInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::AudioStatsInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::AudioStatsInfo* out);
};

template <>
struct Converter<rtvc::VideoStatsInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::VideoStatsInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::VideoStatsInfo* out);
};

template <>
struct Converter<rtvc::RTCVideoStats> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::RTCVideoStats& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::RTCVideoStats* out);
};

template <>
struct Converter<rtvc::RTCAudioStats> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::RTCAudioStats& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::RTCAudioStats* out);
};

template <>
struct Converter<rtvc::RTCStats> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::RTCStats& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::RTCStats* out);
};

template <>
struct Converter<rtvc::RTCStatsInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::RTCStatsInfo& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::RTCStatsInfo* out);
};

template <>
struct Converter<rtvc::PartyInviteInfos> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const rtvc::PartyInviteInfos& val);

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     rtvc::PartyInviteInfos* out);
};

}  // namespace mate

#endif  // YEALINK_RTVC_BINDING_CONVERTER_H_
