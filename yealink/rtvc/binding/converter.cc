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

v8::Local<v8::Value> Converter<yealink::rtvc::ContactNode>::ToV8(
    v8::Isolate* isolate,
    const yealink::rtvc::ContactNode& val) {
  Dictionary dict = Dictionary::CreateEmpty(isolate);
  dict.Set("id", val.id);
  dict.Set("type", val.type);
  dict.Set("parentId", val.parentId);
  dict.Set("childCounts", val.childCounts);
  dict.Set("name", val.name);
  dict.Set("i18nName", val.i18nName);
  dict.Set("pinyin", val.pinyin);
  dict.Set("pinyinAbbr", val.pinyinAbbr);
  dict.Set("email", val.email);
  dict.Set("phone", val.phone);
  dict.Set("mobile", val.mobile);
  dict.Set("number", val.number);
  dict.Set("fullNumber", val.fullNumber);
  return dict.GetHandle();
}

bool Converter<yealink::rtvc::ContactNode>::FromV8(
    v8::Isolate* isolate,
    v8::Local<v8::Value> val,
    yealink::rtvc::ContactNode* out) {
  Dictionary dict;
  if (!ConvertFromV8(isolate, val, &dict))
    return false;
  dict.Get("id", &(out->id));
  dict.Get("type", &(out->type));
  dict.Get("parentId", &(out->parentId));
  dict.Get("childCounts", &(out->childCounts));
  dict.Get("name", &(out->name));
  dict.Get("i18nName", &(out->i18nName));
  dict.Get("pinyin", &(out->pinyin));
  dict.Get("pinyinAbbr", &(out->pinyinAbbr));
  dict.Get("email", &(out->email));
  dict.Get("phone", &(out->phone));
  dict.Get("mobile", &(out->mobile));
  dict.Get("number", &(out->number));
  dict.Get("fullNumber", &(out->fullNumber));
  return true;
}

}  // namespace mate
