#include "yealink/rtvc/binding/conference_description_binding.h"

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace yealink {

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
      .SetProperty("startTime", &ConferenceDescriptionBinding::StartTime)
      .SetProperty("banner", &ConferenceDescriptionBinding::Banner)
      .SetProperty("defaultRtmp", &ConferenceDescriptionBinding::DefaultRtmp)
      .SetProperty("profile", &ConferenceDescriptionBinding::Profile)
      .SetProperty("recordId", &ConferenceDescriptionBinding::RecordId)
      .SetProperty("confUris", &ConferenceDescriptionBinding::ConfUris)
      .SetProperty("organizer", &ConferenceDescriptionBinding::Organizer)
      .SetProperty("conferenceId", &ConferenceDescriptionBinding::ConferenceId)
      .SetProperty("conferenceNumber",
                   &ConferenceDescriptionBinding::ConferenceNumber)
      .SetProperty("conferenceType",
                   &ConferenceDescriptionBinding::ConferenceType)
      .SetProperty("conferenceNumberType",
                   &ConferenceDescriptionBinding::ConferenceNumberType)
      .SetProperty("bookStartTime",
                   &ConferenceDescriptionBinding::BookStartTime)
      .SetProperty("bookExpiryTime",
                   &ConferenceDescriptionBinding::BookExpiryTime)
      .SetProperty("presenterPin", &ConferenceDescriptionBinding::PresenterPin)
      .SetProperty("attendeePin", &ConferenceDescriptionBinding::AttendeePin)
      .SetProperty("maximumUserCount",
                   &ConferenceDescriptionBinding::MaximumUserCount)
      .SetProperty("admissionPolicy",
                   &ConferenceDescriptionBinding::AdmissionPolicy)
      .SetProperty("lobbyCapable", &ConferenceDescriptionBinding::LobbyCapable)
      .SetProperty("attendeeByPass",
                   &ConferenceDescriptionBinding::AttendeeByPass)
      .SetProperty("autoPromote", &ConferenceDescriptionBinding::AutoPromote)
      .SetProperty("serverMode", &ConferenceDescriptionBinding::ServerMode)
      .SetProperty("interactiveBroadcastEnabled",
                   &ConferenceDescriptionBinding::InteractiveBroadcastEnabled)
      .SetProperty("enterpriseId", &ConferenceDescriptionBinding::EnterpriseId)
      .SetProperty("videoEnable", &ConferenceDescriptionBinding::VideoEnable)
      .SetProperty("ipcallEnable", &ConferenceDescriptionBinding::IpcallEnable)
      .SetProperty("webrtcEnable", &ConferenceDescriptionBinding::WebrtcEnable)
      .SetProperty("recordServerType",
                   &ConferenceDescriptionBinding::RecordServerType)
      .SetProperty("recordPrivilege",
                   &ConferenceDescriptionBinding::RecordPrivilege)
      .SetProperty("confInfoUrl", &ConferenceDescriptionBinding::ConfInfoUrl)
      .SetMethod("getDefaultRtmp",
                 &ConferenceDescriptionBinding::GetDefaultRtmp)
      .SetMethod("getLock", &ConferenceDescriptionBinding::GetLock)
      .SetMethod("setLock", &ConferenceDescriptionBinding::SetLock)
      .SetMethod("getShareInfo", &ConferenceDescriptionBinding::GetShareInfo);
}

void ConferenceDescriptionBinding::UpdateRoomController(
    RoomController* handler) {
  room_controller_ = handler;
}

ConferenceDescriptionBinding::ConferenceDescriptionBinding(
    v8::Isolate* isolate,
    v8::Local<v8::Object> wrapper)
    : weak_factory_(this) {
  InitWith(isolate, wrapper);
}

ConferenceDescriptionBinding::ConferenceDescriptionBinding(
    v8::Isolate* isolate,
    yealink::RoomController* controller)
    : weak_factory_(this) {
  Init(isolate);
  room_controller_ = controller;
  // state_ = ConferenceStateBinding::Create(isolate, controller);
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
v8::Local<v8::Value> ConferenceDescriptionBinding::StartTime() {
  int64_t value = 0;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .startTime);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::Banner() {
  DescBanner value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .banner);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::DefaultRtmp() {
  DescDefaultRtmp value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .defaultRtmp);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::Profile() {
  DescProfile value = DescProfile::kInvalid;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .profile);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::RecordId() {
  std::string value = "";

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .recordId);

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Value> ConferenceDescriptionBinding::ConfUris() {
  std::vector<DescConfUriInfo> value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .confUris);

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Value> ConferenceDescriptionBinding::Organizer() {
  DescOrganizerInfo value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .organizer);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::ConferenceId() {
  std::string value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .conferenceId);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::ConferenceNumber() {
  std::string value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .conferenceNumber);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::ConferenceType() {
  DescConferenceType value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .conferenceType);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::ConferenceNumberType() {
  DescNumberType value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .conferenceNumberType);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::BookStartTime() {
  int64_t value = 0;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .bookStartTime);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::BookExpiryTime() {
  int64_t value = 0;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .bookExpiryTime);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::PresenterPin() {
  std::string value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .presenterPin);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::AttendeePin() {
  std::string value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .attendeePin);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::MaximumUserCount() {
  uint32_t value = 0;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .maximumUserCount);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::AdmissionPolicy() {
  DescAdmissionPolicy value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .admissionPolicy);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::LobbyCapable() {
  bool value = false;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .lobbyCapable);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::AttendeeByPass() {
  bool value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .attendeeByPass);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::AutoPromote() {
  DescAutoPromote value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .autoPromote);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::ServerMode() {
  std::string value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .serverMode);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value>
ConferenceDescriptionBinding::InteractiveBroadcastEnabled() {
  bool value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .interactiveBroadcastEnabled);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::EnterpriseId() {
  std::string value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .enterpriseId);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::VideoEnable() {
  bool value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .videoEnable);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::IpcallEnable() {
  bool value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .ipcallEnable);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::WebrtcEnable() {
  bool value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .webrtcEnable);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::RecordServerType() {
  DescRecordType value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .recordServerType);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::RecordPrivilege() {
  DescRecordPrivilege value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .recordPrivilege);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceDescriptionBinding::ConfInfoUrl() {
  std::string value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .confInfoUrl);

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Value> ConferenceDescriptionBinding::GetDefaultRtmp() {
  DescDefaultRtmp value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetDescriptionComponent()
                           .GetConferenceDescription()
                           .defaultRtmp);

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Value> ConferenceDescriptionBinding::GetLock() {
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

  return mate::ConvertToV8(isolate(), params);
}

v8::Local<v8::Value> ConferenceDescriptionBinding::SetLock(
    DescSetLockInfo params) {
  yealink::RequestResult result;
  yealink::rtvc::ResponseInfo response;

  if (room_controller_)
    result = room_controller_->GetViewComponent().ModifyConferenceLock(
        (yealink::ConferenceDescription::AdmissionPolicy)
            params.admission_policy,
        (yealink::ConferenceDescription::AttendeeByPass)params.attendee_by_pass,
        (yealink::ConferenceDescription::AutoPromote)params.auto_promote);

  ConvertFrom(response, result);

  return mate::ConvertToV8(isolate(), response);
}

void ConferenceDescriptionBinding::DoSetLock(DescSetLockInfo params) {
  if (room_controller_)
    room_controller_->GetViewComponent().ModifyConferenceLock(
        (yealink::ConferenceDescription::AdmissionPolicy)
            params.admission_policy,
        (yealink::ConferenceDescription::AttendeeByPass)params.attendee_by_pass,
        (yealink::ConferenceDescription::AutoPromote)params.auto_promote);
}

v8::Local<v8::Value> ConferenceDescriptionBinding::GetShareInfo(
    mate::Arguments* args) {
  std::string lang;

  if (!args->GetNext(&lang)) {
    args->ThrowError("lang is required");
  }

  yealink::RequestResult result;
  yealink::rtvc::ResponseInfo response;

  if (room_controller_)
    result =
        room_controller_->GetDescriptionComponent().GetShareInfo(lang.c_str());

  ConvertFrom(response, result);

  return mate::ConvertToV8(isolate(), response);
}

void ConferenceDescriptionBinding::DoGetShareInfo(std::string lang) {
  if (room_controller_)
    room_controller_->GetDescriptionComponent().GetShareInfo(lang.c_str());
}

void ConferenceDescriptionBinding::OnCommandCompeleted(Promise promise) {
  std::move(promise).Resolve(true);
}

}  // namespace rtvc

}  // namespace yealink
