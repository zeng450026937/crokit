#include "yealink/rtvc/binding/conference_description_binding.h"

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace rtvc {

mate::Handle<ConferenceDescriptionBinding> ConferenceDescriptionBinding::Create(
    v8::Isolate* isolate,
    yealink::RoomController* controller) {
  return mate::CreateHandle(
      isolate, new ConferenceDescriptionBinding(isolate, controller));
}

// static
void ConferenceDescriptionBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "ConferenceDescription"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("subject", &ConferenceDescriptionBinding::subject)
      .SetProperty("startTime", &ConferenceDescriptionBinding::startTime)
      .SetProperty("banner", &ConferenceDescriptionBinding::banner)
      .SetProperty("defaultRtmp", &ConferenceDescriptionBinding::defaultRtmp)
      .SetProperty("profile", &ConferenceDescriptionBinding::profile)
      .SetProperty("recordId", &ConferenceDescriptionBinding::recordId)
      .SetProperty("confUris", &ConferenceDescriptionBinding::confUris)
      .SetProperty("organizer", &ConferenceDescriptionBinding::organizer)
      .SetProperty("conferenceId", &ConferenceDescriptionBinding::conferenceId)
      .SetProperty("conferenceNumber",
                   &ConferenceDescriptionBinding::conferenceNumber)
      .SetProperty("conferenceType",
                   &ConferenceDescriptionBinding::conferenceType)
      .SetProperty("conferenceNumberType",
                   &ConferenceDescriptionBinding::conferenceNumberType)
      .SetProperty("bookStartTime",
                   &ConferenceDescriptionBinding::bookStartTime)
      .SetProperty("bookExpiryTime",
                   &ConferenceDescriptionBinding::bookExpiryTime)
      .SetProperty("presenterPin", &ConferenceDescriptionBinding::presenterPin)
      .SetProperty("attendeePin", &ConferenceDescriptionBinding::attendeePin)
      .SetProperty("maximumUserCount",
                   &ConferenceDescriptionBinding::maximumUserCount)
      .SetProperty("admissionPolicy",
                   &ConferenceDescriptionBinding::admissionPolicy)
      .SetProperty("lobbyCapable", &ConferenceDescriptionBinding::lobbyCapable)
      .SetProperty("attendeeByPass",
                   &ConferenceDescriptionBinding::attendeeByPass)
      .SetProperty("autoPromote", &ConferenceDescriptionBinding::autoPromote)
      .SetProperty("serverMode", &ConferenceDescriptionBinding::serverMode)
      .SetProperty("interactiveBroadcastEnabled",
                   &ConferenceDescriptionBinding::interactiveBroadcastEnabled)
      .SetProperty("enterpriseId", &ConferenceDescriptionBinding::enterpriseId)
      .SetProperty("videoEnable", &ConferenceDescriptionBinding::videoEnable)
      .SetProperty("ipcallEnable", &ConferenceDescriptionBinding::ipcallEnable)
      .SetProperty("webrtcEnable", &ConferenceDescriptionBinding::webrtcEnable)
      .SetProperty("recordServerType",
                   &ConferenceDescriptionBinding::recordServerType)
      .SetProperty("recordPrivilege",
                   &ConferenceDescriptionBinding::recordPrivilege)
      .SetProperty("confInfoUrl", &ConferenceDescriptionBinding::confInfoUrl)
      .SetMethod("getDefaultRtmp",
                 &ConferenceDescriptionBinding::GetDefaultRtmp)
      .SetMethod("getLock", &ConferenceDescriptionBinding::GetLock)
      .SetMethod("setLock", &ConferenceDescriptionBinding::SetLock)
      .SetMethod("getShareInfo", &ConferenceDescriptionBinding::GetShareInfo);
}

void ConferenceDescriptionBinding::UpdateRoomController(
    yealink::RoomController* handler) {
  room_controller_ = handler;
}

void ConferenceDescriptionBinding::UpdatePendingHandler(
    std::unordered_map<int64_t, Promise>* handler) {
  pending_requests_ = handler;
}

ConferenceDescriptionBinding::ConferenceDescriptionBinding(
    v8::Isolate* isolate,
    v8::Local<v8::Object> wrapper)
    : weak_factory_(this), pending_requests_(nullptr) {
  InitWith(isolate, wrapper);
}

ConferenceDescriptionBinding::ConferenceDescriptionBinding(
    v8::Isolate* isolate,
    yealink::RoomController* controller)
    : weak_factory_(this), pending_requests_(nullptr) {
  Init(isolate);
  room_controller_ = controller;
}

ConferenceDescriptionBinding::~ConferenceDescriptionBinding() = default;

std::string ConferenceDescriptionBinding::subject() {
  std::string subject = "";

  if (room_controller_)
    ConvertFrom(subject, room_controller_->GetDescriptionComponent()
                             .GetConferenceDescription()
                             .subject);

  return subject;
}
int64_t ConferenceDescriptionBinding::startTime() {
  int64_t value = 0;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .startTime);

  return value;
}
DescBanner ConferenceDescriptionBinding::banner() {
  DescBanner value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .banner);

  return value;
}
DescDefaultRtmp ConferenceDescriptionBinding::defaultRtmp() {
  DescDefaultRtmp value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .defaultRtmp);

  return value;
}
DescProfile ConferenceDescriptionBinding::profile() {
  DescProfile value = DescProfile::kInvalid;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .profile);

  return value;
}
std::string ConferenceDescriptionBinding::recordId() {
  std::string value = "";

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .recordId);

  return value;
}

std::vector<DescConfUriInfo> ConferenceDescriptionBinding::confUris() {
  std::vector<DescConfUriInfo> value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .confUris);

  return value;
}

DescOrganizerInfo ConferenceDescriptionBinding::organizer() {
  DescOrganizerInfo value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .organizer);

  return value;
}
std::string ConferenceDescriptionBinding::conferenceId() {
  std::string value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .conferenceId);

  return value;
}
std::string ConferenceDescriptionBinding::conferenceNumber() {
  std::string value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .conferenceNumber);

  return value;
}
DescConferenceType ConferenceDescriptionBinding::conferenceType() {
  DescConferenceType value = DescConferenceType::kInvalid;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .conferenceType);

  return value;
}
DescNumberType ConferenceDescriptionBinding::conferenceNumberType() {
  DescNumberType value = DescNumberType::kInvalid;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .conferenceNumberType);

  return value;
}
int64_t ConferenceDescriptionBinding::bookStartTime() {
  int64_t value = 0;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .bookStartTime);

  return value;
}
int64_t ConferenceDescriptionBinding::bookExpiryTime() {
  int64_t value = 0;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .bookExpiryTime);

  return value;
}
std::string ConferenceDescriptionBinding::presenterPin() {
  std::string value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .presenterPin);

  return value;
}
std::string ConferenceDescriptionBinding::attendeePin() {
  std::string value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .attendeePin);

  return value;
}
uint32_t ConferenceDescriptionBinding::maximumUserCount() {
  uint32_t value = 0;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .maximumUserCount);

  return value;
}
DescAdmissionPolicy ConferenceDescriptionBinding::admissionPolicy() {
  DescAdmissionPolicy value = DescAdmissionPolicy::kInvalid;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .admissionPolicy);

  return value;
}
bool ConferenceDescriptionBinding::lobbyCapable() {
  bool value = false;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .lobbyCapable);

  return value;
}
bool ConferenceDescriptionBinding::attendeeByPass() {
  bool value = false;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .attendeeByPass);

  return value;
}
DescAutoPromote ConferenceDescriptionBinding::autoPromote() {
  DescAutoPromote value = DescAutoPromote::kInvalid;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .autoPromote);

  return value;
}
std::string ConferenceDescriptionBinding::serverMode() {
  std::string value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .serverMode);

  return value;
}
bool ConferenceDescriptionBinding::interactiveBroadcastEnabled() {
  bool value = false;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .interactiveBroadcastEnabled);

  return value;
}
std::string ConferenceDescriptionBinding::enterpriseId() {
  std::string value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .enterpriseId);

  return value;
}
bool ConferenceDescriptionBinding::videoEnable() {
  bool value = false;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .videoEnable);

  return value;
}
bool ConferenceDescriptionBinding::ipcallEnable() {
  bool value = false;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .ipcallEnable);

  return value;
}
bool ConferenceDescriptionBinding::webrtcEnable() {
  bool value = false;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .webrtcEnable);

  return value;
}
DescRecordType ConferenceDescriptionBinding::recordServerType() {
  DescRecordType value = DescRecordType::kInvalid;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .recordServerType);

  return value;
}
DescRecordPrivilege ConferenceDescriptionBinding::recordPrivilege() {
  DescRecordPrivilege value = DescRecordPrivilege::kInvalid;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .recordPrivilege);

  return value;
}
std::string ConferenceDescriptionBinding::confInfoUrl() {
  std::string value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .confInfoUrl);

  return value;
}

DescDefaultRtmp ConferenceDescriptionBinding::GetDefaultRtmp() {
  DescDefaultRtmp value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .defaultRtmp);

  return value;
}

DescGetLockInfo ConferenceDescriptionBinding::GetLock() {
  DescGetLockInfo params;

  if (room_controller_) {
    ConvertFrom(params.admission_policy,
                room_controller_->GetDescriptionComponent()
                    .GetConferenceDescription()
                    .admissionPolicy);

    ConvertFrom(params.attendee_by_pass,
                room_controller_->GetDescriptionComponent()
                    .GetConferenceDescription()
                    .attendeeByPass);

    ConvertFrom(params.auto_promote, room_controller_->GetDescriptionComponent()
                                         .GetConferenceDescription()
                                         .autoPromote);
  }

  return params;
}

v8::Local<v8::Promise> ConferenceDescriptionBinding::SetLock(
    DescSetLockInfo params) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  if (room_controller_)
    room_controller_->GetViewComponent().ModifyConferenceLock(
        (yealink::ConferenceDescription::AdmissionPolicy)
            params.admission_policy,
        (yealink::ConferenceDescription::AttendeeByPass)params.attendee_by_pass,
        (yealink::ConferenceDescription::AutoPromote)params.auto_promote);

  std::move(promise).Resolve();

  return handle;
}

void ConferenceDescriptionBinding::DoSetLock(DescSetLockInfo params) {
  if (room_controller_)
    room_controller_->GetViewComponent().ModifyConferenceLock(
        (yealink::ConferenceDescription::AdmissionPolicy)
            params.admission_policy,
        (yealink::ConferenceDescription::AttendeeByPass)params.attendee_by_pass,
        (yealink::ConferenceDescription::AutoPromote)params.auto_promote);
}

v8::Local<v8::Promise> ConferenceDescriptionBinding::GetShareInfo(
    mate::Arguments* args) {
  std::string lang;
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  if (!args->GetNext(&lang)) {
    args->ThrowError("lang is required");
  }

  yealink::RequestResult result;

  if (room_controller_)
    result =
        room_controller_->GetDescriptionComponent().GetShareInfo(lang.c_str());

  if (pending_requests_) {
    pending_requests_->emplace(result.requestId, std::move(promise));
  } else {
    std::move(promise).Resolve();
  }

  return handle;
}

void ConferenceDescriptionBinding::DoGetShareInfo(std::string lang) {
  if (room_controller_)
    room_controller_->GetDescriptionComponent().GetShareInfo(lang.c_str());
}

void ConferenceDescriptionBinding::OnCommandCompeleted(Promise promise) {
  std::move(promise).Resolve(true);
}

}  // namespace rtvc
