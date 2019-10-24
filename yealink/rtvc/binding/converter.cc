#include "yealink/rtvc/binding/converter.h"

namespace mate {

v8::Local<v8::Value> Converter<rtvc::AudioMode>::ToV8(v8::Isolate* isolate,
                                                      rtvc::AudioMode val) {
  std::string audio_mode;
  switch (val) {
    case rtvc::AudioMode::kIdle:
      audio_mode = "kIdle";
      break;
    case rtvc::AudioMode::kHandset:
      audio_mode = "kHandset";
      break;
    case rtvc::AudioMode::kHandsetFree:
      audio_mode = "kHandsetFree";
      break;
  }
  return ConvertToV8(isolate, audio_mode);
}

bool Converter<rtvc::AudioMode>::FromV8(v8::Isolate* isolate,
                                        v8::Local<v8::Value> val,
                                        rtvc::AudioMode* out) {
  std::string audio_mode;
  if (!ConvertFromV8(isolate, val, &audio_mode))
    return false;

  if (audio_mode == "kHandset")
    *out = rtvc::AudioMode::kHandset;
  else if (audio_mode == "kHandsetFree")
    *out = rtvc::AudioMode::kHandsetFree;
  else if (audio_mode == "kIdle")
    *out = rtvc::AudioMode::kIdle;
  else
    return false;

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DeviceType>::ToV8(v8::Isolate* isolate,
                                                       rtvc::DeviceType val) {
  std::string device_type;
  switch (val) {
    case rtvc::DeviceType::kAudioInput:
      device_type = "kAudioInput";
      break;
    case rtvc::DeviceType::kAudioOutput:
      device_type = "kAudioOutput";
      break;
    case rtvc::DeviceType::kVideoInput:
      device_type = "kVideoInput";
      break;
    case rtvc::DeviceType::kScreen:
      device_type = "kScreen";
      break;
    case rtvc::DeviceType::kWindow:
      device_type = "kWindow";
      break;
    case rtvc::DeviceType::kImageFile:
      device_type = "kImageFile";
      break;
  }
  return ConvertToV8(isolate, device_type);
}

bool Converter<rtvc::DeviceType>::FromV8(v8::Isolate* isolate,
                                         v8::Local<v8::Value> val,
                                         rtvc::DeviceType* out) {
  std::string device_type;
  if (!ConvertFromV8(isolate, val, &device_type))
    return false;

  if (device_type == "kAudioInput")
    *out = rtvc::DeviceType::kAudioInput;
  else if (device_type == "kAudioOutput")
    *out = rtvc::DeviceType::kAudioOutput;
  else if (device_type == "kAudioOutput")
    *out = rtvc::DeviceType::kAudioOutput;
  else if (device_type == "kVideoInput")
    *out = rtvc::DeviceType::kVideoInput;
  else if (device_type == "kScreen")
    *out = rtvc::DeviceType::kScreen;
  else if (device_type == "kWindow")
    *out = rtvc::DeviceType::kWindow;
  else if (device_type == "kImageFile")
    *out = rtvc::DeviceType::kImageFile;
  else
    return false;

  return true;
}

v8::Local<v8::Value> Converter<rtvc::Device>::ToV8(v8::Isolate* isolate,
                                                   const rtvc::Device& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("deviceId", val.deviceId);
  dict.Set("label", val.label);
  dict.Set("type", val.type);
  return dict.GetHandle();
}

bool Converter<rtvc::Device>::FromV8(v8::Isolate* isolate,
                                     v8::Local<v8::Value> val,
                                     rtvc::Device* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("deviceId", &(out->deviceId));
  dict.Get("label", &(out->label));
  dict.Get("type", &(out->type));
  return true;
}

v8::Local<v8::Value> Converter<rtvc::VideoFrameBuffer::Type>::ToV8(
    v8::Isolate* isolate,
    rtvc::VideoFrameBuffer::Type val) {
  std::string buffer_type;
  switch (val) {
    case rtvc::VideoFrameBuffer::Type::kI010:
      buffer_type = "kI010";
      break;
    case rtvc::VideoFrameBuffer::Type::kI420:
      buffer_type = "kI420";
      break;
    case rtvc::VideoFrameBuffer::Type::kI420A:
      buffer_type = "kI420A";
      break;
    case rtvc::VideoFrameBuffer::Type::kI444:
      buffer_type = "kI444";
      break;
    case rtvc::VideoFrameBuffer::Type::kNative:
      buffer_type = "kNative";
      break;
  }
  return ConvertToV8(isolate, buffer_type);
}

bool Converter<rtvc::VideoFrameBuffer::Type>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::VideoFrameBuffer::Type* out) {
  std::string buffer_type;
  if (!ConvertFromV8(isolate, val, &buffer_type))
    return false;

  if (buffer_type == "kI010")
    *out = rtvc::VideoFrameBuffer::Type::kI010;
  else if (buffer_type == "kI420")
    *out = rtvc::VideoFrameBuffer::Type::kI420;
  else if (buffer_type == "kI420A")
    *out = rtvc::VideoFrameBuffer::Type::kI420A;
  else if (buffer_type == "kI444")
    *out = rtvc::VideoFrameBuffer::Type::kI444;
  else if (buffer_type == "kNative")
    *out = rtvc::VideoFrameBuffer::Type::kNative;
  else
    return false;

  return true;
}

v8::Local<v8::Value> Converter<rtvc::VideoRotation>::ToV8(
    v8::Isolate* isolate,
    rtvc::VideoRotation val) {
  std::string rotation;
  switch (val) {
    case rtvc::VideoRotation::kVideoRotation_0:
      rotation = "kVideoRotation_0";
      break;
    case rtvc::VideoRotation::kVideoRotation_180:
      rotation = "kVideoRotation_180";
      break;
    case rtvc::VideoRotation::kVideoRotation_270:
      rotation = "kVideoRotation_270";
      break;
    case rtvc::VideoRotation::kVideoRotation_90:
      rotation = "kVideoRotation_90";
      break;
    default:
      rotation = "kVideoRotation_0";
      break;
  }
  return ConvertToV8(isolate, rotation);
}

bool Converter<rtvc::VideoRotation>::FromV8(v8::Isolate* isolate,
                                            v8::Local<v8::Value> val,
                                            rtvc::VideoRotation* out) {
  std::string buffer_type;
  if (!ConvertFromV8(isolate, val, &buffer_type))
    return false;

  if (buffer_type == "kVideoRotation_0")
    *out = rtvc::VideoRotation::kVideoRotation_0;
  else if (buffer_type == "kVideoRotation_180")
    *out = rtvc::VideoRotation::kVideoRotation_180;
  else if (buffer_type == "kVideoRotation_270")
    *out = rtvc::VideoRotation::kVideoRotation_270;
  else if (buffer_type == "kVideoRotation_90")
    *out = rtvc::VideoRotation::kVideoRotation_90;
  else
    return false;

  return true;
}

// static
v8::Local<v8::Value> Converter<rtvc::AccountInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::AccountInfo& val) {
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

  Dictionary turn_server = Dictionary::CreateEmpty(isolate);
  turn_server.Set("username", val.turn_server.username);
  turn_server.Set("password", val.turn_server.password);

  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("enterprise", enterprise);
  dict.Set("turnServer", turn_server);
  dict.Set("id", val.id);
  dict.Set("uid", val.uid);
  dict.Set("number", val.number);
  dict.Set("fullNumber", val.full_number);
  dict.Set("name", val.name);
  dict.Set("namePinyin", val.name_pinyin);
  dict.Set("groupInfo", val.group_info);
  dict.Set("token", val.token);
  dict.Set("type", val.type);
  dict.Set("meetnow", val.meetnow);
  dict.Set("ha1", val.ha1);

  return dict.GetHandle();
}

v8::Local<v8::Value> Converter<rtvc::PrimaryAccountInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::PrimaryAccountInfo& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("upgraded", val.upgraded);
  dict.Set("principle", val.principle);
  dict.Set("realm", val.realm);
  dict.Set("type", val.type);
  dict.Set("algorithm", val.algorithm);
  dict.Set("ha1", val.ha1);

  return dict.GetHandle();
}

v8::Local<v8::Value> Converter<rtvc::AccessInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::AccessInfo& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("accountList", val.account_list);
  dict.Set("primaryAccount", val.primary_account);

  return dict.GetHandle();
}

v8::Local<v8::Value> Converter<rtvc::ErrorInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::ErrorInfo& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("bizCode", val.biz_code);

  return dict.GetHandle();
}

// static
v8::Local<v8::Value> Converter<rtvc::ScheduleItemProfile>::ToV8(
    v8::Isolate* isolate,
    rtvc::ScheduleItemProfile val) {
  std::string profile;
  switch (val) {
    case rtvc::ScheduleItemProfile::kDefault:
      profile = "kDefault";
      break;
    case rtvc::ScheduleItemProfile::kEducation:
      profile = "kEducation";
      break;
    case rtvc::ScheduleItemProfile::kSeminar:
      profile = "kSeminar";
      break;
    default:
      profile = "kDefault";
      break;
  }
  return ConvertToV8(isolate, profile);
}
// static
bool Converter<rtvc::ScheduleItemProfile>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::ScheduleItemProfile* out) {
  std::string profile;
  if (!ConvertFromV8(isolate, val, &profile))
    return false;

  if (profile == "kDefault")
    *out = rtvc::ScheduleItemProfile::kDefault;
  else if (profile == "kEducation")
    *out = rtvc::ScheduleItemProfile::kEducation;
  else if (profile == "kSeminar")
    *out = rtvc::ScheduleItemProfile::kSeminar;
  else
    return false;

  return true;
}

// static
v8::Local<v8::Value> Converter<rtvc::ScheduleRecurrenceType>::ToV8(
    v8::Isolate* isolate,
    rtvc::ScheduleRecurrenceType val) {
  std::string recurrence;
  switch (val) {
    case rtvc::ScheduleRecurrenceType::kDaily:
      recurrence = "kDaily";
      break;
    case rtvc::ScheduleRecurrenceType::kMonthly:
      recurrence = "kMonthly";
      break;
    case rtvc::ScheduleRecurrenceType::kMonthlyNTH:
      recurrence = "kMonthlyNTH";
      break;
    case rtvc::ScheduleRecurrenceType::kNone:
      recurrence = "kNone";
      break;
    case rtvc::ScheduleRecurrenceType::kWeekly:
      recurrence = "kWeekly";
      break;
    case rtvc::ScheduleRecurrenceType::kYearly:
      recurrence = "kYearly";
      break;
    case rtvc::ScheduleRecurrenceType::kYearlyNTH:
      recurrence = "kYearlyNTH";
      break;
    default:
      recurrence = "kNone";
      break;
  }
  return ConvertToV8(isolate, recurrence);
}
// static
bool Converter<rtvc::ScheduleRecurrenceType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::ScheduleRecurrenceType* out) {
  std::string recurrence;
  if (!ConvertFromV8(isolate, val, &recurrence))
    return false;

  if (recurrence == "kNone")
    *out = rtvc::ScheduleRecurrenceType::kNone;
  else if (recurrence == "kDaily")
    *out = rtvc::ScheduleRecurrenceType::kDaily;
  else if (recurrence == "kWeekly")
    *out = rtvc::ScheduleRecurrenceType::kWeekly;
  else if (recurrence == "kMonthly")
    *out = rtvc::ScheduleRecurrenceType::kMonthly;
  else if (recurrence == "kMonthlyNTH")
    *out = rtvc::ScheduleRecurrenceType::kMonthlyNTH;
  else if (recurrence == "kYearly")
    *out = rtvc::ScheduleRecurrenceType::kYearly;
  else if (recurrence == "kYearlyNTH")
    *out = rtvc::ScheduleRecurrenceType::kYearlyNTH;
  else
    return false;

  return true;
}
// static
v8::Local<v8::Value> Converter<rtvc::ScheduleRecurrenceDailyType>::ToV8(
    v8::Isolate* isolate,
    rtvc::ScheduleRecurrenceDailyType val) {
  std::string recurrence_daily;
  switch (val) {
    case rtvc::ScheduleRecurrenceDailyType::kEach:
      recurrence_daily = "kEach";
      break;
    case rtvc::ScheduleRecurrenceDailyType::kNone:
      recurrence_daily = "kNone";
      break;
    case rtvc::ScheduleRecurrenceDailyType::kWeekday:
      recurrence_daily = "kWeekday";
      break;
    default:
      recurrence_daily = "kNone";
      break;
  }
  return ConvertToV8(isolate, recurrence_daily);
}
// static
bool Converter<rtvc::ScheduleRecurrenceDailyType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::ScheduleRecurrenceDailyType* out) {
  std::string recurrence_daily;
  if (!ConvertFromV8(isolate, val, &recurrence_daily))
    return false;

  if (recurrence_daily == "kEach")
    *out = rtvc::ScheduleRecurrenceDailyType::kEach;
  else if (recurrence_daily == "kNone")
    *out = rtvc::ScheduleRecurrenceDailyType::kNone;
  else if (recurrence_daily == "kWeekday")
    *out = rtvc::ScheduleRecurrenceDailyType::kWeekday;
  else
    return false;

  return true;
}

v8::Local<v8::Value> Converter<rtvc::ScheduleRecurrence>::ToV8(
    v8::Isolate* isolate,
    const rtvc::ScheduleRecurrence& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("type", val.type);
  dict.Set("dailyType", val.dailyType);
  dict.Set("interval", val.interval);
  dict.Set("startDate", val.startDate);
  dict.Set("endDate", val.endDate);
  dict.Set("count", val.count);
  return dict.GetHandle();
}

bool Converter<rtvc::ScheduleRecurrence>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::ScheduleRecurrence* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("type", &(out->type));
  dict.Get("dailyType", &(out->dailyType));
  dict.Get("interval", &(out->interval));
  dict.Get("startDate", &(out->startDate));
  dict.Get("endDate", &(out->endDate));
  dict.Get("count", &(out->count));
  return true;
}

v8::Local<v8::Value> Converter<rtvc::ScheduleDaylightStrategy>::ToV8(
    v8::Isolate* isolate,
    const rtvc::ScheduleDaylightStrategy& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("isFixedDateRule", val.isFixedDateRule);
  dict.Set("day", val.day);
  dict.Set("month", val.month);
  dict.Set("week", val.week);
  dict.Set("dayOfWeek", val.dayOfWeek);
  dict.Set("timeOfDay", val.timeOfDay);
  return dict.GetHandle();
}

bool Converter<rtvc::ScheduleDaylightStrategy>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::ScheduleDaylightStrategy* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("isFixedDateRule", &(out->isFixedDateRule));
  dict.Get("day", &(out->day));
  dict.Get("month", &(out->month));
  dict.Get("week", &(out->week));
  dict.Get("dayOfWeek", &(out->dayOfWeek));
  dict.Get("timeOfDay", &(out->timeOfDay));
  return true;
}

v8::Local<v8::Value> Converter<rtvc::ScheduleTimeZoneRule>::ToV8(
    v8::Isolate* isolate,
    const rtvc::ScheduleTimeZoneRule& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("startDate", val.startDate);
  dict.Set("endDate", val.endDate);
  dict.Set("daylightDelta", val.daylightDelta);
  dict.Set("daylightStrategyStart", val.daylightStrategyStart);
  dict.Set("daylightStrategyEnd", val.daylightStrategyEnd);
  return dict.GetHandle();
}

bool Converter<rtvc::ScheduleTimeZoneRule>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::ScheduleTimeZoneRule* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("startDate", &(out->startDate));
  dict.Get("endDate", &(out->endDate));
  dict.Get("daylightDelta", &(out->daylightDelta));
  dict.Get("daylightStrategyStart", &(out->daylightStrategyStart));
  dict.Get("daylightStrategyEnd", &(out->daylightStrategyEnd));
  return true;
}

v8::Local<v8::Value> Converter<rtvc::ScheduleTimeZone>::ToV8(
    v8::Isolate* isolate,
    const rtvc::ScheduleTimeZone& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("id", val.id);
  dict.Set("cnName", val.cnName);
  dict.Set("usName", val.usName);
  dict.Set("utcOffset", val.utcOffset);
  dict.Set("utcOffsetName", val.utcOffsetName);
  dict.Set("rule", val.rule);
  return dict.GetHandle();
}

bool Converter<rtvc::ScheduleTimeZone>::FromV8(v8::Isolate* isolate,
                                               v8::Local<v8::Value> val,
                                               rtvc::ScheduleTimeZone* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("id", &(out->id));
  dict.Get("cnName", &(out->cnName));
  dict.Get("usName", &(out->usName));
  dict.Get("utcOffset", &(out->utcOffset));
  dict.Get("utcOffsetName", &(out->utcOffsetName));
  dict.Get("rule", &(out->rule));
  return true;
}

// static
v8::Local<v8::Value> Converter<rtvc::ScheduleMemberRole>::ToV8(
    v8::Isolate* isolate,
    rtvc::ScheduleMemberRole val) {
  std::string member_role;
  switch (val) {
    case rtvc::ScheduleMemberRole::kOrganizer:
      member_role = "kOrganizer";
      break;
    case rtvc::ScheduleMemberRole::kPresenter:
      member_role = "kPresenter";
      break;
    case rtvc::ScheduleMemberRole::kPaticipant:
      member_role = "kPaticipant";
      break;
    case rtvc::ScheduleMemberRole::kCastViewer:
      member_role = "kCastViewer";
      break;
    default:
      member_role = "kPaticipant";
      break;
  }
  return ConvertToV8(isolate, member_role);
}
// static
bool Converter<rtvc::ScheduleMemberRole>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::ScheduleMemberRole* out) {
  std::string member_role;
  if (!ConvertFromV8(isolate, val, &member_role))
    return false;

  if (member_role == "kOrganizer")
    *out = rtvc::ScheduleMemberRole::kOrganizer;
  else if (member_role == "kPresenter")
    *out = rtvc::ScheduleMemberRole::kPresenter;
  else if (member_role == "kPaticipant")
    *out = rtvc::ScheduleMemberRole::kPaticipant;
  else if (member_role == "kCastViewer")
    *out = rtvc::ScheduleMemberRole::kCastViewer;
  else
    return false;

  return true;
}

// static
v8::Local<v8::Value> Converter<rtvc::ScheduleMemberType>::ToV8(
    v8::Isolate* isolate,
    rtvc::ScheduleMemberType val) {
  std::string member_role;
  switch (val) {
    case rtvc::ScheduleMemberType::kInternal:
      member_role = "kInternal";
      break;
    case rtvc::ScheduleMemberType::kExternal:
      member_role = "kExternal";
      break;
    default:
      member_role = "kInternal";
      break;
  }
  return ConvertToV8(isolate, member_role);
}
// static
bool Converter<rtvc::ScheduleMemberType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::ScheduleMemberType* out) {
  std::string member_role;
  if (!ConvertFromV8(isolate, val, &member_role))
    return false;

  if (member_role == "kInternal")
    *out = rtvc::ScheduleMemberType::kInternal;
  else if (member_role == "kExternal")
    *out = rtvc::ScheduleMemberType::kExternal;
  else
    return false;

  return true;
}

v8::Local<v8::Value> Converter<rtvc::ScheduleMember>::ToV8(
    v8::Isolate* isolate,
    const rtvc::ScheduleMember& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("id", val.id);
  dict.Set("name", val.name);
  dict.Set("number", val.number);
  dict.Set("role", val.role);
  dict.Set("type", val.type);
  return dict.GetHandle();
}

bool Converter<rtvc::ScheduleMember>::FromV8(v8::Isolate* isolate,
                                             v8::Local<v8::Value> val,
                                             rtvc::ScheduleMember* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("id", &(out->id));
  dict.Get("name", &(out->name));
  dict.Get("number", &(out->number));
  dict.Get("role", &(out->role));
  dict.Get("type", &(out->type));
  return true;
}

v8::Local<v8::Value> Converter<rtvc::ScheduleRoom>::ToV8(
    v8::Isolate* isolate,
    const rtvc::ScheduleRoom& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("id", val.id);
  dict.Set("name", val.name);
  return dict.GetHandle();
}

bool Converter<rtvc::ScheduleRoom>::FromV8(v8::Isolate* isolate,
                                           v8::Local<v8::Value> val,
                                           rtvc::ScheduleRoom* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("id", &(out->id));
  dict.Get("name", &(out->name));
  return true;
}

// static
v8::Local<v8::Value> Converter<rtvc::ScheduleRTMPLimitType>::ToV8(
    v8::Isolate* isolate,
    rtvc::ScheduleRTMPLimitType val) {
  std::string member_role;
  switch (val) {
    case rtvc::ScheduleRTMPLimitType::kAll:
      member_role = "kAll";
      break;
    case rtvc::ScheduleRTMPLimitType::kPassword:
      member_role = "kPassword";
      break;
    default:
      member_role = "kAll";
      break;
  }
  return ConvertToV8(isolate, member_role);
}
// static
bool Converter<rtvc::ScheduleRTMPLimitType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::ScheduleRTMPLimitType* out) {
  std::string member_role;
  if (!ConvertFromV8(isolate, val, &member_role))
    return false;

  if (member_role == "kAll")
    *out = rtvc::ScheduleRTMPLimitType::kAll;
  else if (member_role == "kPassword")
    *out = rtvc::ScheduleRTMPLimitType::kPassword;
  else
    return false;

  return true;
}

v8::Local<v8::Value> Converter<rtvc::ScheduleRTMP>::ToV8(
    v8::Isolate* isolate,
    const rtvc::ScheduleRTMP& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("autoRecord", val.autoRecord);
  dict.Set("url", val.url);
  dict.Set("password", val.password);
  dict.Set("logoUrl", val.logoUrl);
  dict.Set("limitType", val.limitType);
  return dict.GetHandle();
}

bool Converter<rtvc::ScheduleRTMP>::FromV8(v8::Isolate* isolate,
                                           v8::Local<v8::Value> val,
                                           rtvc::ScheduleRTMP* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("autoRecord", &(out->autoRecord));
  dict.Get("url", &(out->url));
  dict.Get("password", &(out->password));
  dict.Get("logoUrl", &(out->logoUrl));
  dict.Get("limitType", &(out->limitType));
  return true;
}

v8::Local<v8::Value> Converter<rtvc::ScheduleItemDetail>::ToV8(
    v8::Isolate* isolate,
    const rtvc::ScheduleItemDetail& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("shareLink", val.share_link);
  dict.Set("remark", val.remark);
  dict.Set("organizer", val.organizer);
  dict.Set("participants", val.participants);
  dict.Set("rooms", val.rooms);
  dict.Set("rtmp", val.rtmp);
  return dict.GetHandle();
}

bool Converter<rtvc::ScheduleItemDetail>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::ScheduleItemDetail* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("shareLink", &(out->share_link));
  dict.Get("remark", &(out->remark));
  dict.Get("organizer", &(out->organizer));
  dict.Get("participants", &(out->participants));
  dict.Get("rooms", &(out->rooms));
  dict.Get("rtmp", &(out->rtmp));
  return true;
}

// static
v8::Local<v8::Value> Converter<rtvc::ContactLoadMode>::ToV8(
    v8::Isolate* isolate,
    rtvc::ContactLoadMode val) {
  std::string load_mode;
  switch (val) {
    case rtvc::ContactLoadMode::kAuto:
      load_mode = "kAuto";
      break;
    case rtvc::ContactLoadMode::kOverall:
      load_mode = "kOverall";
      break;
    case rtvc::ContactLoadMode::kPartial:
      load_mode = "kPartial";
      break;
    default:
      load_mode = "kAuto";
      break;
  }
  return ConvertToV8(isolate, load_mode);
}

// static
bool Converter<rtvc::ContactLoadMode>::FromV8(v8::Isolate* isolate,
                                              v8::Local<v8::Value> val,
                                              rtvc::ContactLoadMode* out) {
  std::string load_mode;
  if (!ConvertFromV8(isolate, val, &load_mode))
    return false;

  if (load_mode == "kAuto")
    *out = rtvc::ContactLoadMode::kAuto;
  else if (load_mode == "kOverall")
    *out = rtvc::ContactLoadMode::kOverall;
  else if (load_mode == "kPartial")
    *out = rtvc::ContactLoadMode::kPartial;
  else
    return false;

  return true;
}

// static
v8::Local<v8::Value> Converter<rtvc::ContactNodeType>::ToV8(
    v8::Isolate* isolate,
    rtvc::ContactNodeType val) {
  std::string node_type;
  switch (val) {
    case rtvc::ContactNodeType::kDepartment:
      node_type = "kDepartment";
      break;
    case rtvc::ContactNodeType::kStaff:
      node_type = "kStaff";
      break;
    case rtvc::ContactNodeType::kDevice:
      node_type = "kDevice";
      break;
    case rtvc::ContactNodeType::kVMR:
      node_type = "kVMR";
      break;
    case rtvc::ContactNodeType::kThirdParty:
      node_type = "kThirdParty";
      break;
    case rtvc::ContactNodeType::kRoom:
      node_type = "kRoom";
      break;
    case rtvc::ContactNodeType::kEnterprise:
      node_type = "kEnterprise";
      break;
    default:
      node_type = "kDevice";
      break;
  }
  return ConvertToV8(isolate, node_type);
}

// static
bool Converter<rtvc::ContactNodeType>::FromV8(v8::Isolate* isolate,
                                              v8::Local<v8::Value> val,
                                              rtvc::ContactNodeType* out) {
  std::string node_type;
  if (!ConvertFromV8(isolate, val, &node_type))
    return false;

  if (node_type == "kDepartment")
    *out = rtvc::ContactNodeType::kDepartment;
  else if (node_type == "kStaff")
    *out = rtvc::ContactNodeType::kStaff;
  else if (node_type == "kDevice")
    *out = rtvc::ContactNodeType::kDevice;
  else if (node_type == "kVMR")
    *out = rtvc::ContactNodeType::kVMR;
  else if (node_type == "kThirdParty")
    *out = rtvc::ContactNodeType::kThirdParty;
  else if (node_type == "kRoom")
    *out = rtvc::ContactNodeType::kRoom;
  else if (node_type == "kEnterprise")
    *out = rtvc::ContactNodeType::kEnterprise;
  else
    return false;

  return true;
}

// v8::Local<v8::Value> Converter<rtvc::ContactNode>::ToV8(
//     v8::Isolate* isolate,
//     const rtvc::ContactNode& val) {
//   Dictionary dict = Dictionary::CreateEmpty(isolate);
//   dict.Set("uid", val.uid);
//   dict.Set("type", val.type);
//   dict.Set("parentId", val.parentId);
//   dict.Set("childCounts", val.childCounts);
//   dict.Set("name", val.name);
//   dict.Set("i18nName", val.i18nName);
//   dict.Set("pinyin", val.pinyin);
//   dict.Set("pinyinAbbr", val.pinyinAbbr);
//   dict.Set("email", val.email);
//   dict.Set("phone", val.phone);
//   dict.Set("mobile", val.mobile);
//   dict.Set("number", val.number);
//   dict.Set("fullNumber", val.fullNumber);
//   return dict.GetHandle();
// }

// bool Converter<rtvc::ContactNode>::FromV8(
//     v8::Isolate* isolate,
//     v8::Local<v8::Value> val,
//     rtvc::ContactNode* out) {
//   Dictionary dict;
//   if (!ConvertFromV8(isolate, val, &dict))
//     return false;
//   dict.Get("uid", &(out->uid));
//   dict.Get("type", &(out->type));
//   dict.Get("parentId", &(out->parentId));
//   dict.Get("childCounts", &(out->childCounts));
//   dict.Get("name", &(out->name));
//   dict.Get("i18nName", &(out->i18nName));
//   dict.Get("pinyin", &(out->pinyin));
//   dict.Get("pinyinAbbr", &(out->pinyinAbbr));
//   dict.Get("email", &(out->email));
//   dict.Get("phone", &(out->phone));
//   dict.Get("mobile", &(out->mobile));
//   dict.Get("number", &(out->number));
//   dict.Get("fullNumber", &(out->fullNumber));
//   return true;
// }

v8::Local<v8::Value> Converter<rtvc::TerminalInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::TerminalInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("name", val.name);
  handler.Set("type", val.type);
  handler.Set("category", val.category);
  handler.Set("model", val.model);
  handler.Set("platform", val.platform);
  handler.Set("version", val.version);
  handler.Set("arch", val.arch);
  handler.Set("updateChannel", val.update_channel);
  handler.Set("customId", val.custom_id);
  handler.Set("configId", val.config_id);
  handler.Set("remarks", val.remarks);

  handler.Set("deviceModel", val.device_model);
  handler.Set("deviceResolution", val.device_resolution);
  handler.Set("deviceOs", val.device_os);
  handler.Set("deviceIp", val.device_ip);
  handler.Set("deviceMac", val.device_mac);
  handler.Set("deviceHostname", val.device_hostname);
  handler.Set("deviceCpu", val.device_cpu);
  handler.Set("deviceMemory", val.device_memory);

  handler.Set("account", val.account);
  handler.Set("displayName", val.display_name);
  handler.Set("serverType", val.server_type);
  handler.Set("serverAddress", val.server_address);
  handler.Set("serverDomain", val.server_domain);
  handler.Set("serverOutbound", val.server_outbound);
  handler.Set("registerStatus", val.register_status);

  handler.Set("enterpriseDomain", val.enterprise_domain);
  handler.Set("enterpriseId", val.enterprise_id);
  handler.Set("enterpriseName", val.enterprise_name);

  return handler.GetHandle();
}

bool Converter<rtvc::TerminalInfo>::FromV8(v8::Isolate* isolate,
                                           v8::Local<v8::Value> val,
                                           rtvc::TerminalInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("name", &(out->name));
  dict.Get("type", &(out->type));
  dict.Get("category", &(out->category));
  dict.Get("model", &(out->model));
  dict.Get("platform", &(out->platform));
  dict.Get("version", &(out->version));
  dict.Get("arch", &(out->arch));
  dict.Get("updateChannel", &(out->update_channel));
  dict.Get("customId", &(out->custom_id));
  dict.Get("configId", &(out->config_id));
  dict.Get("remarks", &(out->remarks));

  dict.Get("deviceModel", &(out->device_model));
  dict.Get("deviceResolution", &(out->device_resolution));
  dict.Get("deviceOs", &(out->device_os));
  dict.Get("deviceIp", &(out->device_ip));
  dict.Get("deviceMac", &(out->device_mac));
  dict.Get("deviceHostname", &(out->device_hostname));
  dict.Get("deviceCpu", &(out->device_cpu));
  dict.Get("deviceMemory", &(out->device_memory));

  dict.Get("account", &(out->account));
  dict.Get("displayName", &(out->display_name));
  dict.Get("serverType", &(out->server_type));
  dict.Get("serverAddress", &(out->server_address));
  dict.Get("serverDomain", &(out->server_domain));
  dict.Get("serverOutbound", &(out->server_outbound));
  dict.Get("registerStatus", &(out->register_status));

  dict.Get("enterpriseDomain", &(out->enterprise_domain));
  dict.Get("enterpriseId", &(out->enterprise_id));
  dict.Get("enterpriseName", &(out->enterprise_name));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::AlarmInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::AlarmInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("filePath", val.file_path);
  handler.Set("code", val.code);
  handler.Set("name", val.name);
  handler.Set("type", val.type);
  handler.Set("level", val.level);
  handler.Set("desc", val.desc);

  return handler.GetHandle();
}

bool Converter<rtvc::AlarmInfo>::FromV8(v8::Isolate* isolate,
                                        v8::Local<v8::Value> val,
                                        rtvc::AlarmInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("filePath", &(out->file_path));
  dict.Get("code", &(out->code));
  dict.Get("name", &(out->name));
  dict.Get("type", &(out->type));
  dict.Get("level", &(out->level));
  dict.Get("desc", &(out->desc));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::FeedbackInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::FeedbackInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("title", val.title);
  handler.Set("content", val.content);
  handler.Set("category", val.category);
  handler.Set("contact", val.contact);
  handler.Set("filePath", val.file_path);
  handler.Set("imagePath", val.image_path);
  handler.Set("videoPath", val.video_path);

  return handler.GetHandle();
}

bool Converter<rtvc::FeedbackInfo>::FromV8(v8::Isolate* isolate,
                                           v8::Local<v8::Value> val,
                                           rtvc::FeedbackInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("title", &(out->title));
  dict.Get("content", &(out->content));
  dict.Get("category", &(out->category));
  dict.Get("contact", &(out->contact));
  dict.Get("filePath", &(out->file_path));
  dict.Get("imagePath", &(out->image_path));
  dict.Get("videoPath", &(out->video_path));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::PackageInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::PackageInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("version", val.version);
  handler.Set("date", val.date);
  handler.Set("note", val.note);
  handler.Set("name", val.name);
  handler.Set("url", val.url);
  handler.Set("md5", val.md5);
  handler.Set("size", val.size);
  handler.Set("forceUpdate", val.force_update);

  return handler.GetHandle();
}

bool Converter<rtvc::PackageInfo>::FromV8(v8::Isolate* isolate,
                                          v8::Local<v8::Value> val,
                                          rtvc::PackageInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("version", &(out->version));
  dict.Get("date", &(out->date));
  dict.Get("note", &(out->note));
  dict.Get("name", &(out->name));
  dict.Get("url", &(out->url));
  dict.Get("md5", &(out->md5));
  dict.Get("size", &(out->size));
  dict.Get("forceUpdate", &(out->force_update));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::ConfigurationInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::ConfigurationInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("id", val.id);
  handler.Set("name", val.name);
  handler.Set("url", val.url);
  handler.Set("md5", val.md5);

  return handler.GetHandle();
}

bool Converter<rtvc::ConfigurationInfo>::FromV8(v8::Isolate* isolate,
                                                v8::Local<v8::Value> val,
                                                rtvc::ConfigurationInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("id", &(out->id));
  dict.Get("name", &(out->name));
  dict.Get("url", &(out->url));
  dict.Get("md5", &(out->md5));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DownloadInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::DownloadInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("url", val.url);
  handler.Set("path", val.path);
  handler.Set("fileName", val.file_name);

  return handler.GetHandle();
}

bool Converter<rtvc::DownloadInfo>::FromV8(v8::Isolate* isolate,
                                           v8::Local<v8::Value> val,
                                           rtvc::DownloadInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("url", &(out->url));
  dict.Get("path", &(out->path));
  dict.Get("fileName", &(out->file_name));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UploadLogInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::UploadLogInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("sessionId", val.session_id);
  handler.Set("path", val.file_path);

  return handler.GetHandle();
}

bool Converter<rtvc::UploadLogInfo>::FromV8(v8::Isolate* isolate,
                                            v8::Local<v8::Value> val,
                                            rtvc::UploadLogInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("sessionId", &(out->session_id));
  dict.Get("filePath", &(out->file_path));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::NetCaptureInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::NetCaptureInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("sessionId", val.session_id);
  handler.Set("deviceId", val.device_id);
  handler.Set("path", val.path);

  return handler.GetHandle();
}

bool Converter<rtvc::NetCaptureInfo>::FromV8(v8::Isolate* isolate,
                                             v8::Local<v8::Value> val,
                                             rtvc::NetCaptureInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("sessionId", &(out->session_id));
  dict.Get("deviceId", &(out->device_id));
  dict.Get("path", &(out->path));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::EventInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::EventInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("code", val.code);
  handler.Set("name", val.name);
  handler.Set("network", val.network);
  handler.Set("isp", val.isp);

  return handler.GetHandle();
}

bool Converter<rtvc::EventInfo>::FromV8(v8::Isolate* isolate,
                                        v8::Local<v8::Value> val,
                                        rtvc::EventInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("code", &(out->code));
  dict.Get("name", &(out->name));
  dict.Get("network", &(out->network));
  dict.Get("isp", &(out->isp));

  return true;
}

// description
v8::Local<v8::Value> Converter<rtvc::DescProfile>::ToV8(v8::Isolate* isolate,
                                                        rtvc::DescProfile val) {
  std::string profile;
  switch (val) {
    case rtvc::DescProfile::kConference:
      profile = "conference";
      break;
    case rtvc::DescProfile::kTeaching:
      profile = "education";
      break;
    case rtvc::DescProfile::kSeminar:
      profile = "seminar";
      break;
    case rtvc::DescProfile::kInvalid:
      profile = "";
      break;
  }
  return ConvertToV8(isolate, profile);
}

bool Converter<rtvc::DescProfile>::FromV8(v8::Isolate* isolate,
                                          v8::Local<v8::Value> val,
                                          rtvc::DescProfile* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "conference")
    *out = rtvc::DescProfile::kConference;
  else if (in == "education")
    *out = rtvc::DescProfile::kTeaching;
  else if (in == "seminar")
    *out = rtvc::DescProfile::kSeminar;
  else {
    *out = rtvc::DescProfile::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DescPosition>::ToV8(
    v8::Isolate* isolate,
    rtvc::DescPosition val) {
  std::string position;
  switch (val) {
    case rtvc::DescPosition::kTop:
      position = "top";
      break;
    case rtvc::DescPosition::kMedium:
      position = "medium";
      break;
    case rtvc::DescPosition::kBottom:
      position = "bottom";
      break;
    case rtvc::DescPosition::kInvalid:
      position = "";
      break;
  }
  return ConvertToV8(isolate, position);
}

bool Converter<rtvc::DescPosition>::FromV8(v8::Isolate* isolate,
                                           v8::Local<v8::Value> val,
                                           rtvc::DescPosition* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "top")
    *out = rtvc::DescPosition::kTop;
  else if (in == "medium")
    *out = rtvc::DescPosition::kMedium;
  else if (in == "bottom")
    *out = rtvc::DescPosition::kBottom;
  else {
    *out = rtvc::DescPosition::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DescBanner>::ToV8(
    v8::Isolate* isolate,
    const rtvc::DescBanner& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("enabled", val.enabled);
  handler.Set("displayText", val.display_text);
  handler.Set("position", val.position);

  return handler.GetHandle();
}

bool Converter<rtvc::DescBanner>::FromV8(v8::Isolate* isolate,
                                         v8::Local<v8::Value> val,
                                         rtvc::DescBanner* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("enabled", &(out->enabled));
  dict.Get("displayText", &(out->display_text));
  dict.Get("position", &(out->position));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DescRtmpSessionType>::ToV8(
    v8::Isolate* isolate,
    rtvc::DescRtmpSessionType val) {
  std::string profile;
  switch (val) {
    case rtvc::DescRtmpSessionType::kAV:
      profile = "AV";
      break;
    case rtvc::DescRtmpSessionType::kAD:
      profile = "AD";
      break;
    case rtvc::DescRtmpSessionType::kAVD:
      profile = "AVD";
      break;
    case rtvc::DescRtmpSessionType::kInvalid:
      profile = "";
      break;
  }
  return ConvertToV8(isolate, profile);
}

bool Converter<rtvc::DescRtmpSessionType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::DescRtmpSessionType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "AV")
    *out = rtvc::DescRtmpSessionType::kAV;
  else if (in == "AD")
    *out = rtvc::DescRtmpSessionType::kAD;
  else if (in == "AVD")
    *out = rtvc::DescRtmpSessionType::kAVD;
  else {
    *out = rtvc::DescRtmpSessionType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DescRtmpFsType>::ToV8(
    v8::Isolate* isolate,
    rtvc::DescRtmpFsType val) {
  std::string profile;
  switch (val) {
    case rtvc::DescRtmpFsType::k360P:
      profile = "360P";
      break;
    case rtvc::DescRtmpFsType::k720P:
      profile = "720P";
      break;
    case rtvc::DescRtmpFsType::k1080P:
      profile = "1080P";
      break;
    case rtvc::DescRtmpFsType::kInvalid:
      profile = "";
      break;
  }
  return ConvertToV8(isolate, profile);
}

bool Converter<rtvc::DescRtmpFsType>::FromV8(v8::Isolate* isolate,
                                             v8::Local<v8::Value> val,
                                             rtvc::DescRtmpFsType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "360P")
    *out = rtvc::DescRtmpFsType::k360P;
  else if (in == "720P")
    *out = rtvc::DescRtmpFsType::k720P;
  else if (in == "1080P")
    *out = rtvc::DescRtmpFsType::k1080P;
  else {
    *out = rtvc::DescRtmpFsType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DescDefaultRtmp>::ToV8(
    v8::Isolate* isolate,
    const rtvc::DescDefaultRtmp& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("enabled", val.enabled);
  handler.Set("displayText", val.display_text);
  handler.Set("mcuSessionType", val.mcu_session_type);
  handler.Set("maxVideoFs", val.max_video_fs);
  handler.Set("webShareUrl", val.web_share_url);

  return handler.GetHandle();
}

bool Converter<rtvc::DescDefaultRtmp>::FromV8(v8::Isolate* isolate,
                                              v8::Local<v8::Value> val,
                                              rtvc::DescDefaultRtmp* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("enabled", &(out->enabled));
  dict.Get("displayText", &(out->display_text));
  dict.Get("mcuSessionType", &(out->mcu_session_type));
  dict.Get("maxVideoFs", &(out->max_video_fs));
  dict.Get("webShareUrl", &(out->web_share_url));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DescUriPurpose>::ToV8(
    v8::Isolate* isolate,
    rtvc::DescUriPurpose val) {
  std::string profile;
  switch (val) {
    case rtvc::DescUriPurpose::kFocus:
      profile = "focus";
      break;
    case rtvc::DescUriPurpose::kAudioVideo:
      profile = "audio-video";
      break;
    case rtvc::DescUriPurpose::kChat:
      profile = "chat";
      break;
    case rtvc::DescUriPurpose::kCoopShare:
      profile = "coopshare";
      break;
    case rtvc::DescUriPurpose::kApplicationSharing:
      profile = "applicationsharing";
      break;
    case rtvc::DescUriPurpose::kInvalid:
      profile = "";
      break;
  }
  return ConvertToV8(isolate, profile);
}

bool Converter<rtvc::DescUriPurpose>::FromV8(v8::Isolate* isolate,
                                             v8::Local<v8::Value> val,
                                             rtvc::DescUriPurpose* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "focus")
    *out = rtvc::DescUriPurpose::kFocus;
  else if (in == "audio-video")
    *out = rtvc::DescUriPurpose::kAudioVideo;
  else if (in == "chat")
    *out = rtvc::DescUriPurpose::kChat;
  else if (in == "coopshare")
    *out = rtvc::DescUriPurpose::kCoopShare;
  else if (in == "applicationsharing")
    *out = rtvc::DescUriPurpose::kApplicationSharing;
  else {
    *out = rtvc::DescUriPurpose::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DescConfUriInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::DescConfUriInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("uri", val.uri);
  handler.Set("displayText", val.display_text);
  handler.Set("purpose", val.purpose);

  return handler.GetHandle();
}

bool Converter<rtvc::DescConfUriInfo>::FromV8(v8::Isolate* isolate,
                                              v8::Local<v8::Value> val,
                                              rtvc::DescConfUriInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("uri", &(out->uri));
  dict.Get("displayText", &(out->display_text));
  dict.Get("purpose", &(out->purpose));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DescOrganizerInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::DescOrganizerInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("displayText", val.display_text);
  handler.Set("uid", val.uid);
  handler.Set("username", val.username);
  handler.Set("realm", val.realm);
  handler.Set("phone", val.phone);
  handler.Set("domain", val.domain);

  return handler.GetHandle();
}

bool Converter<rtvc::DescOrganizerInfo>::FromV8(v8::Isolate* isolate,
                                                v8::Local<v8::Value> val,
                                                rtvc::DescOrganizerInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("displayText", &(out->display_text));
  dict.Get("uid", &(out->uid));
  dict.Get("username", &(out->username));
  dict.Get("realm", &(out->realm));
  dict.Get("phone", &(out->phone));
  dict.Get("domain", &(out->domain));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DescConferenceType>::ToV8(
    v8::Isolate* isolate,
    rtvc::DescConferenceType val) {
  std::string res;
  switch (val) {
    case rtvc::DescConferenceType::kVGCM:
      res = "VGCM";
      break;
    case rtvc::DescConferenceType::kVGCP:
      res = "VGCP";
      break;
    case rtvc::DescConferenceType::kVMN:
      res = "VMN";
      break;
    case rtvc::DescConferenceType::kVSC:
      res = "VSC";
      break;
    case rtvc::DescConferenceType::kVSCA:
      res = "VSCA";
      break;
    case rtvc::DescConferenceType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::DescConferenceType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::DescConferenceType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "VGCM")
    *out = rtvc::DescConferenceType::kVGCM;
  else if (in == "VGCP")
    *out = rtvc::DescConferenceType::kVGCP;
  else if (in == "VMN")
    *out = rtvc::DescConferenceType::kVMN;
  else if (in == "VSC")
    *out = rtvc::DescConferenceType::kVSC;
  else if (in == "VSCA")
    *out = rtvc::DescConferenceType::kVSCA;
  else {
    *out = rtvc::DescConferenceType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DescNumberType>::ToV8(
    v8::Isolate* isolate,
    rtvc::DescNumberType val) {
  std::string res;
  switch (val) {
    case rtvc::DescNumberType::kMeetNow:
      res = "meetnow";
      break;
    case rtvc::DescNumberType::kRecurrence:
      res = "recurrence";
      break;
    case rtvc::DescNumberType::kVMR:
      res = "vmr";
      break;
    case rtvc::DescNumberType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::DescNumberType>::FromV8(v8::Isolate* isolate,
                                             v8::Local<v8::Value> val,
                                             rtvc::DescNumberType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "meetnow")
    *out = rtvc::DescNumberType::kMeetNow;
  else if (in == "recurrence")
    *out = rtvc::DescNumberType::kRecurrence;
  else if (in == "vmr")
    *out = rtvc::DescNumberType::kVMR;
  else {
    *out = rtvc::DescNumberType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DescAdmissionPolicy>::ToV8(
    v8::Isolate* isolate,
    rtvc::DescAdmissionPolicy val) {
  std::string res;
  switch (val) {
    case rtvc::DescAdmissionPolicy::kClosedAuthenticated:
      res = "closedAuthenticated";
      break;
    case rtvc::DescAdmissionPolicy::kAnonumous:
      res = "anonymous";
      break;
    case rtvc::DescAdmissionPolicy::KOpenAuthenticated:
      res = "openAuthenticated";
      break;
    case rtvc::DescAdmissionPolicy::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::DescAdmissionPolicy>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::DescAdmissionPolicy* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "closedAuthenticated")
    *out = rtvc::DescAdmissionPolicy::kClosedAuthenticated;
  else if (in == "anonymous")
    *out = rtvc::DescAdmissionPolicy::kAnonumous;
  else if (in == "openAuthenticated")
    *out = rtvc::DescAdmissionPolicy::KOpenAuthenticated;
  else {
    *out = rtvc::DescAdmissionPolicy::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DescAttendeeByPass>::ToV8(
    v8::Isolate* isolate,
    rtvc::DescAttendeeByPass val) {
  bool res;
  switch (val) {
    case rtvc::DescAttendeeByPass::kByPassTrue:
      res = true;
      break;
    case rtvc::DescAttendeeByPass::KByPassFalse:
      res = false;
      break;
    case rtvc::DescAttendeeByPass::kInvalid:
      res = false;
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::DescAttendeeByPass>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::DescAttendeeByPass* out) {
  bool in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == true)
    *out = rtvc::DescAttendeeByPass::kByPassTrue;
  else if (in == false)
    *out = rtvc::DescAttendeeByPass::KByPassFalse;
  else {
    *out = rtvc::DescAttendeeByPass::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DescAutoPromote>::ToV8(
    v8::Isolate* isolate,
    rtvc::DescAutoPromote val) {
  int64_t res = 0;
  switch (val) {
    case rtvc::DescAutoPromote::kNone:
      res = 0;
      break;
    case rtvc::DescAutoPromote::kEveryOne:
      res = 2147483648;
      break;
    case rtvc::DescAutoPromote::kCompany:
      res = 32768;
      break;
    case rtvc::DescAutoPromote::kInvalid:
      res = -1;
      break;
  }
  return ConvertToV8(isolate, res);
}

v8::Local<v8::Value> Converter<rtvc::DescRecordType>::ToV8(
    v8::Isolate* isolate,
    rtvc::DescRecordType val) {
  std::string res;
  switch (val) {
    case rtvc::DescRecordType::kThirdParty:
      res = "third-party";
      break;
    case rtvc::DescRecordType::kYealinkRecord:
      res = "ylrecord";
      break;
    case rtvc::DescRecordType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::DescRecordType>::FromV8(v8::Isolate* isolate,
                                             v8::Local<v8::Value> val,
                                             rtvc::DescRecordType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "third-party")
    *out = rtvc::DescRecordType::kThirdParty;
  else if (in == "ylrecord")
    *out = rtvc::DescRecordType::kYealinkRecord;
  else {
    *out = rtvc::DescRecordType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DescRecordPrivilege>::ToV8(
    v8::Isolate* isolate,
    rtvc::DescRecordPrivilege val) {
  std::string res;
  switch (val) {
    case rtvc::DescRecordPrivilege::kOrganizer:
      res = "organizer";
      break;
    case rtvc::DescRecordPrivilege::kPresenter:
      res = "presenter";
      break;
    case rtvc::DescRecordPrivilege::kAttendee:
      res = "attendee";
      break;
    case rtvc::DescRecordPrivilege::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::DescRecordPrivilege>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::DescRecordPrivilege* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "organizer")
    *out = rtvc::DescRecordPrivilege::kOrganizer;
  else if (in == "presenter")
    *out = rtvc::DescRecordPrivilege::kPresenter;
  else if (in == "attendee")
    *out = rtvc::DescRecordPrivilege::kAttendee;
  else {
    *out = rtvc::DescRecordPrivilege::kInvalid;
    return false;
  }

  return true;
}

bool Converter<rtvc::DescAutoPromote>::FromV8(v8::Isolate* isolate,
                                              v8::Local<v8::Value> val,
                                              rtvc::DescAutoPromote* out) {
  int64_t in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == 0)
    *out = rtvc::DescAutoPromote::kNone;
  else if (in == 2147483648)
    *out = rtvc::DescAutoPromote::kEveryOne;
  else if (in == 32768)
    *out = rtvc::DescAutoPromote::kCompany;
  else {
    *out = rtvc::DescAutoPromote::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DescSetLockInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::DescSetLockInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("admissionPolicy", val.admission_policy);
  handler.Set("attendeeByPass", val.attendee_by_pass);
  handler.Set("autoPromote", val.auto_promote);

  return handler.GetHandle();
}

bool Converter<rtvc::DescSetLockInfo>::FromV8(v8::Isolate* isolate,
                                              v8::Local<v8::Value> val,
                                              rtvc::DescSetLockInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("admissionPolicy", &(out->admission_policy));
  dict.Get("attendeeByPass", &(out->attendee_by_pass));
  dict.Get("autoPromote", &(out->auto_promote));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DescGetLockInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::DescGetLockInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("admissionPolicy", val.admission_policy);
  handler.Set("attendeeByPass", val.attendee_by_pass);
  handler.Set("autoPromote", val.auto_promote);

  return handler.GetHandle();
}

bool Converter<rtvc::DescGetLockInfo>::FromV8(v8::Isolate* isolate,
                                              v8::Local<v8::Value> val,
                                              rtvc::DescGetLockInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("admissionPolicy", &(out->admission_policy));
  dict.Get("attendeeByPass", &(out->attendee_by_pass));
  dict.Get("autoPromote", &(out->auto_promote));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::DescInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::DescInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("subject", val.subject);
  handler.Set("startTime", val.start_time);
  handler.Set("banner", val.banner);
  handler.Set("defaultRtmp", val.default_rtmp);
  handler.Set("profile", val.profile);
  handler.Set("recordId", val.record_id);
  handler.Set("confUris", val.conf_uris);
  handler.Set("conferenceId", val.conference_id);
  handler.Set("conferenceNumber", val.conference_number);
  handler.Set("conferenceType", val.conference_type);
  handler.Set("conferenceNumberType", val.conference_number_type);
  handler.Set("bookStartTime", val.book_start_time);
  handler.Set("bookExpiryTime", val.book_expiry_time);
  handler.Set("presenterPin", val.presenter_pin);
  handler.Set("attendeePin", val.attendee_pin);
  handler.Set("admissionPolicy", val.admission_policy);
  handler.Set("lobbyCapable", val.lobby_capable);
  handler.Set("attendeeByPass", val.attendee_by_pass);
  handler.Set("autoPromote", val.auto_promote);
  handler.Set("serverMode", val.server_mode);
  handler.Set("interactiveBroadcastEnabled", val.interactive_broadcast_enabled);
  handler.Set("enterpriseId", val.enterprise_id);
  handler.Set("videoEnable", val.video_enable);
  handler.Set("ipcallEnable", val.ipcall_enable);
  handler.Set("webrtcEnable", val.webrtc_enable);
  handler.Set("recordServer_type", val.record_server_type);
  handler.Set("recordPrivilege", val.record_privilege);
  handler.Set("confInfoUrl", val.conf_info_url);

  return handler.GetHandle();
}

bool Converter<rtvc::DescInfo>::FromV8(v8::Isolate* isolate,
                                       v8::Local<v8::Value> val,
                                       rtvc::DescInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("subject", &(out->subject));
  dict.Get("startTime", &(out->start_time));
  dict.Get("banner", &(out->banner));
  dict.Get("defaultRtmp", &(out->default_rtmp));
  dict.Get("profile", &(out->profile));
  dict.Get("recordId", &(out->record_id));
  dict.Get("confUris", &(out->conf_uris));
  dict.Get("conferenceId", &(out->conference_id));
  dict.Get("conferenceNumber", &(out->conference_number));
  dict.Get("conferenceType", &(out->conference_type));
  dict.Get("conferenceNumberType", &(out->conference_number_type));
  dict.Get("bookStartTime", &(out->book_start_time));
  dict.Get("bookExpiryTime", &(out->book_expiry_time));
  dict.Get("presenterPin", &(out->presenter_pin));
  dict.Get("attendeePin", &(out->attendee_pin));
  dict.Get("admissionPolicy", &(out->admission_policy));
  dict.Get("lobbyCapable", &(out->lobby_capable));
  dict.Get("attendeeByPass", &(out->attendee_by_pass));
  dict.Get("autoPromote", &(out->auto_promote));
  dict.Get("serverMode", &(out->server_mode));
  dict.Get("interactiveBroadcastEnabled",
           &(out->interactive_broadcast_enabled));
  dict.Get("enterpriseId", &(out->enterprise_id));
  dict.Get("videoEnable", &(out->video_enable));
  dict.Get("ipcallEnable", &(out->ipcall_enable));
  dict.Get("webrtcEnable", &(out->webrtc_enable));
  dict.Get("recordServer_type", &(out->record_server_type));
  dict.Get("recordPrivilege", &(out->record_privilege));
  dict.Get("confInfoUrl", &(out->conf_info_url));

  return true;
}

// state

// user
v8::Local<v8::Value> Converter<rtvc::RequesrResult>::ToV8(
    v8::Isolate* isolate,
    rtvc::RequesrResult val) {
  std::string res;
  switch (val) {
    case rtvc::RequesrResult::kSuccess:
      res = "success";
      break;
    case rtvc::RequesrResult::kInvalidParam:
      res = "invalid param";
      break;
    case rtvc::RequesrResult::kSipFailure:
      res = "sip failure";
      break;
    case rtvc::RequesrResult::kInvalid:
      res = "invalid";
      break;
    case rtvc::RequesrResult::kHttpFailure:
      res = "http failure";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::RequesrResult>::FromV8(v8::Isolate* isolate,
                                            v8::Local<v8::Value> val,
                                            rtvc::RequesrResult* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "success")
    *out = rtvc::RequesrResult::kSuccess;
  else if (in == "invalid param")
    *out = rtvc::RequesrResult::kInvalidParam;
  else if (in == "sip failure")
    *out = rtvc::RequesrResult::kSipFailure;
  else if (in == "http failure")
    *out = rtvc::RequesrResult::kHttpFailure;
  else {
    *out = rtvc::RequesrResult::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::ResponseInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::ResponseInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("requestId", val.request_id);
  handler.Set("result", val.result);

  return handler.GetHandle();
}

bool Converter<rtvc::ResponseInfo>::FromV8(v8::Isolate* isolate,
                                           v8::Local<v8::Value> val,
                                           rtvc::ResponseInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("requestId", &(out->request_id));
  dict.Get("result", &(out->result));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::HttpResponseInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::HttpResponseInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("bizCode", val.biz_code);
  handler.Set("result", val.result);

  return handler.GetHandle();
}

bool Converter<rtvc::HttpResponseInfo>::FromV8(v8::Isolate* isolate,
                                               v8::Local<v8::Value> val,
                                               rtvc::HttpResponseInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("bizCode", &(out->biz_code));
  dict.Get("result", &(out->result));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::ImResponseInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::ImResponseInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("bizCode", val.biz_code);
  handler.Set("entity", val.entity);
  handler.Set("timestamp", val.timestamp);

  return handler.GetHandle();
}

bool Converter<rtvc::ImResponseInfo>::FromV8(v8::Isolate* isolate,
                                             v8::Local<v8::Value> val,
                                             rtvc::ImResponseInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("bizCode", &(out->biz_code));
  dict.Get("entity", &(out->entity));
  dict.Get("timestamp", &(out->timestamp));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::ImMessageInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::ImMessageInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("isPrivate", val.is_private);
  handler.Set("text", val.text);
  handler.Set("timestamp", val.timestamp);
  handler.Set("version", val.version);
  handler.Set("senderEntity", val.sender_entity);
  handler.Set("senderDisplayText", val.sender_display_text);

  return handler.GetHandle();
}

bool Converter<rtvc::ImMessageInfo>::FromV8(v8::Isolate* isolate,
                                            v8::Local<v8::Value> val,
                                            rtvc::ImMessageInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("isPrivate", &(out->is_private));
  dict.Get("text", &(out->text));
  dict.Get("timestamp", &(out->timestamp));
  dict.Get("version", &(out->version));
  dict.Get("senderEntity", &(out->sender_entity));
  dict.Get("senderDisplayText", &(out->sender_display_text));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::ImMessageList>::ToV8(
    v8::Isolate* isolate,
    const rtvc::ImMessageList& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("bizCode", val.biz_code);
  handler.Set("messages", val.messages);

  return handler.GetHandle();
}

bool Converter<rtvc::ImMessageList>::FromV8(v8::Isolate* isolate,
                                            v8::Local<v8::Value> val,
                                            rtvc::ImMessageList* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("bizCode", &(out->biz_code));
  dict.Get("messages", &(out->messages));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UserProtocolType>::ToV8(
    v8::Isolate* isolate,
    rtvc::UserProtocolType val) {
  std::string res;
  switch (val) {
    case rtvc::UserProtocolType::kSIP:
      res = "SIP";
      break;
    case rtvc::UserProtocolType::kH323:
      res = "H323";
      break;
    case rtvc::UserProtocolType::kRTMP:
      res = "RTMP";
      break;
    case rtvc::UserProtocolType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::UserProtocolType>::FromV8(v8::Isolate* isolate,
                                               v8::Local<v8::Value> val,
                                               rtvc::UserProtocolType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "SIP")
    *out = rtvc::UserProtocolType::kSIP;
  else if (in == "H323")
    *out = rtvc::UserProtocolType::kH323;
  else if (in == "RTMP")
    *out = rtvc::UserProtocolType::kRTMP;
  else {
    *out = rtvc::UserProtocolType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UserPermissionType>::ToV8(
    v8::Isolate* isolate,
    rtvc::UserPermissionType val) {
  std::string res;
  switch (val) {
    case rtvc::UserPermissionType::kAttendee:
      res = "attendee";
      break;
    case rtvc::UserPermissionType::kCastviewer:
      res = "castviewer";
      break;
    case rtvc::UserPermissionType::kOrganizer:
      res = "organizer";
      break;
    case rtvc::UserPermissionType::kPresenter:
      res = "presenter";
      break;
    case rtvc::UserPermissionType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::UserPermissionType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::UserPermissionType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "attendee")
    *out = rtvc::UserPermissionType::kAttendee;
  else if (in == "castviewer")
    *out = rtvc::UserPermissionType::kCastviewer;
  else if (in == "organizer")
    *out = rtvc::UserPermissionType::kOrganizer;
  else if (in == "presenter")
    *out = rtvc::UserPermissionType::kPresenter;
  else {
    *out = rtvc::UserPermissionType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UserDemoStateType>::ToV8(
    v8::Isolate* isolate,
    rtvc::UserDemoStateType val) {
  std::string res;
  switch (val) {
    case rtvc::UserDemoStateType::kAudience:
      res = "audience";
      break;
    case rtvc::UserDemoStateType::kDemonstrator:
      res = "demonstrator";
      break;
    case rtvc::UserDemoStateType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::UserDemoStateType>::FromV8(v8::Isolate* isolate,
                                                v8::Local<v8::Value> val,
                                                rtvc::UserDemoStateType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "audience")
    *out = rtvc::UserDemoStateType::kAudience;
  else if (in == "demonstrator")
    *out = rtvc::UserDemoStateType::kDemonstrator;
  else {
    *out = rtvc::UserDemoStateType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::PresenterDemoStateType>::ToV8(
    v8::Isolate* isolate,
    rtvc::PresenterDemoStateType val) {
  std::string res;
  switch (val) {
    case rtvc::PresenterDemoStateType::kAudience:
      res = "audience";
      break;
    case rtvc::PresenterDemoStateType::kDemonstrator:
      res = "demonstrator";
      break;
    case rtvc::PresenterDemoStateType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::PresenterDemoStateType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::PresenterDemoStateType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "audience")
    *out = rtvc::PresenterDemoStateType::kAudience;
  else if (in == "demonstrator")
    *out = rtvc::PresenterDemoStateType::kDemonstrator;
  else {
    *out = rtvc::PresenterDemoStateType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UserRolesInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::UserRolesInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("permission", val.permission);
  handler.Set("demostate", val.demostate);
  handler.Set("presenterDemostate", val.presenter_demostate);

  return handler.GetHandle();
}

bool Converter<rtvc::UserRolesInfo>::FromV8(v8::Isolate* isolate,
                                            v8::Local<v8::Value> val,
                                            rtvc::UserRolesInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("permission", &(out->permission));
  dict.Get("demostate", &(out->demostate));
  dict.Get("presenterDemostate", &(out->presenter_demostate));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UserEndpointSeesionType>::ToV8(
    v8::Isolate* isolate,
    rtvc::UserEndpointSeesionType val) {
  std::string res;
  switch (val) {
    case rtvc::UserEndpointSeesionType::kApplicationSharing:
      res = "applicationsharing";
      break;
    case rtvc::UserEndpointSeesionType::kAudioVideo:
      res = "audio-video";
      break;
    case rtvc::UserEndpointSeesionType::kChat:
      res = "chat";
      break;
    case rtvc::UserEndpointSeesionType::kCoopshare:
      res = "coopshare";
      break;
    case rtvc::UserEndpointSeesionType::kFocus:
      res = "focus";
      break;
    case rtvc::UserEndpointSeesionType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::UserEndpointSeesionType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::UserEndpointSeesionType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "applicationsharing")
    *out = rtvc::UserEndpointSeesionType::kApplicationSharing;
  else if (in == "audio-video")
    *out = rtvc::UserEndpointSeesionType::kAudioVideo;
  else if (in == "chat")
    *out = rtvc::UserEndpointSeesionType::kChat;
  else if (in == "coopshare")
    *out = rtvc::UserEndpointSeesionType::kCoopshare;
  else if (in == "focus")
    *out = rtvc::UserEndpointSeesionType::kFocus;
  else {
    *out = rtvc::UserEndpointSeesionType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UserEndpointStatusType>::ToV8(
    v8::Isolate* isolate,
    rtvc::UserEndpointStatusType val) {
  std::string res;
  switch (val) {
    case rtvc::UserEndpointStatusType::kConnected:
      res = "connected";
      break;
    case rtvc::UserEndpointStatusType::kDialingIn:
      res = "dialing-in";
      break;
    case rtvc::UserEndpointStatusType::kDialingOut:
      res = "dialing-out";
      break;
    case rtvc::UserEndpointStatusType::kDisconnected:
      res = "disconnected";
      break;
    case rtvc::UserEndpointStatusType::kOnHold:
      res = "on-hold";
      break;
    case rtvc::UserEndpointStatusType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::UserEndpointStatusType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::UserEndpointStatusType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "connected")
    *out = rtvc::UserEndpointStatusType::kConnected;
  else if (in == "dialing-in")
    *out = rtvc::UserEndpointStatusType::kDialingIn;
  else if (in == "dialing-out")
    *out = rtvc::UserEndpointStatusType::kDialingOut;
  else if (in == "disconnected")
    *out = rtvc::UserEndpointStatusType::kDisconnected;
  else if (in == "on-hold")
    *out = rtvc::UserEndpointStatusType::kOnHold;
  else {
    *out = rtvc::UserEndpointStatusType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UserJoinMethod>::ToV8(
    v8::Isolate* isolate,
    rtvc::UserJoinMethod val) {
  std::string res;
  switch (val) {
    case rtvc::UserJoinMethod::kDialedIn:
      res = "dialed-in";
      break;
    case rtvc::UserJoinMethod::kDialedOut:
      res = "dialed-out";
      break;
    case rtvc::UserJoinMethod::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::UserJoinMethod>::FromV8(v8::Isolate* isolate,
                                             v8::Local<v8::Value> val,
                                             rtvc::UserJoinMethod* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "dialed-in")
    *out = rtvc::UserJoinMethod::kDialedIn;
  else if (in == "dialed-out")
    *out = rtvc::UserJoinMethod::kDialedOut;
  else {
    *out = rtvc::UserJoinMethod::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UserMediaType>::ToV8(
    v8::Isolate* isolate,
    rtvc::UserMediaType val) {
  std::string res;
  switch (val) {
    case rtvc::UserMediaType::kApplication:
      res = "application";
      break;
    case rtvc::UserMediaType::kAudio:
      res = "audio";
      break;
    case rtvc::UserMediaType::kVideo:
      res = "video";
      break;
    case rtvc::UserMediaType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::UserMediaType>::FromV8(v8::Isolate* isolate,
                                            v8::Local<v8::Value> val,
                                            rtvc::UserMediaType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "application")
    *out = rtvc::UserMediaType::kApplication;
  else if (in == "audio")
    *out = rtvc::UserMediaType::kAudio;
  else if (in == "video")
    *out = rtvc::UserMediaType::kVideo;
  else {
    *out = rtvc::UserMediaType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UserMediaLabelType>::ToV8(
    v8::Isolate* isolate,
    rtvc::UserMediaLabelType val) {
  std::string res;
  switch (val) {
    case rtvc::UserMediaLabelType::kApplication:
      res = "application";
      break;
    case rtvc::UserMediaLabelType::kFecc:
      res = "fecc";
      break;
    case rtvc::UserMediaLabelType::kMainAudio:
      res = "main-audio";
      break;
    case rtvc::UserMediaLabelType::kMainVideo:
      res = "main-video";
      break;
    case rtvc::UserMediaLabelType::kInvalid:
      res = "main-video";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::UserMediaLabelType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::UserMediaLabelType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "application")
    *out = rtvc::UserMediaLabelType::kApplication;
  else if (in == "fecc")
    *out = rtvc::UserMediaLabelType::kFecc;
  else if (in == "main-audio")
    *out = rtvc::UserMediaLabelType::kMainAudio;
  else if (in == "main-video")
    *out = rtvc::UserMediaLabelType::kMainVideo;
  else {
    *out = rtvc::UserMediaLabelType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UserMediaDirectionType>::ToV8(
    v8::Isolate* isolate,
    rtvc::UserMediaDirectionType val) {
  std::string res;
  switch (val) {
    case rtvc::UserMediaDirectionType::kInactive:
      res = "inactive";
      break;
    case rtvc::UserMediaDirectionType::kRecvOnly:
      res = "recvonly";
      break;
    case rtvc::UserMediaDirectionType::kSendOnly:
      res = "sendonly";
      break;
    case rtvc::UserMediaDirectionType::kSendRecv:
      res = "sendrecv";
      break;
    case rtvc::UserMediaDirectionType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::UserMediaDirectionType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::UserMediaDirectionType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "inactive")
    *out = rtvc::UserMediaDirectionType::kInactive;
  else if (in == "recvonly")
    *out = rtvc::UserMediaDirectionType::kRecvOnly;
  else if (in == "sendonly")
    *out = rtvc::UserMediaDirectionType::kSendOnly;
  else if (in == "sendrecv")
    *out = rtvc::UserMediaDirectionType::kSendRecv;
  else {
    *out = rtvc::UserMediaDirectionType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UserMediafilterType>::ToV8(
    v8::Isolate* isolate,
    rtvc::UserMediafilterType val) {
  std::string res;
  switch (val) {
    case rtvc::UserMediafilterType::kBlock:
      res = "block";
      break;
    case rtvc::UserMediafilterType::kUnblock:
      res = "unblock";
      break;
    case rtvc::UserMediafilterType::kUnblocking:
      res = "unblocking";
      break;
    case rtvc::UserMediafilterType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::UserMediafilterType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::UserMediafilterType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "block")
    *out = rtvc::UserMediafilterType::kBlock;
  else if (in == "unblock")
    *out = rtvc::UserMediafilterType::kUnblock;
  else if (in == "unblocking")
    *out = rtvc::UserMediafilterType::kUnblocking;
  else {
    *out = rtvc::UserMediafilterType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UserMediaBlockByType>::ToV8(
    v8::Isolate* isolate,
    rtvc::UserMediaBlockByType val) {
  std::string res;
  switch (val) {
    case rtvc::UserMediaBlockByType::kClient:
      res = "client";
      break;
    case rtvc::UserMediaBlockByType::kNone:
      res = "none";
      break;
    case rtvc::UserMediaBlockByType::kServer:
      res = "server";
      break;
    case rtvc::UserMediaBlockByType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::UserMediaBlockByType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::UserMediaBlockByType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "client")
    *out = rtvc::UserMediaBlockByType::kClient;
  else if (in == "none")
    *out = rtvc::UserMediaBlockByType::kNone;
  else if (in == "server")
    *out = rtvc::UserMediaBlockByType::kServer;
  else {
    *out = rtvc::UserMediaBlockByType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UserMediaInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::UserMediaInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("id", val.id);
  handler.Set("type", val.type);
  handler.Set("label", val.label);
  handler.Set("status", val.status);
  handler.Set("mediaEgressBlockBy", val.media_egress_block_by);
  handler.Set("mediaEgressFilter", val.media_egress_filter);
  handler.Set("mediaIngressBlockBy", val.media_ingress_block_by);
  handler.Set("mediaIngressFilter", val.media_ingress_filter);

  return handler.GetHandle();
}

bool Converter<rtvc::UserMediaInfo>::FromV8(v8::Isolate* isolate,
                                            v8::Local<v8::Value> val,
                                            rtvc::UserMediaInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("id", &(out->id));
  dict.Get("type", &(out->type));
  dict.Get("label", &(out->label));
  dict.Get("status", &(out->status));
  dict.Get("mediaEgressBlockBy", &(out->media_egress_block_by));
  dict.Get("mediaEgressFilter", &(out->media_egress_filter));
  dict.Get("mediaIngressBlockBy", &(out->media_ingress_block_by));
  dict.Get("mediaIngressFilter", &(out->media_ingress_filter));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UserMediaFilterInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::UserMediaFilterInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("mediaEgressBlockBy", val.media_egress_block_by);
  handler.Set("mediaEgressFilter", val.media_egress_filter);
  handler.Set("mediaIngressBlockBy", val.media_ingress_block_by);
  handler.Set("mediaIngressFilter", val.media_ingress_filter);

  return handler.GetHandle();
}

bool Converter<rtvc::UserMediaFilterInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::UserMediaFilterInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("mediaEgressBlockBy", &(out->media_egress_block_by));
  dict.Get("mediaEgressFilter", &(out->media_egress_filter));
  dict.Get("mediaIngressBlockBy", &(out->media_ingress_block_by));
  dict.Get("mediaIngressFilter", &(out->media_ingress_filter));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UserEndpointInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::UserEndpointInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("entity", val.entity);
  handler.Set("sessionType", val.session_type);
  handler.Set("status", val.status);
  handler.Set("joiningMethod", val.joining_method);
  handler.Set("when", val.when);
  handler.Set("mcuCallId", val.mcu_call_id);
  handler.Set("media", val.media);

  return handler.GetHandle();
}

bool Converter<rtvc::UserEndpointInfo>::FromV8(v8::Isolate* isolate,
                                               v8::Local<v8::Value> val,
                                               rtvc::UserEndpointInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("entity", &(out->entity));
  dict.Get("sessionType", &(out->session_type));
  dict.Get("status", &(out->status));
  dict.Get("joiningMethod", &(out->joining_method));
  dict.Get("when", &(out->when));
  dict.Get("mcuCallId", &(out->mcu_call_id));
  dict.Get("media", &(out->media));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UserInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::UserInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("entity", val.entity);
  handler.Set("displayText", val.display_text);
  handler.Set("displayNumber", val.display_number);
  handler.Set("displayTextPinyin", val.display_text_pinyin);
  handler.Set("uid", val.uid);
  handler.Set("protocol", val.protocol);
  handler.Set("mediumServerType", val.medium_server_type);
  handler.Set("ip", val.ip);
  handler.Set("phone", val.phone);
  handler.Set("requestUri", val.request_uri);
  handler.Set("userAgent", val.user_agent);
  handler.Set("roles", val.roles);
  handler.Set("endpoint", val.endpoint);

  return handler.GetHandle();
}

bool Converter<rtvc::UserInfo>::FromV8(v8::Isolate* isolate,
                                       v8::Local<v8::Value> val,
                                       rtvc::UserInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("entity", &(out->entity));
  dict.Get("displayText", &(out->display_text));
  dict.Get("displayNumber", &(out->display_number));
  dict.Get("displayTextPinyin", &(out->display_text_pinyin));
  dict.Get("uid", &(out->uid));
  dict.Get("protocol", &(out->protocol));
  dict.Get("mediumServerType", &(out->medium_server_type));
  dict.Get("ip", &(out->ip));
  dict.Get("phone", &(out->phone));
  dict.Get("requestUri", &(out->request_uri));
  dict.Get("userAgent", &(out->user_agent));
  dict.Get("roles", &(out->roles));
  dict.Get("endpoint", &(out->endpoint));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UserMediaDataInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::UserMediaDataInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("enable", val.enable);
  handler.Set("ip", val.ip);
  handler.Set("codec", val.codec);
  handler.Set("width", val.width);
  handler.Set("height", val.height);
  handler.Set("fr", val.fr);
  handler.Set("sampleRate", val.sample_rate);
  handler.Set("bandwidth", val.bandwidth);
  handler.Set("bitRate", val.bit_rate);
  handler.Set("lossRate", val.loss_rate);
  handler.Set("packetLost", val.packet_lost);
  handler.Set("jitter", val.jitter);
  handler.Set("rtt", val.rtt);

  return handler.GetHandle();
}

bool Converter<rtvc::UserMediaDataInfo>::FromV8(v8::Isolate* isolate,
                                                v8::Local<v8::Value> val,
                                                rtvc::UserMediaDataInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("enable", &(out->enable));
  dict.Get("ip", &(out->ip));
  dict.Get("codec", &(out->codec));
  dict.Get("width", &(out->width));
  dict.Get("height", &(out->height));
  dict.Get("fr", &(out->fr));
  dict.Get("sampleRate", &(out->sample_rate));
  dict.Get("bandwidth", &(out->bandwidth));
  dict.Get("bitRate", &(out->bit_rate));
  dict.Get("lossRate", &(out->loss_rate));
  dict.Get("packetLost", &(out->packet_lost));
  dict.Get("jitter", &(out->jitter));
  dict.Get("rtt", &(out->rtt));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::UserStatisticsInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::UserStatisticsInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("mediaId", val.media_id);
  handler.Set("label", val.label);
  handler.Set("type", val.type);
  handler.Set("send", val.send);
  handler.Set("recv", val.recv);

  return handler.GetHandle();
}

bool Converter<rtvc::UserStatisticsInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::UserStatisticsInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("mediaId", &(out->media_id));
  dict.Get("label", &(out->label));
  dict.Get("type", &(out->type));
  dict.Get("send", &(out->send));
  dict.Get("recv", &(out->recv));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::RecordStatusType>::ToV8(
    v8::Isolate* isolate,
    rtvc::RecordStatusType val) {
  std::string res;
  switch (val) {
    case rtvc::RecordStatusType::kInvalid:
      res = "";
      break;
    case rtvc::RecordStatusType::kPause:
      res = "pause";
      break;
    case rtvc::RecordStatusType::kPausing:
      res = "pausing";
      break;
    case rtvc::RecordStatusType::kResume:
      res = "resume";
      break;
    case rtvc::RecordStatusType::kResuming:
      res = "resuming";
      break;
    case rtvc::RecordStatusType::kStart:
      res = "start";
      break;
    case rtvc::RecordStatusType::kStarting:
      res = "starting";
      break;
    case rtvc::RecordStatusType::kStop:
      res = "stop";
      break;
    case rtvc::RecordStatusType::kStopping:
      res = "stopping";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::RecordStatusType>::FromV8(v8::Isolate* isolate,
                                               v8::Local<v8::Value> val,
                                               rtvc::RecordStatusType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "pause")
    *out = rtvc::RecordStatusType::kPause;
  else if (in == "pausing")
    *out = rtvc::RecordStatusType::kPausing;
  else if (in == "resume")
    *out = rtvc::RecordStatusType::kResume;
  else if (in == "resuming")
    *out = rtvc::RecordStatusType::kResuming;
  else if (in == "start")
    *out = rtvc::RecordStatusType::kStart;
  else if (in == "starting")
    *out = rtvc::RecordStatusType::kStarting;
  else if (in == "stop")
    *out = rtvc::RecordStatusType::kStop;
  else if (in == "stopping")
    *out = rtvc::RecordStatusType::kStopping;
  else {
    *out = rtvc::RecordStatusType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::RecordUserInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::RecordUserInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("recordLastStartTime", val.record_last_start_time);
  handler.Set("recordLastStopDuration", val.record_last_stop_duration);
  handler.Set("recordStatus", val.record_status);

  return handler.GetHandle();
}

bool Converter<rtvc::RecordUserInfo>::FromV8(v8::Isolate* isolate,
                                             v8::Local<v8::Value> val,
                                             rtvc::RecordUserInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("recordLastStartTime", &(out->record_last_start_time));
  dict.Get("recordLastStopDuration", &(out->record_last_stop_duration));
  dict.Get("recordStatus", &(out->record_status));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::RecordUsers>::ToV8(
    v8::Isolate* isolate,
    const rtvc::RecordUsers& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("user", val.user);
  handler.Set("bizCode", val.biz_code);

  return handler.GetHandle();
}

bool Converter<rtvc::RecordUsers>::FromV8(v8::Isolate* isolate,
                                          v8::Local<v8::Value> val,
                                          rtvc::RecordUsers* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("user", &(out->user));
  dict.Get("bizCode", &(out->biz_code));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::RtmpStatusType>::ToV8(
    v8::Isolate* isolate,
    rtvc::RtmpStatusType val) {
  std::string res;
  switch (val) {
    case rtvc::RtmpStatusType::kInvalid:
      res = "";
      break;
    case rtvc::RtmpStatusType::kPause:
      res = "pause";
      break;
    case rtvc::RtmpStatusType::kPausing:
      res = "pausing";
      break;
    case rtvc::RtmpStatusType::kResume:
      res = "resume";
      break;
    case rtvc::RtmpStatusType::kResuming:
      res = "resuming";
      break;
    case rtvc::RtmpStatusType::kStart:
      res = "start";
      break;
    case rtvc::RtmpStatusType::kStarting:
      res = "starting";
      break;
    case rtvc::RtmpStatusType::kStop:
      res = "stop";
      break;
    case rtvc::RtmpStatusType::kStopping:
      res = "stopping";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::RtmpStatusType>::FromV8(v8::Isolate* isolate,
                                             v8::Local<v8::Value> val,
                                             rtvc::RtmpStatusType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "pause")
    *out = rtvc::RtmpStatusType::kPause;
  else if (in == "pausing")
    *out = rtvc::RtmpStatusType::kPausing;
  else if (in == "resume")
    *out = rtvc::RtmpStatusType::kResume;
  else if (in == "resuming")
    *out = rtvc::RtmpStatusType::kResuming;
  else if (in == "start")
    *out = rtvc::RtmpStatusType::kStart;
  else if (in == "starting")
    *out = rtvc::RtmpStatusType::kStarting;
  else if (in == "stop")
    *out = rtvc::RtmpStatusType::kStop;
  else if (in == "stopping")
    *out = rtvc::RtmpStatusType::kStopping;
  else {
    *out = rtvc::RtmpStatusType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::RtmpUserInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::RtmpUserInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("entity", val.entity);
  handler.Set("isDefault", val.is_default);
  handler.Set("rtmpStatus", val.rtmp_status);
  handler.Set("rtmpLastStopDuration", val.rtmp_last_start_time);
  handler.Set("rtmpLastStartTime", val.rtmp_last_stop_duration);

  return handler.GetHandle();
}

bool Converter<rtvc::RtmpUserInfo>::FromV8(v8::Isolate* isolate,
                                           v8::Local<v8::Value> val,
                                           rtvc::RtmpUserInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("entity", &(out->entity));
  dict.Get("isDefault", &(out->is_default));
  dict.Get("rtmpStatus", &(out->rtmp_status));
  dict.Get("rtmpLastStopDuration", &(out->rtmp_last_start_time));
  dict.Get("rtmpLastStartTime", &(out->rtmp_last_stop_duration));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::RtmpInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::RtmpInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("enable", val.enable);
  handler.Set("bizCode", val.biz_code);
  handler.Set("users", val.users);

  return handler.GetHandle();
}

bool Converter<rtvc::RtmpInfo>::FromV8(v8::Isolate* isolate,
                                       v8::Local<v8::Value> val,
                                       rtvc::RtmpInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("enable", &(out->enable));
  dict.Get("bizCode", &(out->biz_code));
  dict.Get("users", &(out->users));

  return true;
}

// view
v8::Local<v8::Value> Converter<rtvc::ViewSpeakMode>::ToV8(
    v8::Isolate* isolate,
    rtvc::ViewSpeakMode val) {
  std::string res;
  switch (val) {
    case rtvc::ViewSpeakMode::kFree:
      res = "free";
      break;
    case rtvc::ViewSpeakMode::kHandUp:
      res = "handUp";
      break;
    case rtvc::ViewSpeakMode::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::ViewSpeakMode>::FromV8(v8::Isolate* isolate,
                                            v8::Local<v8::Value> val,
                                            rtvc::ViewSpeakMode* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "free")
    *out = rtvc::ViewSpeakMode::kFree;
  else if (in == "handUp")
    *out = rtvc::ViewSpeakMode::kHandUp;
  else {
    *out = rtvc::ViewSpeakMode::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::ViewLayoutType>::ToV8(
    v8::Isolate* isolate,
    rtvc::ViewLayoutType val) {
  std::string res;
  switch (val) {
    case rtvc::ViewLayoutType::kEquality:
      res = "Equality";
      break;
    case rtvc::ViewLayoutType::kPresentation:
      res = "Presentation";
      break;
    case rtvc::ViewLayoutType::kSpeechExcitation:
      res = "SpeechExcitation";
      break;
    case rtvc::ViewLayoutType::kExclusive:
      res = "Exclusive";
      break;
    case rtvc::ViewLayoutType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::ViewLayoutType>::FromV8(v8::Isolate* isolate,
                                             v8::Local<v8::Value> val,
                                             rtvc::ViewLayoutType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "Equality")
    *out = rtvc::ViewLayoutType::kEquality;
  else if (in == "Presentation")
    *out = rtvc::ViewLayoutType::kPresentation;
  else if (in == "SpeechExcitation")
    *out = rtvc::ViewLayoutType::kSpeechExcitation;
  else if (in == "Exclusive")
    *out = rtvc::ViewLayoutType::kExclusive;
  else {
    *out = rtvc::ViewLayoutType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::ViewPresenterLayoutType>::ToV8(
    v8::Isolate* isolate,
    rtvc::ViewPresenterLayoutType val) {
  std::string res;
  switch (val) {
    case rtvc::ViewPresenterLayoutType::kEquality:
      res = "Equality";
      break;
    case rtvc::ViewPresenterLayoutType::kSpeechExcitation:
      res = "SpeechExcitation";
      break;
    case rtvc::ViewPresenterLayoutType::kExclusive:
      res = "Exclusive";
      break;
    case rtvc::ViewPresenterLayoutType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::ViewPresenterLayoutType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::ViewPresenterLayoutType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "Equality")
    *out = rtvc::ViewPresenterLayoutType::kEquality;
  else if (in == "SpeechExcitation")
    *out = rtvc::ViewPresenterLayoutType::kSpeechExcitation;
  else if (in == "Exclusive")
    *out = rtvc::ViewPresenterLayoutType::kExclusive;
  else {
    *out = rtvc::ViewPresenterLayoutType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::GetLayoutInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::GetLayoutInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("speakMode", val.speak_mode);
  handler.Set("videoLayout", val.video_layout);
  handler.Set("videoMaxView", val.video_max_view);
  handler.Set("videoPresenterLayout", val.video_presenter_layout);
  handler.Set("videoPresenterMaxView", val.video_presenter_max_view);
  handler.Set("videoRoundNumber", val.video_round_number);
  handler.Set("videoRoundInterval", val.video_round_interval);
  handler.Set("videoSpeechExSensitivity", val.video_speech_ex_sensitivity);
  handler.Set("videoRoundEnable", val.video_round_enable);
  handler.Set("videoBigRound", val.video_big_round);
  handler.Set("videoSpeechExEnabled", val.video_speech_ex_enabled);
  handler.Set("videoDataMixEnabled", val.video_data_mix_enabled);
  handler.Set("hideOsdSitename", val.hide_osd_sitename);
  handler.Set("hideOsdSitestatus", val.hide_osd_sitestatus);

  return handler.GetHandle();
}

bool Converter<rtvc::GetLayoutInfo>::FromV8(v8::Isolate* isolate,
                                            v8::Local<v8::Value> val,
                                            rtvc::GetLayoutInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("speakMode", &(out->speak_mode));
  dict.Get("videoLayout", &(out->video_layout));
  dict.Get("videoMaxView", &(out->video_max_view));
  dict.Get("videoPresenterLayout", &(out->video_presenter_layout));
  dict.Get("videoPresenterMaxView", &(out->video_presenter_max_view));
  dict.Get("videoRoundNumber", &(out->video_round_number));
  dict.Get("videoRoundInterval", &(out->video_round_interval));
  dict.Get("videoSpeechExSensitivity", &(out->video_speech_ex_sensitivity));
  dict.Get("videoRoundEnable", &(out->video_round_enable));
  dict.Get("videoBigRound", &(out->video_big_round));
  dict.Get("videoSpeechExEnabled", &(out->video_speech_ex_enabled));
  dict.Get("videoDataMixEnabled", &(out->video_data_mix_enabled));
  dict.Get("hideOsdSitename", &(out->hide_osd_sitename));
  dict.Get("hideOsdSitestatus", &(out->hide_osd_sitestatus));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::SetLayoutInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::SetLayoutInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("videoLayout", val.video_layout);
  handler.Set("videoMaxView", val.video_max_view);

  return handler.GetHandle();
}

bool Converter<rtvc::SetLayoutInfo>::FromV8(v8::Isolate* isolate,
                                            v8::Local<v8::Value> val,
                                            rtvc::SetLayoutInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("videoLayout", &(out->video_layout));
  dict.Get("videoMaxView", &(out->video_max_view));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::ViewFilterRoleType>::ToV8(
    v8::Isolate* isolate,
    rtvc::ViewFilterRoleType val) {
  std::string res;
  switch (val) {
    case rtvc::ViewFilterRoleType::kDefault:
      res = "default";
      break;
    case rtvc::ViewFilterRoleType::kAttendee:
      res = "attendee";
      break;
    case rtvc::ViewFilterRoleType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::ViewFilterRoleType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::ViewFilterRoleType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "default")
    *out = rtvc::ViewFilterRoleType::kDefault;
  else if (in == "attendee")
    *out = rtvc::ViewFilterRoleType::kAttendee;
  else {
    *out = rtvc::ViewFilterRoleType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::ViewFilterType>::ToV8(
    v8::Isolate* isolate,
    rtvc::ViewFilterType val) {
  std::string res;
  switch (val) {
    case rtvc::ViewFilterType::kBlock:
      res = "block";
      break;
    case rtvc::ViewFilterType::kUnBlock:
      res = "unblock";
      break;
    case rtvc::ViewFilterType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::ViewFilterType>::FromV8(v8::Isolate* isolate,
                                             v8::Local<v8::Value> val,
                                             rtvc::ViewFilterType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "block")
    *out = rtvc::ViewFilterType::kBlock;
  else if (in == "unblock")
    *out = rtvc::ViewFilterType::kUnBlock;
  else {
    *out = rtvc::ViewFilterType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::ViewFilterRuleInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::ViewFilterRuleInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("role", val.role);
  handler.Set("ingress", val.ingress);
  handler.Set("egress", val.egress);

  return handler.GetHandle();
}

bool Converter<rtvc::ViewFilterRuleInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::ViewFilterRuleInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("role", &(out->role));
  dict.Get("ingress", &(out->ingress));
  dict.Get("egress", &(out->egress));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::StatsAudioCodecType>::ToV8(
    v8::Isolate* isolate,
    rtvc::StatsAudioCodecType val) {
  std::string res;
  switch (val) {
    case rtvc::StatsAudioCodecType::kAACLC:
      res = "AACLC";
      break;
    case rtvc::StatsAudioCodecType::kARES:
      res = "ARES";
      break;
    case rtvc::StatsAudioCodecType::kG7221:
      res = "G7221";
      break;
    case rtvc::StatsAudioCodecType::kG72221C:
      res = "G7221C";
      break;
    case rtvc::StatsAudioCodecType::kG722:
      res = "G722";
      break;
    case rtvc::StatsAudioCodecType::kG729:
      res = "G729";
      break;
    case rtvc::StatsAudioCodecType::kNone:
      res = "";
      break;
    case rtvc::StatsAudioCodecType::kOPUS:
      res = "OPUS";
      break;
    case rtvc::StatsAudioCodecType::kPCMA:
      res = "PCMA";
      break;
    case rtvc::StatsAudioCodecType::kPCMU:
      res = "PCMU";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::StatsAudioCodecType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::StatsAudioCodecType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "AACLC")
    *out = rtvc::StatsAudioCodecType::kAACLC;
  else if (in == "ARES")
    *out = rtvc::StatsAudioCodecType::kARES;
  else if (in == "G7221")
    *out = rtvc::StatsAudioCodecType::kG7221;
  else if (in == "G72221C")
    *out = rtvc::StatsAudioCodecType::kG72221C;
  else if (in == "G722")
    *out = rtvc::StatsAudioCodecType::kG722;
  else if (in == "G729")
    *out = rtvc::StatsAudioCodecType::kG729;
  else if (in == "OPUS")
    *out = rtvc::StatsAudioCodecType::kOPUS;
  else if (in == "PCMA")
    *out = rtvc::StatsAudioCodecType::kPCMA;
  else if (in == "PCMU")
    *out = rtvc::StatsAudioCodecType::kPCMU;
  else {
    *out = rtvc::StatsAudioCodecType::kNone;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::StatsVideoCodecType>::ToV8(
    v8::Isolate* isolate,
    rtvc::StatsVideoCodecType val) {
  std::string res;
  switch (val) {
    case rtvc::StatsVideoCodecType::kH263:
      res = "H263";
      break;
    case rtvc::StatsVideoCodecType::kH264:
      res = "H264";
      break;
    case rtvc::StatsVideoCodecType::kNone:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::StatsVideoCodecType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::StatsVideoCodecType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "H263")
    *out = rtvc::StatsVideoCodecType::kH263;
  else if (in == "H264")
    *out = rtvc::StatsVideoCodecType::kH264;
  else {
    *out = rtvc::StatsVideoCodecType::kNone;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::StatsVideoProfileType>::ToV8(
    v8::Isolate* isolate,
    rtvc::StatsVideoProfileType val) {
  std::string res;
  switch (val) {
    case rtvc::StatsVideoProfileType::kBase:
      res = "base";
      break;
    case rtvc::StatsVideoProfileType::kHigh:
      res = "high";
      break;
    case rtvc::StatsVideoProfileType::kMain:
      res = "main";
      break;
    case rtvc::StatsVideoProfileType::kMax:
      res = "max";
      break;
    case rtvc::StatsVideoProfileType::kNone:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<rtvc::StatsVideoProfileType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    rtvc::StatsVideoProfileType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "base")
    *out = rtvc::StatsVideoProfileType::kBase;
  else if (in == "high")
    *out = rtvc::StatsVideoProfileType::kHigh;
  else if (in == "main")
    *out = rtvc::StatsVideoProfileType::kMain;
  else if (in == "max")
    *out = rtvc::StatsVideoProfileType::kMax;
  else {
    *out = rtvc::StatsVideoProfileType::kNone;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<rtvc::AudioStatsInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::AudioStatsInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("codec", val.codec);
  handler.Set("bitrate", val.bitrate);
  handler.Set("samplerate", val.samplerate);
  handler.Set("lossRate", val.loss_rate);
  handler.Set("totalLostPackets", val.total_lost_packets);
  handler.Set("jitter", val.jitter);
  handler.Set("delay", val.delay);

  return handler.GetHandle();
}

bool Converter<rtvc::AudioStatsInfo>::FromV8(v8::Isolate* isolate,
                                             v8::Local<v8::Value> val,
                                             rtvc::AudioStatsInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("codec", &(out->codec));
  dict.Get("bitrate", &(out->bitrate));
  dict.Get("samplerate", &(out->samplerate));
  dict.Get("lossRate", &(out->loss_rate));
  dict.Get("totalLostPackets", &(out->total_lost_packets));
  dict.Get("jitter", &(out->jitter));
  dict.Get("delay", &(out->delay));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::VideoStatsInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::VideoStatsInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("codec", val.codec);
  handler.Set("profile", val.profile);
  handler.Set("width", val.width);
  handler.Set("height", val.height);
  handler.Set("frameRate", val.frame_rate);
  handler.Set("bitRate", val.bit_rate);
  handler.Set("lossRate", val.loss_rate);
  handler.Set("totalLossPackets", val.total_loss_packets);
  handler.Set("jitter", val.jitter);
  handler.Set("rtt", val.rtt);

  return handler.GetHandle();
}

bool Converter<rtvc::VideoStatsInfo>::FromV8(v8::Isolate* isolate,
                                             v8::Local<v8::Value> val,
                                             rtvc::VideoStatsInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("codec", &(out->codec));
  dict.Get("profile", &(out->profile));
  dict.Get("width", &(out->width));
  dict.Get("height", &(out->height));
  dict.Get("frameRate", &(out->frame_rate));
  dict.Get("bitRate", &(out->bit_rate));
  dict.Get("lossRate", &(out->loss_rate));
  dict.Get("totalLossPackets", &(out->total_loss_packets));
  dict.Get("jitter", &(out->jitter));
  dict.Get("rtt", &(out->rtt));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::RTCVideoStats>::ToV8(
    v8::Isolate* isolate,
    const rtvc::RTCVideoStats& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("inbound", val.inbound);
  handler.Set("outbound", val.outbound);

  return handler.GetHandle();
}

bool Converter<rtvc::RTCVideoStats>::FromV8(v8::Isolate* isolate,
                                            v8::Local<v8::Value> val,
                                            rtvc::RTCVideoStats* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("inbound", &(out->inbound));
  dict.Get("outbound", &(out->outbound));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::RTCAudioStats>::ToV8(
    v8::Isolate* isolate,
    const rtvc::RTCAudioStats& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("inbound", val.inbound);
  handler.Set("outbound", val.outbound);

  return handler.GetHandle();
}

bool Converter<rtvc::RTCAudioStats>::FromV8(v8::Isolate* isolate,
                                            v8::Local<v8::Value> val,
                                            rtvc::RTCAudioStats* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("inbound", &(out->inbound));
  dict.Get("outbound", &(out->outbound));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::RTCStats>::ToV8(
    v8::Isolate* isolate,
    const rtvc::RTCStats& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("video", val.video);
  handler.Set("audio", val.audio);

  return handler.GetHandle();
}

bool Converter<rtvc::RTCStats>::FromV8(v8::Isolate* isolate,
                                       v8::Local<v8::Value> val,
                                       rtvc::RTCStats* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("video", &(out->video));
  dict.Get("audio", &(out->audio));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::RTCStatsInfo>::ToV8(
    v8::Isolate* isolate,
    const rtvc::RTCStatsInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("media", val.media);
  handler.Set("share", val.share);

  return handler.GetHandle();
}

bool Converter<rtvc::RTCStatsInfo>::FromV8(v8::Isolate* isolate,
                                           v8::Local<v8::Value> val,
                                           rtvc::RTCStatsInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("media", &(out->media));
  dict.Get("share", &(out->share));

  return true;
}

v8::Local<v8::Value> Converter<rtvc::PartyInviteInfos>::ToV8(
    v8::Isolate* isolate,
    const rtvc::PartyInviteInfos& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("url", val.url);
  handler.Set("applicants", val.applicants);

  return handler.GetHandle();
}

bool Converter<rtvc::PartyInviteInfos>::FromV8(v8::Isolate* isolate,
                                               v8::Local<v8::Value> val,
                                               rtvc::PartyInviteInfos* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("url", &(out->url));
  dict.Get("applicants", &(out->applicants));

  return true;
}

}  // namespace mate
