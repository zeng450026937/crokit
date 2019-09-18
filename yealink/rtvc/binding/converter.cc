#include "yealink/rtvc/binding/converter.h"

namespace mate {

v8::Local<v8::Value> Converter<yealink::rtvc::AudioMode>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::AudioMode val) {
  std::string audio_mode;
  switch (val) {
    case yealink::rtvc::AudioMode::kIdle:
      audio_mode = "kIdle";
      break;
    case yealink::rtvc::AudioMode::kHandset:
      audio_mode = "kHandset";
      break;
    case yealink::rtvc::AudioMode::kHandsetFree:
      audio_mode = "kHandsetFree";
      break;
  }
  return ConvertToV8(isolate, audio_mode);
}

bool Converter<yealink::rtvc::AudioMode>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::AudioMode* out) {
  std::string audio_mode;
  if (!ConvertFromV8(isolate, val, &audio_mode))
    return false;

  if (audio_mode == "kHandset")
    *out = yealink::rtvc::AudioMode::kHandset;
  else if (audio_mode == "kHandsetFree")
    *out = yealink::rtvc::AudioMode::kHandsetFree;
  else if (audio_mode == "kIdle")
    *out = yealink::rtvc::AudioMode::kIdle;
  else
    return false;

  return true;
}

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

  return dict.GetHandle();
}

// static
v8::Local<v8::Value> Converter<yealink::rtvc::ScheduleItemProfile>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::ScheduleItemProfile val) {
  std::string profile;
  switch (val) {
    case yealink::rtvc::ScheduleItemProfile::kDefault:
      profile = "kDefault";
      break;
    case yealink::rtvc::ScheduleItemProfile::kEducation:
      profile = "kEducation";
      break;
    case yealink::rtvc::ScheduleItemProfile::kSeminar:
      profile = "kSeminar";
      break;
    default:
      profile = "kDefault";
      break;
  }
  return ConvertToV8(isolate, profile);
}
// static
bool Converter<yealink::rtvc::ScheduleItemProfile>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ScheduleItemProfile* out) {
  std::string profile;
  if (!ConvertFromV8(isolate, val, &profile))
    return false;

  if (profile == "kDefault")
    *out = yealink::rtvc::ScheduleItemProfile::kDefault;
  else if (profile == "kEducation")
    *out = yealink::rtvc::ScheduleItemProfile::kEducation;
  else if (profile == "kSeminar")
    *out = yealink::rtvc::ScheduleItemProfile::kSeminar;
  else
    return false;

  return true;
}

// static
v8::Local<v8::Value> Converter<yealink::rtvc::ScheduleRecurrenceType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::ScheduleRecurrenceType val) {
  std::string recurrence;
  switch (val) {
    case yealink::rtvc::ScheduleRecurrenceType::kDaily:
      recurrence = "kDaily";
      break;
    case yealink::rtvc::ScheduleRecurrenceType::kMonthly:
      recurrence = "kMonthly";
      break;
    case yealink::rtvc::ScheduleRecurrenceType::kMonthlyNTH:
      recurrence = "kMonthlyNTH";
      break;
    case yealink::rtvc::ScheduleRecurrenceType::kNone:
      recurrence = "kNone";
      break;
    case yealink::rtvc::ScheduleRecurrenceType::kWeekly:
      recurrence = "kWeekly";
      break;
    case yealink::rtvc::ScheduleRecurrenceType::kYearly:
      recurrence = "kYearly";
      break;
    case yealink::rtvc::ScheduleRecurrenceType::kYearlyNTH:
      recurrence = "kYearlyNTH";
      break;
    default:
      recurrence = "kNone";
      break;
  }
  return ConvertToV8(isolate, recurrence);
}
// static
bool Converter<yealink::rtvc::ScheduleRecurrenceType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ScheduleRecurrenceType* out) {
  std::string recurrence;
  if (!ConvertFromV8(isolate, val, &recurrence))
    return false;

  if (recurrence == "kNone")
    *out = yealink::rtvc::ScheduleRecurrenceType::kNone;
  else if (recurrence == "kDaily")
    *out = yealink::rtvc::ScheduleRecurrenceType::kDaily;
  else if (recurrence == "kWeekly")
    *out = yealink::rtvc::ScheduleRecurrenceType::kWeekly;
  else if (recurrence == "kMonthly")
    *out = yealink::rtvc::ScheduleRecurrenceType::kMonthly;
  else if (recurrence == "kMonthlyNTH")
    *out = yealink::rtvc::ScheduleRecurrenceType::kMonthlyNTH;
  else if (recurrence == "kYearly")
    *out = yealink::rtvc::ScheduleRecurrenceType::kYearly;
  else if (recurrence == "kYearlyNTH")
    *out = yealink::rtvc::ScheduleRecurrenceType::kYearlyNTH;
  else
    return false;

  return true;
}
// static
v8::Local<v8::Value>
Converter<yealink::rtvc::ScheduleRecurrenceDailyType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::ScheduleRecurrenceDailyType val) {
  std::string recurrence_daily;
  switch (val) {
    case yealink::rtvc::ScheduleRecurrenceDailyType::kEach:
      recurrence_daily = "kEach";
      break;
    case yealink::rtvc::ScheduleRecurrenceDailyType::kNone:
      recurrence_daily = "kNone";
      break;
    case yealink::rtvc::ScheduleRecurrenceDailyType::kWeekday:
      recurrence_daily = "kWeekday";
      break;
    default:
      recurrence_daily = "kNone";
      break;
  }
  return ConvertToV8(isolate, recurrence_daily);
}
// static
bool Converter<yealink::rtvc::ScheduleRecurrenceDailyType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ScheduleRecurrenceDailyType* out) {
  std::string recurrence_daily;
  if (!ConvertFromV8(isolate, val, &recurrence_daily))
    return false;

  if (recurrence_daily == "kEach")
    *out = yealink::rtvc::ScheduleRecurrenceDailyType::kEach;
  else if (recurrence_daily == "kNone")
    *out = yealink::rtvc::ScheduleRecurrenceDailyType::kNone;
  else if (recurrence_daily == "kWeekday")
    *out = yealink::rtvc::ScheduleRecurrenceDailyType::kWeekday;
  else
    return false;

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::ScheduleRecurrence>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::ScheduleRecurrence& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("type", val.type);
  dict.Set("dailyType", val.dailyType);
  dict.Set("interval", val.interval);
  dict.Set("startDate", val.startDate);
  dict.Set("endDate", val.endDate);
  dict.Set("count", val.count);
  return dict.GetHandle();
}

bool Converter<yealink::rtvc::ScheduleRecurrence>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ScheduleRecurrence* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::ScheduleDaylightStrategy>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::ScheduleDaylightStrategy& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("isFixedDateRule", val.isFixedDateRule);
  dict.Set("day", val.day);
  dict.Set("month", val.month);
  dict.Set("week", val.week);
  dict.Set("dayOfWeek", val.dayOfWeek);
  dict.Set("timeOfDay", val.timeOfDay);
  return dict.GetHandle();
}

bool Converter<yealink::rtvc::ScheduleDaylightStrategy>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ScheduleDaylightStrategy* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::ScheduleTimeZoneRule>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::ScheduleTimeZoneRule& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("startDate", val.startDate);
  dict.Set("endDate", val.endDate);
  dict.Set("daylightDelta", val.daylightDelta);
  dict.Set("daylightStrategyStart", val.daylightStrategyStart);
  dict.Set("daylightStrategyEnd", val.daylightStrategyEnd);
  return dict.GetHandle();
}

bool Converter<yealink::rtvc::ScheduleTimeZoneRule>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ScheduleTimeZoneRule* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::ScheduleTimeZone>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::ScheduleTimeZone& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("id", val.id);
  dict.Set("cnName", val.cnName);
  dict.Set("usName", val.usName);
  dict.Set("utcOffset", val.utcOffset);
  dict.Set("utcOffsetName", val.utcOffsetName);
  dict.Set("rule", val.rule);
  return dict.GetHandle();
}

bool Converter<yealink::rtvc::ScheduleTimeZone>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ScheduleTimeZone* out) {
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
v8::Local<v8::Value> Converter<yealink::rtvc::ScheduleMemberRole>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::ScheduleMemberRole val) {
  std::string member_role;
  switch (val) {
    case yealink::rtvc::ScheduleMemberRole::kOrganizer:
      member_role = "kOrganizer";
      break;
    case yealink::rtvc::ScheduleMemberRole::kPresenter:
      member_role = "kPresenter";
      break;
    case yealink::rtvc::ScheduleMemberRole::kPaticipant:
      member_role = "kPaticipant";
      break;
    case yealink::rtvc::ScheduleMemberRole::kCastViewer:
      member_role = "kCastViewer";
      break;
    default:
      member_role = "kPaticipant";
      break;
  }
  return ConvertToV8(isolate, member_role);
}
// static
bool Converter<yealink::rtvc::ScheduleMemberRole>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ScheduleMemberRole* out) {
  std::string member_role;
  if (!ConvertFromV8(isolate, val, &member_role))
    return false;

  if (member_role == "kOrganizer")
    *out = yealink::rtvc::ScheduleMemberRole::kOrganizer;
  else if (member_role == "kPresenter")
    *out = yealink::rtvc::ScheduleMemberRole::kPresenter;
  else if (member_role == "kPaticipant")
    *out = yealink::rtvc::ScheduleMemberRole::kPaticipant;
  else if (member_role == "kCastViewer")
    *out = yealink::rtvc::ScheduleMemberRole::kCastViewer;
  else
    return false;

  return true;
}

// static
v8::Local<v8::Value> Converter<yealink::rtvc::ScheduleMemberType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::ScheduleMemberType val) {
  std::string member_role;
  switch (val) {
    case yealink::rtvc::ScheduleMemberType::kInternal:
      member_role = "kInternal";
      break;
    case yealink::rtvc::ScheduleMemberType::kExternal:
      member_role = "kExternal";
      break;
    default:
      member_role = "kInternal";
      break;
  }
  return ConvertToV8(isolate, member_role);
}
// static
bool Converter<yealink::rtvc::ScheduleMemberType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ScheduleMemberType* out) {
  std::string member_role;
  if (!ConvertFromV8(isolate, val, &member_role))
    return false;

  if (member_role == "kInternal")
    *out = yealink::rtvc::ScheduleMemberType::kInternal;
  else if (member_role == "kExternal")
    *out = yealink::rtvc::ScheduleMemberType::kExternal;
  else
    return false;

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::ScheduleMember>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::ScheduleMember& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("id", val.id);
  dict.Set("name", val.name);
  dict.Set("number", val.number);
  dict.Set("role", val.role);
  dict.Set("type", val.type);
  return dict.GetHandle();
}

bool Converter<yealink::rtvc::ScheduleMember>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ScheduleMember* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::ScheduleRoom>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::ScheduleRoom& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("id", val.id);
  dict.Set("name", val.name);
  return dict.GetHandle();
}

bool Converter<yealink::rtvc::ScheduleRoom>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ScheduleRoom* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("id", &(out->id));
  dict.Get("name", &(out->name));
  return true;
}

// static
v8::Local<v8::Value> Converter<yealink::rtvc::ScheduleRTMPLimitType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::ScheduleRTMPLimitType val) {
  std::string member_role;
  switch (val) {
    case yealink::rtvc::ScheduleRTMPLimitType::kAll:
      member_role = "kAll";
      break;
    case yealink::rtvc::ScheduleRTMPLimitType::kPassword:
      member_role = "kPassword";
      break;
    default:
      member_role = "kAll";
      break;
  }
  return ConvertToV8(isolate, member_role);
}
// static
bool Converter<yealink::rtvc::ScheduleRTMPLimitType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ScheduleRTMPLimitType* out) {
  std::string member_role;
  if (!ConvertFromV8(isolate, val, &member_role))
    return false;

  if (member_role == "kAll")
    *out = yealink::rtvc::ScheduleRTMPLimitType::kAll;
  else if (member_role == "kPassword")
    *out = yealink::rtvc::ScheduleRTMPLimitType::kPassword;
  else
    return false;

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::ScheduleRTMP>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::ScheduleRTMP& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("autoRecord", val.autoRecord);
  dict.Set("url", val.url);
  dict.Set("password", val.password);
  dict.Set("logoUrl", val.logoUrl);
  dict.Set("limitType", val.limitType);
  return dict.GetHandle();
}

bool Converter<yealink::rtvc::ScheduleRTMP>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ScheduleRTMP* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::ScheduleItemDetail>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::ScheduleItemDetail& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("shareLink", val.share_link);
  dict.Set("remark", val.remark);
  dict.Set("organizer", val.organizer);
  dict.Set("participants", val.participants);
  dict.Set("rooms", val.rooms);
  dict.Set("rtmp", val.rtmp);
  return dict.GetHandle();
}

bool Converter<yealink::rtvc::ScheduleItemDetail>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ScheduleItemDetail* out) {
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
v8::Local<v8::Value> Converter<yealink::rtvc::ContactLoadMode>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::ContactLoadMode val) {
  std::string load_mode;
  switch (val) {
    case yealink::rtvc::ContactLoadMode::kAuto:
      load_mode = "kAuto";
      break;
    case yealink::rtvc::ContactLoadMode::kOverall:
      load_mode = "kOverall";
      break;
    case yealink::rtvc::ContactLoadMode::kPartial:
      load_mode = "kPartial";
      break;
    default:
      load_mode = "kAuto";
      break;
  }
  return ConvertToV8(isolate, load_mode);
}

// static
bool Converter<yealink::rtvc::ContactLoadMode>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ContactLoadMode* out) {
  std::string load_mode;
  if (!ConvertFromV8(isolate, val, &load_mode))
    return false;

  if (load_mode == "kAuto")
    *out = yealink::rtvc::ContactLoadMode::kAuto;
  else if (load_mode == "kOverall")
    *out = yealink::rtvc::ContactLoadMode::kOverall;
  else if (load_mode == "kPartial")
    *out = yealink::rtvc::ContactLoadMode::kPartial;
  else
    return false;

  return true;
}

// static
v8::Local<v8::Value> Converter<yealink::rtvc::ContactNodeType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::ContactNodeType val) {
  std::string node_type;
  switch (val) {
    case yealink::rtvc::ContactNodeType::kDepartment:
      node_type = "kDepartment";
      break;
    case yealink::rtvc::ContactNodeType::kStaff:
      node_type = "kStaff";
      break;
    case yealink::rtvc::ContactNodeType::kDevice:
      node_type = "kDevice";
      break;
    case yealink::rtvc::ContactNodeType::kVMR:
      node_type = "kVMR";
      break;
    case yealink::rtvc::ContactNodeType::kThirdParty:
      node_type = "kThirdParty";
      break;
    case yealink::rtvc::ContactNodeType::kRoom:
      node_type = "kRoom";
      break;
    case yealink::rtvc::ContactNodeType::kEnterprise:
      node_type = "kEnterprise";
      break;
    default:
      node_type = "kDevice";
      break;
  }
  return ConvertToV8(isolate, node_type);
}

// static
bool Converter<yealink::rtvc::ContactNodeType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ContactNodeType* out) {
  std::string node_type;
  if (!ConvertFromV8(isolate, val, &node_type))
    return false;

  if (node_type == "kDepartment")
    *out = yealink::rtvc::ContactNodeType::kDepartment;
  else if (node_type == "kStaff")
    *out = yealink::rtvc::ContactNodeType::kStaff;
  else if (node_type == "kDevice")
    *out = yealink::rtvc::ContactNodeType::kDevice;
  else if (node_type == "kVMR")
    *out = yealink::rtvc::ContactNodeType::kVMR;
  else if (node_type == "kThirdParty")
    *out = yealink::rtvc::ContactNodeType::kThirdParty;
  else if (node_type == "kRoom")
    *out = yealink::rtvc::ContactNodeType::kRoom;
  else if (node_type == "kEnterprise")
    *out = yealink::rtvc::ContactNodeType::kEnterprise;
  else
    return false;

  return true;
}

// v8::Local<v8::Value> Converter<yealink::rtvc::ContactNode>::ToV8(
//     v8::Isolate* isolate,
//     const yealink::rtvc::ContactNode& val) {
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

// bool Converter<yealink::rtvc::ContactNode>::FromV8(
//     v8::Isolate* isolate,
//     v8::Local<v8::Value> val,
//     yealink::rtvc::ContactNode* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::TerminalInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::TerminalInfo& val) {
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

bool Converter<yealink::rtvc::TerminalInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::TerminalInfo* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::AlarmInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::AlarmInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("filePath", val.file_path);
  handler.Set("code", val.code);
  handler.Set("name", val.name);
  handler.Set("type", val.type);
  handler.Set("level", val.level);
  handler.Set("desc", val.desc);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::AlarmInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::AlarmInfo* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::FeedbackInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::FeedbackInfo& val) {
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

bool Converter<yealink::rtvc::FeedbackInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::FeedbackInfo* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::PackageInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::PackageInfo& val) {
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

bool Converter<yealink::rtvc::PackageInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::PackageInfo* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::ConfigurationInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::ConfigurationInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("id", val.id);
  handler.Set("name", val.name);
  handler.Set("url", val.url);
  handler.Set("md5", val.md5);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::ConfigurationInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ConfigurationInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("id", &(out->id));
  dict.Get("name", &(out->name));
  dict.Get("url", &(out->url));
  dict.Get("md5", &(out->md5));

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::DownloadInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::DownloadInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("url", val.url);
  handler.Set("path", val.path);
  handler.Set("fileName", val.file_name);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::DownloadInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DownloadInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("url", &(out->url));
  dict.Get("path", &(out->path));
  dict.Get("fileName", &(out->file_name));

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::UploadLogInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::UploadLogInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("sessionId", val.session_id);
  handler.Set("path", val.file_path);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::UploadLogInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::UploadLogInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("sessionId", &(out->session_id));
  dict.Get("filePath", &(out->file_path));

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::NetCaptureInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::NetCaptureInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("sessionId", val.session_id);
  handler.Set("deviceId", val.device_id);
  handler.Set("path", val.path);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::NetCaptureInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::NetCaptureInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("sessionId", &(out->session_id));
  dict.Get("deviceId", &(out->device_id));
  dict.Get("path", &(out->path));

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::EventInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::EventInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("code", val.code);
  handler.Set("name", val.name);
  handler.Set("network", val.network);
  handler.Set("isp", val.isp);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::EventInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::EventInfo* out) {
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
v8::Local<v8::Value> Converter<yealink::rtvc::DescProfile>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::DescProfile val) {
  std::string profile;
  switch (val) {
    case yealink::rtvc::DescProfile::kConference:
      profile = "conference";
      break;
    case yealink::rtvc::DescProfile::kTeaching:
      profile = "education";
      break;
    case yealink::rtvc::DescProfile::kSeminar:
      profile = "seminar";
      break;
    case yealink::rtvc::DescProfile::kInvalid:
      profile = "";
      break;
  }
  return ConvertToV8(isolate, profile);
}

bool Converter<yealink::rtvc::DescProfile>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DescProfile* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "conference")
    *out = yealink::rtvc::DescProfile::kConference;
  else if (in == "education")
    *out = yealink::rtvc::DescProfile::kTeaching;
  else if (in == "seminar")
    *out = yealink::rtvc::DescProfile::kSeminar;
  else {
    *out = yealink::rtvc::DescProfile::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::DescPosition>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::DescPosition val) {
  std::string position;
  switch (val) {
    case yealink::rtvc::DescPosition::kTop:
      position = "top";
      break;
    case yealink::rtvc::DescPosition::kMedium:
      position = "medium";
      break;
    case yealink::rtvc::DescPosition::kBottom:
      position = "bottom";
      break;
    case yealink::rtvc::DescPosition::kInvalid:
      position = "";
      break;
  }
  return ConvertToV8(isolate, position);
}

bool Converter<yealink::rtvc::DescPosition>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DescPosition* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "top")
    *out = yealink::rtvc::DescPosition::kTop;
  else if (in == "medium")
    *out = yealink::rtvc::DescPosition::kMedium;
  else if (in == "bottom")
    *out = yealink::rtvc::DescPosition::kBottom;
  else {
    *out = yealink::rtvc::DescPosition::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::DescBanner>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::DescBanner& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("enabled", val.enabled);
  handler.Set("displayText", val.display_text);
  handler.Set("position", val.position);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::DescBanner>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DescBanner* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("enabled", &(out->enabled));
  dict.Get("displayText", &(out->display_text));
  dict.Get("position", &(out->position));

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::DescRtmpSessionType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::DescRtmpSessionType val) {
  std::string profile;
  switch (val) {
    case yealink::rtvc::DescRtmpSessionType::kAV:
      profile = "AV";
      break;
    case yealink::rtvc::DescRtmpSessionType::kAD:
      profile = "AD";
      break;
    case yealink::rtvc::DescRtmpSessionType::kAVD:
      profile = "AVD";
      break;
    case yealink::rtvc::DescRtmpSessionType::kInvalid:
      profile = "";
      break;
  }
  return ConvertToV8(isolate, profile);
}

bool Converter<yealink::rtvc::DescRtmpSessionType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DescRtmpSessionType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "AV")
    *out = yealink::rtvc::DescRtmpSessionType::kAV;
  else if (in == "AD")
    *out = yealink::rtvc::DescRtmpSessionType::kAD;
  else if (in == "AVD")
    *out = yealink::rtvc::DescRtmpSessionType::kAVD;
  else {
    *out = yealink::rtvc::DescRtmpSessionType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::DescRtmpFsType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::DescRtmpFsType val) {
  std::string profile;
  switch (val) {
    case yealink::rtvc::DescRtmpFsType::k360P:
      profile = "360P";
      break;
    case yealink::rtvc::DescRtmpFsType::k720P:
      profile = "720P";
      break;
    case yealink::rtvc::DescRtmpFsType::k1080P:
      profile = "1080P";
      break;
    case yealink::rtvc::DescRtmpFsType::kInvalid:
      profile = "";
      break;
  }
  return ConvertToV8(isolate, profile);
}

bool Converter<yealink::rtvc::DescRtmpFsType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DescRtmpFsType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "360P")
    *out = yealink::rtvc::DescRtmpFsType::k360P;
  else if (in == "720P")
    *out = yealink::rtvc::DescRtmpFsType::k720P;
  else if (in == "1080P")
    *out = yealink::rtvc::DescRtmpFsType::k1080P;
  else {
    *out = yealink::rtvc::DescRtmpFsType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::DescDefaultRtmp>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::DescDefaultRtmp& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("enabled", val.enabled);
  handler.Set("displayText", val.display_text);
  handler.Set("mcuSessionType", val.mcu_session_type);
  handler.Set("maxVideoFs", val.max_video_fs);
  handler.Set("webShareUrl", val.web_share_url);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::DescDefaultRtmp>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DescDefaultRtmp* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::DescUriPurpose>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::DescUriPurpose val) {
  std::string profile;
  switch (val) {
    case yealink::rtvc::DescUriPurpose::kFocus:
      profile = "focus";
      break;
    case yealink::rtvc::DescUriPurpose::kAudioVideo:
      profile = "audio-video";
      break;
    case yealink::rtvc::DescUriPurpose::kChat:
      profile = "chat";
      break;
    case yealink::rtvc::DescUriPurpose::kCoopShare:
      profile = "coopshare";
      break;
    case yealink::rtvc::DescUriPurpose::kApplicationSharing:
      profile = "applicationsharing";
      break;
    case yealink::rtvc::DescUriPurpose::kInvalid:
      profile = "";
      break;
  }
  return ConvertToV8(isolate, profile);
}

bool Converter<yealink::rtvc::DescUriPurpose>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DescUriPurpose* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "focus")
    *out = yealink::rtvc::DescUriPurpose::kFocus;
  else if (in == "audio-video")
    *out = yealink::rtvc::DescUriPurpose::kAudioVideo;
  else if (in == "chat")
    *out = yealink::rtvc::DescUriPurpose::kChat;
  else if (in == "coopshare")
    *out = yealink::rtvc::DescUriPurpose::kCoopShare;
  else if (in == "applicationsharing")
    *out = yealink::rtvc::DescUriPurpose::kApplicationSharing;
  else {
    *out = yealink::rtvc::DescUriPurpose::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::DescConfUriInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::DescConfUriInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("uri", val.uri);
  handler.Set("displayText", val.display_text);
  handler.Set("purpose", val.purpose);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::DescConfUriInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DescConfUriInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("uri", &(out->uri));
  dict.Get("displayText", &(out->display_text));
  dict.Get("purpose", &(out->purpose));

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::DescOrganizerInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::DescOrganizerInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("displayText", val.display_text);
  handler.Set("uid", val.uid);
  handler.Set("username", val.username);
  handler.Set("realm", val.realm);
  handler.Set("phone", val.phone);
  handler.Set("domain", val.domain);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::DescOrganizerInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DescOrganizerInfo* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::DescConferenceType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::DescConferenceType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::DescConferenceType::kVGCM:
      res = "VGCM";
      break;
    case yealink::rtvc::DescConferenceType::kVGCP:
      res = "VGCP";
      break;
    case yealink::rtvc::DescConferenceType::kVMN:
      res = "VMN";
      break;
    case yealink::rtvc::DescConferenceType::kVSC:
      res = "VSC";
      break;
    case yealink::rtvc::DescConferenceType::kVSCA:
      res = "VSCA";
      break;
    case yealink::rtvc::DescConferenceType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::DescConferenceType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DescConferenceType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "VGCM")
    *out = yealink::rtvc::DescConferenceType::kVGCM;
  else if (in == "VGCP")
    *out = yealink::rtvc::DescConferenceType::kVGCP;
  else if (in == "VMN")
    *out = yealink::rtvc::DescConferenceType::kVMN;
  else if (in == "VSC")
    *out = yealink::rtvc::DescConferenceType::kVSC;
  else if (in == "VSCA")
    *out = yealink::rtvc::DescConferenceType::kVSCA;
  else {
    *out = yealink::rtvc::DescConferenceType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::DescNumberType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::DescNumberType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::DescNumberType::kMeetNow:
      res = "meetnow";
      break;
    case yealink::rtvc::DescNumberType::kRecurrence:
      res = "recurrence";
      break;
    case yealink::rtvc::DescNumberType::kVMR:
      res = "vmr";
      break;
    case yealink::rtvc::DescNumberType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::DescNumberType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DescNumberType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "meetnow")
    *out = yealink::rtvc::DescNumberType::kMeetNow;
  else if (in == "recurrence")
    *out = yealink::rtvc::DescNumberType::kRecurrence;
  else if (in == "vmr")
    *out = yealink::rtvc::DescNumberType::kVMR;
  else {
    *out = yealink::rtvc::DescNumberType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::DescAdmissionPolicy>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::DescAdmissionPolicy val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::DescAdmissionPolicy::kClosedAuthenticated:
      res = "closedAuthenticated";
      break;
    case yealink::rtvc::DescAdmissionPolicy::kAnonumous:
      res = "anonymous";
      break;
    case yealink::rtvc::DescAdmissionPolicy::KOpenAuthenticated:
      res = "openAuthenticated";
      break;
    case yealink::rtvc::DescAdmissionPolicy::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::DescAdmissionPolicy>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DescAdmissionPolicy* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "closedAuthenticated")
    *out = yealink::rtvc::DescAdmissionPolicy::kClosedAuthenticated;
  else if (in == "anonymous")
    *out = yealink::rtvc::DescAdmissionPolicy::kAnonumous;
  else if (in == "openAuthenticated")
    *out = yealink::rtvc::DescAdmissionPolicy::KOpenAuthenticated;
  else {
    *out = yealink::rtvc::DescAdmissionPolicy::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::DescAttendeeByPass>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::DescAttendeeByPass val) {
  bool res;
  switch (val) {
    case yealink::rtvc::DescAttendeeByPass::kByPassTrue:
      res = true;
      break;
    case yealink::rtvc::DescAttendeeByPass::KByPassFalse:
      res = false;
      break;
    case yealink::rtvc::DescAttendeeByPass::kInvalid:
      res = false;
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::DescAttendeeByPass>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DescAttendeeByPass* out) {
  bool in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == true)
    *out = yealink::rtvc::DescAttendeeByPass::kByPassTrue;
  else if (in == false)
    *out = yealink::rtvc::DescAttendeeByPass::KByPassFalse;
  else {
    *out = yealink::rtvc::DescAttendeeByPass::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::DescAutoPromote>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::DescAutoPromote val) {
  int64_t res = 0;
  switch (val) {
    case yealink::rtvc::DescAutoPromote::kNone:
      res = 0;
      break;
    case yealink::rtvc::DescAutoPromote::kEveryOne:
      res = 2147483648;
      break;
    case yealink::rtvc::DescAutoPromote::kCompany:
      res = 32768;
      break;
    case yealink::rtvc::DescAutoPromote::kInvalid:
      res = -1;
      break;
  }
  return ConvertToV8(isolate, res);
}

v8::Local<v8::Value> Converter<yealink::rtvc::DescRecordType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::DescRecordType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::DescRecordType::kThirdParty:
      res = "third-party";
      break;
    case yealink::rtvc::DescRecordType::kYealinkRecord:
      res = "ylrecord";
      break;
    case yealink::rtvc::DescRecordType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::DescRecordType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DescRecordType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "third-party")
    *out = yealink::rtvc::DescRecordType::kThirdParty;
  else if (in == "ylrecord")
    *out = yealink::rtvc::DescRecordType::kYealinkRecord;
  else {
    *out = yealink::rtvc::DescRecordType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::DescRecordPrivilege>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::DescRecordPrivilege val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::DescRecordPrivilege::kOrganizer:
      res = "organizer";
      break;
    case yealink::rtvc::DescRecordPrivilege::kPresenter:
      res = "presenter";
      break;
    case yealink::rtvc::DescRecordPrivilege::kAttendee:
      res = "attendee";
      break;
    case yealink::rtvc::DescRecordPrivilege::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::DescRecordPrivilege>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DescRecordPrivilege* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "organizer")
    *out = yealink::rtvc::DescRecordPrivilege::kOrganizer;
  else if (in == "presenter")
    *out = yealink::rtvc::DescRecordPrivilege::kPresenter;
  else if (in == "attendee")
    *out = yealink::rtvc::DescRecordPrivilege::kAttendee;
  else {
    *out = yealink::rtvc::DescRecordPrivilege::kInvalid;
    return false;
  }

  return true;
}

bool Converter<yealink::rtvc::DescAutoPromote>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DescAutoPromote* out) {
  int64_t in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == 0)
    *out = yealink::rtvc::DescAutoPromote::kNone;
  else if (in == 2147483648)
    *out = yealink::rtvc::DescAutoPromote::kEveryOne;
  else if (in == 32768)
    *out = yealink::rtvc::DescAutoPromote::kCompany;
  else {
    *out = yealink::rtvc::DescAutoPromote::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::DescSetLockInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::DescSetLockInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("admissionPolicy", val.admission_policy);
  handler.Set("attendeeByPass", val.attendee_by_pass);
  handler.Set("autoPromote", val.auto_promote);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::DescSetLockInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DescSetLockInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("admissionPolicy", &(out->admission_policy));
  dict.Get("attendeeByPass", &(out->attendee_by_pass));
  dict.Get("autoPromote", &(out->auto_promote));

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::DescGetLockInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::DescGetLockInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("admissionPolicy", val.admission_policy);
  handler.Set("attendeeByPass", val.attendee_by_pass);
  handler.Set("autoPromote", val.auto_promote);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::DescGetLockInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::DescGetLockInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("admissionPolicy", &(out->admission_policy));
  dict.Get("attendeeByPass", &(out->attendee_by_pass));
  dict.Get("autoPromote", &(out->auto_promote));

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::DescInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::DescInfo& val) {
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

bool Converter<yealink::rtvc::DescInfo>::FromV8(v8::Isolate* isolate,
                                                v8::Local<v8::Value> val,
                                                yealink::rtvc::DescInfo* out) {
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
v8::Local<v8::Value> Converter<yealink::rtvc::RequesrResult>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::RequesrResult val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::RequesrResult::kSuccess:
      res = "success";
      break;
    case yealink::rtvc::RequesrResult::kInvalidParam:
      res = "invalid param";
      break;
    case yealink::rtvc::RequesrResult::kSipFailure:
      res = "sip failure";
      break;
    case yealink::rtvc::RequesrResult::kInvalid:
      res = "invalid";
      break;
    case yealink::rtvc::RequesrResult::kHttpFailure:
      res = "http failure";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::RequesrResult>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::RequesrResult* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "success")
    *out = yealink::rtvc::RequesrResult::kSuccess;
  else if (in == "invalid param")
    *out = yealink::rtvc::RequesrResult::kInvalidParam;
  else if (in == "sip failure")
    *out = yealink::rtvc::RequesrResult::kSipFailure;
  else if (in == "http failure")
    *out = yealink::rtvc::RequesrResult::kHttpFailure;
  else {
    *out = yealink::rtvc::RequesrResult::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::ResponseInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::ResponseInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("requestId", val.request_id);
  handler.Set("result", val.result);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::ResponseInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ResponseInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("requestId", &(out->request_id));
  dict.Get("result", &(out->result));

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::HttpResponseInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::HttpResponseInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("bizCode", val.biz_code);
  handler.Set("result", val.result);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::HttpResponseInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::HttpResponseInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("bizCode", &(out->biz_code));
  dict.Get("result", &(out->result));

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::UserProtocolType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::UserProtocolType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::UserProtocolType::kSIP:
      res = "SIP";
      break;
    case yealink::rtvc::UserProtocolType::kH323:
      res = "H323";
      break;
    case yealink::rtvc::UserProtocolType::kRTMP:
      res = "RTMP";
      break;
    case yealink::rtvc::UserProtocolType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::UserProtocolType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::UserProtocolType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "SIP")
    *out = yealink::rtvc::UserProtocolType::kSIP;
  else if (in == "H323")
    *out = yealink::rtvc::UserProtocolType::kH323;
  else if (in == "RTMP")
    *out = yealink::rtvc::UserProtocolType::kRTMP;
  else {
    *out = yealink::rtvc::UserProtocolType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::UserPermissionType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::UserPermissionType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::UserPermissionType::kAttendee:
      res = "attendee";
      break;
    case yealink::rtvc::UserPermissionType::kCastviewer:
      res = "castviewer";
      break;
    case yealink::rtvc::UserPermissionType::kOrganizer:
      res = "organizer";
      break;
    case yealink::rtvc::UserPermissionType::kPresenter:
      res = "presenter";
      break;
    case yealink::rtvc::UserPermissionType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::UserPermissionType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::UserPermissionType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "attendee")
    *out = yealink::rtvc::UserPermissionType::kAttendee;
  else if (in == "castviewer")
    *out = yealink::rtvc::UserPermissionType::kCastviewer;
  else if (in == "organizer")
    *out = yealink::rtvc::UserPermissionType::kOrganizer;
  else if (in == "presenter")
    *out = yealink::rtvc::UserPermissionType::kPresenter;
  else {
    *out = yealink::rtvc::UserPermissionType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::UserDemoStateType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::UserDemoStateType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::UserDemoStateType::kAudience:
      res = "audience";
      break;
    case yealink::rtvc::UserDemoStateType::kDemonstrator:
      res = "demonstrator";
      break;
    case yealink::rtvc::UserDemoStateType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::UserDemoStateType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::UserDemoStateType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "audience")
    *out = yealink::rtvc::UserDemoStateType::kAudience;
  else if (in == "demonstrator")
    *out = yealink::rtvc::UserDemoStateType::kDemonstrator;
  else {
    *out = yealink::rtvc::UserDemoStateType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::PresenterDemoStateType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::PresenterDemoStateType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::PresenterDemoStateType::kAudience:
      res = "audience";
      break;
    case yealink::rtvc::PresenterDemoStateType::kDemonstrator:
      res = "demonstrator";
      break;
    case yealink::rtvc::PresenterDemoStateType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::PresenterDemoStateType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::PresenterDemoStateType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "audience")
    *out = yealink::rtvc::PresenterDemoStateType::kAudience;
  else if (in == "demonstrator")
    *out = yealink::rtvc::PresenterDemoStateType::kDemonstrator;
  else {
    *out = yealink::rtvc::PresenterDemoStateType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::UserRolesInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::UserRolesInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("permission", val.permission);
  handler.Set("demostate", val.demostate);
  handler.Set("presenterDemostate", val.presenter_demostate);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::UserRolesInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::UserRolesInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("permission", &(out->permission));
  dict.Get("demostate", &(out->demostate));
  dict.Get("presenterDemostate", &(out->presenter_demostate));

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::UserEndpointSeesionType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::UserEndpointSeesionType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::UserEndpointSeesionType::kApplicationSharing:
      res = "applicationsharing";
      break;
    case yealink::rtvc::UserEndpointSeesionType::kAudioVideo:
      res = "audio-video";
      break;
    case yealink::rtvc::UserEndpointSeesionType::kChat:
      res = "chat";
      break;
    case yealink::rtvc::UserEndpointSeesionType::kCoopshare:
      res = "coopshare";
      break;
    case yealink::rtvc::UserEndpointSeesionType::kFocus:
      res = "focus";
      break;
    case yealink::rtvc::UserEndpointSeesionType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::UserEndpointSeesionType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::UserEndpointSeesionType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "applicationsharing")
    *out = yealink::rtvc::UserEndpointSeesionType::kApplicationSharing;
  else if (in == "audio-video")
    *out = yealink::rtvc::UserEndpointSeesionType::kAudioVideo;
  else if (in == "chat")
    *out = yealink::rtvc::UserEndpointSeesionType::kChat;
  else if (in == "coopshare")
    *out = yealink::rtvc::UserEndpointSeesionType::kCoopshare;
  else if (in == "focus")
    *out = yealink::rtvc::UserEndpointSeesionType::kFocus;
  else {
    *out = yealink::rtvc::UserEndpointSeesionType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::UserEndpointStatusType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::UserEndpointStatusType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::UserEndpointStatusType::kConnected:
      res = "connected";
      break;
    case yealink::rtvc::UserEndpointStatusType::kDialingIn:
      res = "dialing-in";
      break;
    case yealink::rtvc::UserEndpointStatusType::kDialingOut:
      res = "dialing-out";
      break;
    case yealink::rtvc::UserEndpointStatusType::kDisconnected:
      res = "disconnected";
      break;
    case yealink::rtvc::UserEndpointStatusType::kOnHold:
      res = "on-hold";
      break;
    case yealink::rtvc::UserEndpointStatusType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::UserEndpointStatusType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::UserEndpointStatusType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "connected")
    *out = yealink::rtvc::UserEndpointStatusType::kConnected;
  else if (in == "dialing-in")
    *out = yealink::rtvc::UserEndpointStatusType::kDialingIn;
  else if (in == "dialing-out")
    *out = yealink::rtvc::UserEndpointStatusType::kDialingOut;
  else if (in == "disconnected")
    *out = yealink::rtvc::UserEndpointStatusType::kDisconnected;
  else if (in == "on-hold")
    *out = yealink::rtvc::UserEndpointStatusType::kOnHold;
  else {
    *out = yealink::rtvc::UserEndpointStatusType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::UserJoinMethod>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::UserJoinMethod val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::UserJoinMethod::kDialedIn:
      res = "dialed-in";
      break;
    case yealink::rtvc::UserJoinMethod::kDialedOut:
      res = "dialed-out";
      break;
    case yealink::rtvc::UserJoinMethod::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::UserJoinMethod>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::UserJoinMethod* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "dialed-in")
    *out = yealink::rtvc::UserJoinMethod::kDialedIn;
  else if (in == "dialed-out")
    *out = yealink::rtvc::UserJoinMethod::kDialedOut;
  else {
    *out = yealink::rtvc::UserJoinMethod::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::UserMediaType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::UserMediaType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::UserMediaType::kApplication:
      res = "application";
      break;
    case yealink::rtvc::UserMediaType::kAudio:
      res = "audio";
      break;
    case yealink::rtvc::UserMediaType::kVideo:
      res = "video";
      break;
    case yealink::rtvc::UserMediaType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::UserMediaType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::UserMediaType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "application")
    *out = yealink::rtvc::UserMediaType::kApplication;
  else if (in == "audio")
    *out = yealink::rtvc::UserMediaType::kAudio;
  else if (in == "video")
    *out = yealink::rtvc::UserMediaType::kVideo;
  else {
    *out = yealink::rtvc::UserMediaType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::UserMediaLabelType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::UserMediaLabelType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::UserMediaLabelType::kApplication:
      res = "application";
      break;
    case yealink::rtvc::UserMediaLabelType::kFecc:
      res = "fecc";
      break;
    case yealink::rtvc::UserMediaLabelType::kMainAudio:
      res = "main-audio";
      break;
    case yealink::rtvc::UserMediaLabelType::kMainVideo:
      res = "main-video";
      break;
    case yealink::rtvc::UserMediaLabelType::kInvalid:
      res = "main-video";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::UserMediaLabelType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::UserMediaLabelType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "application")
    *out = yealink::rtvc::UserMediaLabelType::kApplication;
  else if (in == "fecc")
    *out = yealink::rtvc::UserMediaLabelType::kFecc;
  else if (in == "main-audio")
    *out = yealink::rtvc::UserMediaLabelType::kMainAudio;
  else if (in == "main-video")
    *out = yealink::rtvc::UserMediaLabelType::kMainVideo;
  else {
    *out = yealink::rtvc::UserMediaLabelType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::UserMediaDirectionType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::UserMediaDirectionType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::UserMediaDirectionType::kInactive:
      res = "inactive";
      break;
    case yealink::rtvc::UserMediaDirectionType::kRecvOnly:
      res = "recvonly";
      break;
    case yealink::rtvc::UserMediaDirectionType::kSendOnly:
      res = "sendonly";
      break;
    case yealink::rtvc::UserMediaDirectionType::kSendRecv:
      res = "sendrecv";
      break;
    case yealink::rtvc::UserMediaDirectionType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::UserMediaDirectionType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::UserMediaDirectionType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "inactive")
    *out = yealink::rtvc::UserMediaDirectionType::kInactive;
  else if (in == "recvonly")
    *out = yealink::rtvc::UserMediaDirectionType::kRecvOnly;
  else if (in == "sendonly")
    *out = yealink::rtvc::UserMediaDirectionType::kSendOnly;
  else if (in == "sendrecv")
    *out = yealink::rtvc::UserMediaDirectionType::kSendRecv;
  else {
    *out = yealink::rtvc::UserMediaDirectionType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::UserMediafilterType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::UserMediafilterType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::UserMediafilterType::kBlock:
      res = "block";
      break;
    case yealink::rtvc::UserMediafilterType::kUnblock:
      res = "unblock";
      break;
    case yealink::rtvc::UserMediafilterType::kUnblocking:
      res = "unblocking";
      break;
    case yealink::rtvc::UserMediafilterType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::UserMediafilterType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::UserMediafilterType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "block")
    *out = yealink::rtvc::UserMediafilterType::kBlock;
  else if (in == "unblock")
    *out = yealink::rtvc::UserMediafilterType::kUnblock;
  else if (in == "unblocking")
    *out = yealink::rtvc::UserMediafilterType::kUnblocking;
  else {
    *out = yealink::rtvc::UserMediafilterType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::UserMediaBlockByType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::UserMediaBlockByType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::UserMediaBlockByType::kClient:
      res = "client";
      break;
    case yealink::rtvc::UserMediaBlockByType::kNone:
      res = "none";
      break;
    case yealink::rtvc::UserMediaBlockByType::kServer:
      res = "server";
      break;
    case yealink::rtvc::UserMediaBlockByType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::UserMediaBlockByType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::UserMediaBlockByType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "client")
    *out = yealink::rtvc::UserMediaBlockByType::kClient;
  else if (in == "none")
    *out = yealink::rtvc::UserMediaBlockByType::kNone;
  else if (in == "server")
    *out = yealink::rtvc::UserMediaBlockByType::kServer;
  else {
    *out = yealink::rtvc::UserMediaBlockByType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::UserMediaInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::UserMediaInfo& val) {
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

bool Converter<yealink::rtvc::UserMediaInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::UserMediaInfo* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::UserMediaFilterInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::UserMediaFilterInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("mediaEgressBlockBy", val.media_egress_block_by);
  handler.Set("mediaEgressFilter", val.media_egress_filter);
  handler.Set("mediaIngressBlockBy", val.media_ingress_block_by);
  handler.Set("mediaIngressFilter", val.media_ingress_filter);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::UserMediaFilterInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::UserMediaFilterInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("mediaEgressBlockBy", &(out->media_egress_block_by));
  dict.Get("mediaEgressFilter", &(out->media_egress_filter));
  dict.Get("mediaIngressBlockBy", &(out->media_ingress_block_by));
  dict.Get("mediaIngressFilter", &(out->media_ingress_filter));

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::UserEndpointInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::UserEndpointInfo& val) {
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

bool Converter<yealink::rtvc::UserEndpointInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::UserEndpointInfo* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::UserInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::UserInfo& val) {
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

bool Converter<yealink::rtvc::UserInfo>::FromV8(v8::Isolate* isolate,
                                                v8::Local<v8::Value> val,
                                                yealink::rtvc::UserInfo* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::UserMediaDataInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::UserMediaDataInfo& val) {
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

bool Converter<yealink::rtvc::UserMediaDataInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::UserMediaDataInfo* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::UserStatisticsInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::UserStatisticsInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("mediaId", val.media_id);
  handler.Set("label", val.label);
  handler.Set("type", val.type);
  handler.Set("send", val.send);
  handler.Set("recv", val.recv);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::UserStatisticsInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::UserStatisticsInfo* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::RecordStatusType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::RecordStatusType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::RecordStatusType::kInvalid:
      res = "";
      break;
    case yealink::rtvc::RecordStatusType::kPause:
      res = "pause";
      break;
    case yealink::rtvc::RecordStatusType::kPausing:
      res = "pausing";
      break;
    case yealink::rtvc::RecordStatusType::kResume:
      res = "resume";
      break;
    case yealink::rtvc::RecordStatusType::kResuming:
      res = "resuming";
      break;
    case yealink::rtvc::RecordStatusType::kStart:
      res = "start";
      break;
    case yealink::rtvc::RecordStatusType::kStarting:
      res = "starting";
      break;
    case yealink::rtvc::RecordStatusType::kStop:
      res = "stop";
      break;
    case yealink::rtvc::RecordStatusType::kStopping:
      res = "stopping";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::RecordStatusType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::RecordStatusType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "pause")
    *out = yealink::rtvc::RecordStatusType::kPause;
  else if (in == "pausing")
    *out = yealink::rtvc::RecordStatusType::kPausing;
  else if (in == "resume")
    *out = yealink::rtvc::RecordStatusType::kResume;
  else if (in == "resuming")
    *out = yealink::rtvc::RecordStatusType::kResuming;
  else if (in == "start")
    *out = yealink::rtvc::RecordStatusType::kStart;
  else if (in == "starting")
    *out = yealink::rtvc::RecordStatusType::kStarting;
  else if (in == "stop")
    *out = yealink::rtvc::RecordStatusType::kStop;
  else if (in == "stopping")
    *out = yealink::rtvc::RecordStatusType::kStopping;
  else {
    *out = yealink::rtvc::RecordStatusType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::RecordUserInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::RecordUserInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("recordLastStartTime", val.record_last_start_time);
  handler.Set("recordLastStopDuration", val.record_last_stop_duration);
  handler.Set("recordStatus", val.record_status);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::RecordUserInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::RecordUserInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("recordLastStartTime", &(out->record_last_start_time));
  dict.Get("recordLastStopDuration", &(out->record_last_stop_duration));
  dict.Get("recordStatus", &(out->record_status));

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::RecordUsers>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::RecordUsers& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("user", val.user);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::RecordUsers>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::RecordUsers* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("user", &(out->user));

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::RtmpStatusType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::RtmpStatusType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::RtmpStatusType::kInvalid:
      res = "";
      break;
    case yealink::rtvc::RtmpStatusType::kPause:
      res = "pause";
      break;
    case yealink::rtvc::RtmpStatusType::kPausing:
      res = "pausing";
      break;
    case yealink::rtvc::RtmpStatusType::kResume:
      res = "resume";
      break;
    case yealink::rtvc::RtmpStatusType::kResuming:
      res = "resuming";
      break;
    case yealink::rtvc::RtmpStatusType::kStart:
      res = "start";
      break;
    case yealink::rtvc::RtmpStatusType::kStarting:
      res = "starting";
      break;
    case yealink::rtvc::RtmpStatusType::kStop:
      res = "stop";
      break;
    case yealink::rtvc::RtmpStatusType::kStopping:
      res = "stopping";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::RtmpStatusType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::RtmpStatusType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "pause")
    *out = yealink::rtvc::RtmpStatusType::kPause;
  else if (in == "pausing")
    *out = yealink::rtvc::RtmpStatusType::kPausing;
  else if (in == "resume")
    *out = yealink::rtvc::RtmpStatusType::kResume;
  else if (in == "resuming")
    *out = yealink::rtvc::RtmpStatusType::kResuming;
  else if (in == "start")
    *out = yealink::rtvc::RtmpStatusType::kStart;
  else if (in == "starting")
    *out = yealink::rtvc::RtmpStatusType::kStarting;
  else if (in == "stop")
    *out = yealink::rtvc::RtmpStatusType::kStop;
  else if (in == "stopping")
    *out = yealink::rtvc::RtmpStatusType::kStopping;
  else {
    *out = yealink::rtvc::RtmpStatusType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::RtmpUserInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::RtmpUserInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("entity", val.entity);
  handler.Set("isDefault", val.is_default);
  handler.Set("rtmpStatus", val.rtmp_status);
  handler.Set("rtmpLastStopDuration", val.rtmp_last_start_time);
  handler.Set("rtmpLastStartTime", val.rtmp_last_stop_duration);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::RtmpUserInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::RtmpUserInfo* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::RtmpInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::RtmpInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("enable", val.enable);
  handler.Set("users", val.users);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::RtmpInfo>::FromV8(v8::Isolate* isolate,
                                                v8::Local<v8::Value> val,
                                                yealink::rtvc::RtmpInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;

  dict.Get("enable", &(out->enable));
  dict.Get("users", &(out->users));

  return true;
}

// view
v8::Local<v8::Value> Converter<yealink::rtvc::ViewSpeakMode>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::ViewSpeakMode val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::ViewSpeakMode::kFree:
      res = "free";
      break;
    case yealink::rtvc::ViewSpeakMode::kHandUp:
      res = "handUp";
      break;
    case yealink::rtvc::ViewSpeakMode::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::ViewSpeakMode>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ViewSpeakMode* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "free")
    *out = yealink::rtvc::ViewSpeakMode::kFree;
  else if (in == "handUp")
    *out = yealink::rtvc::ViewSpeakMode::kHandUp;
  else {
    *out = yealink::rtvc::ViewSpeakMode::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::ViewLayoutType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::ViewLayoutType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::ViewLayoutType::kEquality:
      res = "Equality";
      break;
    case yealink::rtvc::ViewLayoutType::kPresentation:
      res = "Presentation";
      break;
    case yealink::rtvc::ViewLayoutType::kSpeechExcitation:
      res = "SpeechExcitation";
      break;
    case yealink::rtvc::ViewLayoutType::kExclusive:
      res = "Exclusive";
      break;
    case yealink::rtvc::ViewLayoutType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::ViewLayoutType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ViewLayoutType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "Equality")
    *out = yealink::rtvc::ViewLayoutType::kEquality;
  else if (in == "Presentation")
    *out = yealink::rtvc::ViewLayoutType::kPresentation;
  else if (in == "SpeechExcitation")
    *out = yealink::rtvc::ViewLayoutType::kSpeechExcitation;
  else if (in == "Exclusive")
    *out = yealink::rtvc::ViewLayoutType::kExclusive;
  else {
    *out = yealink::rtvc::ViewLayoutType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::ViewPresenterLayoutType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::ViewPresenterLayoutType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::ViewPresenterLayoutType::kEquality:
      res = "Equality";
      break;
    case yealink::rtvc::ViewPresenterLayoutType::kSpeechExcitation:
      res = "SpeechExcitation";
      break;
    case yealink::rtvc::ViewPresenterLayoutType::kExclusive:
      res = "Exclusive";
      break;
    case yealink::rtvc::ViewPresenterLayoutType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::ViewPresenterLayoutType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ViewPresenterLayoutType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "Equality")
    *out = yealink::rtvc::ViewPresenterLayoutType::kEquality;
  else if (in == "SpeechExcitation")
    *out = yealink::rtvc::ViewPresenterLayoutType::kSpeechExcitation;
  else if (in == "Exclusive")
    *out = yealink::rtvc::ViewPresenterLayoutType::kExclusive;
  else {
    *out = yealink::rtvc::ViewPresenterLayoutType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::GetLayoutInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::GetLayoutInfo& val) {
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

bool Converter<yealink::rtvc::GetLayoutInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::GetLayoutInfo* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::SetLayoutInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::SetLayoutInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("videoLayout", val.video_layout);
  handler.Set("videoMaxView", val.video_max_view);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::SetLayoutInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::SetLayoutInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("videoLayout", &(out->video_layout));
  dict.Get("videoMaxView", &(out->video_max_view));

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::ViewFilterRoleType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::ViewFilterRoleType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::ViewFilterRoleType::kDefault:
      res = "default";
      break;
    case yealink::rtvc::ViewFilterRoleType::kAttendee:
      res = "attendee";
      break;
    case yealink::rtvc::ViewFilterRoleType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::ViewFilterRoleType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ViewFilterRoleType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "default")
    *out = yealink::rtvc::ViewFilterRoleType::kDefault;
  else if (in == "attendee")
    *out = yealink::rtvc::ViewFilterRoleType::kAttendee;
  else {
    *out = yealink::rtvc::ViewFilterRoleType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::ViewFilterType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::ViewFilterType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::ViewFilterType::kBlock:
      res = "block";
      break;
    case yealink::rtvc::ViewFilterType::kUnBlock:
      res = "unblock";
      break;
    case yealink::rtvc::ViewFilterType::kInvalid:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::ViewFilterType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ViewFilterType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "block")
    *out = yealink::rtvc::ViewFilterType::kBlock;
  else if (in == "unblock")
    *out = yealink::rtvc::ViewFilterType::kUnBlock;
  else {
    *out = yealink::rtvc::ViewFilterType::kInvalid;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::ViewFilterRuleInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::ViewFilterRuleInfo& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);
  handler.Set("role", val.role);
  handler.Set("ingress", val.ingress);
  handler.Set("egress", val.egress);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::ViewFilterRuleInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ViewFilterRuleInfo* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("role", &(out->role));
  dict.Get("ingress", &(out->ingress));
  dict.Get("egress", &(out->egress));

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::StatsAudioCodecType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::StatsAudioCodecType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::StatsAudioCodecType::kAACLC:
      res = "AACLC";
      break;
    case yealink::rtvc::StatsAudioCodecType::kARES:
      res = "ARES";
      break;
    case yealink::rtvc::StatsAudioCodecType::kG7221:
      res = "G7221";
      break;
    case yealink::rtvc::StatsAudioCodecType::kG72221C:
      res = "G7221C";
      break;
    case yealink::rtvc::StatsAudioCodecType::kG722:
      res = "G722";
      break;
    case yealink::rtvc::StatsAudioCodecType::kG729:
      res = "G729";
      break;
    case yealink::rtvc::StatsAudioCodecType::kNone:
      res = "";
      break;
    case yealink::rtvc::StatsAudioCodecType::kOPUS:
      res = "OPUS";
      break;
    case yealink::rtvc::StatsAudioCodecType::kPCMA:
      res = "PCMA";
      break;
    case yealink::rtvc::StatsAudioCodecType::kPCMU:
      res = "PCMU";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::StatsAudioCodecType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::StatsAudioCodecType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "AACLC")
    *out = yealink::rtvc::StatsAudioCodecType::kAACLC;
  else if (in == "ARES")
    *out = yealink::rtvc::StatsAudioCodecType::kARES;
  else if (in == "G7221")
    *out = yealink::rtvc::StatsAudioCodecType::kG7221;
  else if (in == "G72221C")
    *out = yealink::rtvc::StatsAudioCodecType::kG72221C;
  else if (in == "G722")
    *out = yealink::rtvc::StatsAudioCodecType::kG722;
  else if (in == "G729")
    *out = yealink::rtvc::StatsAudioCodecType::kG729;
  else if (in == "OPUS")
    *out = yealink::rtvc::StatsAudioCodecType::kOPUS;
  else if (in == "PCMA")
    *out = yealink::rtvc::StatsAudioCodecType::kPCMA;
  else if (in == "PCMU")
    *out = yealink::rtvc::StatsAudioCodecType::kPCMU;
  else {
    *out = yealink::rtvc::StatsAudioCodecType::kNone;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::StatsVideoCodecType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::StatsVideoCodecType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::StatsVideoCodecType::kH263:
      res = "H263";
      break;
    case yealink::rtvc::StatsVideoCodecType::kH264:
      res = "H264";
      break;
    case yealink::rtvc::StatsVideoCodecType::kNone:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::StatsVideoCodecType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::StatsVideoCodecType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "H263")
    *out = yealink::rtvc::StatsVideoCodecType::kH263;
  else if (in == "H264")
    *out = yealink::rtvc::StatsVideoCodecType::kH264;
  else {
    *out = yealink::rtvc::StatsVideoCodecType::kNone;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::StatsVideoProfileType>::ToV8(
    v8::Isolate* isolate,
    yealink::rtvc::StatsVideoProfileType val) {
  std::string res;
  switch (val) {
    case yealink::rtvc::StatsVideoProfileType::kBase:
      res = "base";
      break;
    case yealink::rtvc::StatsVideoProfileType::kHigh:
      res = "high";
      break;
    case yealink::rtvc::StatsVideoProfileType::kMain:
      res = "main";
      break;
    case yealink::rtvc::StatsVideoProfileType::kMax:
      res = "max";
      break;
    case yealink::rtvc::StatsVideoProfileType::kNone:
      res = "";
      break;
  }
  return ConvertToV8(isolate, res);
}

bool Converter<yealink::rtvc::StatsVideoProfileType>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::StatsVideoProfileType* out) {
  std::string in;
  if (!ConvertFromV8(isolate, val, &in))
    return false;

  if (in == "base")
    *out = yealink::rtvc::StatsVideoProfileType::kBase;
  else if (in == "high")
    *out = yealink::rtvc::StatsVideoProfileType::kHigh;
  else if (in == "main")
    *out = yealink::rtvc::StatsVideoProfileType::kMain;
  else if (in == "max")
    *out = yealink::rtvc::StatsVideoProfileType::kMax;
  else {
    *out = yealink::rtvc::StatsVideoProfileType::kNone;
    return false;
  }

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::AudioStatsInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::AudioStatsInfo& val) {
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

bool Converter<yealink::rtvc::AudioStatsInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::AudioStatsInfo* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::VideoStatsInfo>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::VideoStatsInfo& val) {
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

bool Converter<yealink::rtvc::VideoStatsInfo>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::VideoStatsInfo* out) {
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

v8::Local<v8::Value> Converter<yealink::rtvc::RTCVideoStats>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::RTCVideoStats& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("inbound", val.inbound);
  handler.Set("outbound", val.outbound);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::RTCVideoStats>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::RTCVideoStats* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("inbound", &(out->inbound));
  dict.Get("outbound", &(out->outbound));

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::RTCAudioStats>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::RTCAudioStats& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("inbound", val.inbound);
  handler.Set("outbound", val.outbound);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::RTCAudioStats>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::RTCAudioStats* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("inbound", &(out->inbound));
  dict.Get("outbound", &(out->outbound));

  return true;
}

v8::Local<v8::Value> Converter<yealink::rtvc::RTCStats>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::RTCStats& val) {
  Dictionary handler = Dictionary::CreateEmpty(isolate);

  handler.Set("video", val.video);
  handler.Set("audio", val.audio);

  return handler.GetHandle();
}

bool Converter<yealink::rtvc::RTCStats>::FromV8(v8::Isolate* isolate,
                                                v8::Local<v8::Value> val,
                                                yealink::rtvc::RTCStats* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("video", &(out->video));
  dict.Get("audio", &(out->audio));

  return true;
}

}  // namespace mate
