#include "yealink/rtvc/binding/conference_user_binding.h"

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* ConferenceUserBinding::New(mate::Arguments* args) {
  return new ConferenceUserBinding(args->isolate(), args->GetThis());
}

mate::Handle<ConferenceUserBinding> ConferenceUserBinding::Create(
    v8::Isolate* isolate,
    yealink::RoomMember* controller) {
  return mate::CreateHandle(isolate,
                            new ConferenceUserBinding(isolate, controller));
}

// static
void ConferenceUserBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "ConferenceUser"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("entity", &ConferenceUserBinding::Entity)
      .SetProperty("displayText", &ConferenceUserBinding::DisplayText)
      .SetProperty("displayNumber", &ConferenceUserBinding::DisplayNumber)
      .SetProperty("displayTextPinyin",
                   &ConferenceUserBinding::DisplayTextPinyin)
      .SetProperty("uid", &ConferenceUserBinding::Uid)
      .SetProperty("protocol", &ConferenceUserBinding::Protocol)
      .SetProperty("mediumServerType", &ConferenceUserBinding::MediumServerType)
      .SetProperty("ip", &ConferenceUserBinding::Ip)
      .SetProperty("phone", &ConferenceUserBinding::Phone)
      .SetProperty("requestUri", &ConferenceUserBinding::RequestUri)
      .SetProperty("userAgent", &ConferenceUserBinding::UserAgent)
      .SetProperty("roles", &ConferenceUserBinding::Roles)
      .SetProperty("endpoint", &ConferenceUserBinding::Endpoint)
      .SetMethod("isCurrentUser", &ConferenceUserBinding::IsCurrentUser)
      .SetMethod("isRtmp", &ConferenceUserBinding::IsRtmp)
      .SetMethod("isSIP", &ConferenceUserBinding::IsSIP)
      .SetMethod("isOrganizer", &ConferenceUserBinding::IsOrganizer)
      .SetMethod("isPresenter", &ConferenceUserBinding::IsPresenter)
      .SetMethod("isAttendee", &ConferenceUserBinding::IsAttendee)
      .SetMethod("isCastViewer", &ConferenceUserBinding::IsCastViewer)
      .SetMethod("isDemonstrator", &ConferenceUserBinding::IsDemonstrator)
      .SetMethod("isPresenterDemonstrator",
                 &ConferenceUserBinding::IsPresenterDemonstrator)
      .SetMethod("isOnHold", &ConferenceUserBinding::IsOnHold)
      .SetMethod("isSharing", &ConferenceUserBinding::IsSharing)
      .SetMethod("isFocus", &ConferenceUserBinding::IsFocus)
      .SetMethod("getAudioFilter", &ConferenceUserBinding::GetAudioFilter)
      .SetMethod("getVideoFilter", &ConferenceUserBinding::GetVideoFilter)
      .SetMethod("getStats", &ConferenceUserBinding::GetStats)
      .SetMethod("setAudioIngressFilter",
                 &ConferenceUserBinding::SetAudioIngressFilter)
      .SetMethod("setAudioEgressFilter",
                 &ConferenceUserBinding::SetAudioEgressFilter)
      .SetMethod("setVideoIngressFilter",
                 &ConferenceUserBinding::SetVideoIngressFilter)
      .SetMethod("setPermission", &ConferenceUserBinding::SetPermission)
      .SetMethod("setDemonstrator", &ConferenceUserBinding::SetDemonstrator)
      .SetMethod("setPresenterDemonstrator",
                 &ConferenceUserBinding::SetPresenterDemonstrator)
      .SetMethod("hold", &ConferenceUserBinding::Hold)
      .SetMethod("unHold", &ConferenceUserBinding::UnHold)
      .SetMethod("kick", &ConferenceUserBinding::Kick)
      .SetMethod("setDisplayName", &ConferenceUserBinding::SetDisplayName);
}

void ConferenceUserBinding::UpdateUserController(RoomMember* handler) {
  user_controller_ = handler;
}

ConferenceUserBinding::ConferenceUserBinding(v8::Isolate* isolate,
                                             yealink::RoomMember* controller)
    : weak_factory_(this) {
  Init(isolate);
  user_controller_ = controller;
}
ConferenceUserBinding::ConferenceUserBinding(v8::Isolate* isolate,
                                             v8::Local<v8::Object> wrapper)
    : weak_factory_(this) {}
ConferenceUserBinding::~ConferenceUserBinding() = default;

v8::Local<v8::Value> ConferenceUserBinding::Entity() {
  std::string value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->GetMemberInfo().entity);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceUserBinding::DisplayText() {
  std::string value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->GetMemberInfo().displayText);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceUserBinding::DisplayNumber() {
  std::string value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->GetMemberInfo().displayNumber);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceUserBinding::DisplayTextPinyin() {
  std::string value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->GetMemberInfo().displayTextPinyin);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceUserBinding::Uid() {
  std::string value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->GetMemberInfo().uid);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceUserBinding::Protocol() {
  UserProtocolType value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->GetMemberInfo().protocol);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceUserBinding::MediumServerType() {
  std::string value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->GetMemberInfo().mediumServerType);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceUserBinding::Ip() {
  std::string value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->GetMemberInfo().ip);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceUserBinding::Phone() {
  std::string value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->GetMemberInfo().phone);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceUserBinding::RequestUri() {
  std::string value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->GetMemberInfo().requestUri);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceUserBinding::UserAgent() {
  std::string value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->GetMemberInfo().userAgent);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceUserBinding::Roles() {
  std::string value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->GetMemberInfo().displayText);

  return mate::ConvertToV8(isolate(), value);
}
v8::Local<v8::Value> ConferenceUserBinding::Endpoint() {
  std::vector<UserEndpointInfo> value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->GetMemberInfo().endpointList);

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Value> ConferenceUserBinding::IsCurrentUser() {
  bool value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->IsCurrentUser());

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Value> ConferenceUserBinding::IsRtmp() {
  bool value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->GetMemberInfo().protocol ==
                           yealink::MemberInfo::Protocol::RTMP);

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Value> ConferenceUserBinding::IsSIP() {
  bool value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->GetMemberInfo().protocol ==
                           yealink::MemberInfo::Protocol::SIP);

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Value> ConferenceUserBinding::IsOrganizer() {
  bool value;

  if (user_controller_)
    ConvertFrom(
        value,
        user_controller_->GetMemberInfo().protocol ==
            yealink::MemberInfo::Roles::PermissionRole::PERMISSION_ORGANIZER);

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Value> ConferenceUserBinding::IsPresenter() {
  bool value;

  if (user_controller_)
    ConvertFrom(
        value,
        user_controller_->GetMemberInfo().protocol ==
            yealink::MemberInfo::Roles::PermissionRole::PERMISSION_PRESENTER);

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Value> ConferenceUserBinding::IsAttendee() {
  bool value;

  if (user_controller_)
    ConvertFrom(
        value,
        user_controller_->GetMemberInfo().protocol ==
            yealink::MemberInfo::Roles::PermissionRole::PERMISSION_ATTENDEE);

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Value> ConferenceUserBinding::IsCastViewer() {
  bool value;

  if (user_controller_)
    ConvertFrom(
        value,
        user_controller_->GetMemberInfo().protocol ==
            yealink::MemberInfo::Roles::PermissionRole::PERMISSION_CAST_VIEWER);

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Value> ConferenceUserBinding::IsDemonstrator() {
  bool value;

  if (user_controller_)
    ConvertFrom(
        value,
        user_controller_->GetMemberInfo().protocol ==
            yealink::MemberInfo::Roles::DemoStateRole::DEMOSTATE_DEMONSTRATOR);

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Value> ConferenceUserBinding::IsPresenterDemonstrator() {
  bool value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->GetMemberInfo().protocol ==
                           yealink::MemberInfo::Roles::PresenterDemoStateRole::
                               PRESENTER_DEMONSTRATOR);

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Value> ConferenceUserBinding::IsOnHold() {
  bool value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->IsHoldOn());

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Value> ConferenceUserBinding::IsSharing() {
  bool value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->IsSharing());

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Value> ConferenceUserBinding::IsFocus() {
  bool value;

  if (user_controller_)
    ConvertFrom(value, user_controller_->IsFocus());

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Value> ConferenceUserBinding::GetAudioFilter() {
  UserMediaFilterInfo value;
  yealink::MemberInfo::Endpoint::Media param;

  if (user_controller_) {
    param.mediaEgressBlockBy =
        yealink::MemberInfo::Endpoint::Media::BlockBy::NONE;
    param.mediaEgressFilter = user_controller_->GetAudioEgressFilter();
    param.mediaIngressBlockBy = user_controller_->GetAudioIngressBlockBy();
    param.mediaIngressFilter = user_controller_->GetAudioIngressFilter();

    ConvertFrom(value, param);
  }

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Value> ConferenceUserBinding::GetVideoFilter() {
  UserMediaFilterInfo value;
  yealink::MemberInfo::Endpoint::Media param;

  if (user_controller_) {
    param.mediaEgressBlockBy =
        yealink::MemberInfo::Endpoint::Media::BlockBy::NONE;
    param.mediaEgressFilter = user_controller_->GetVideoEgressFilter();
    param.mediaIngressBlockBy =
        yealink::MemberInfo::Endpoint::Media::BlockBy::NONE;
    param.mediaIngressFilter = user_controller_->GetVideoIngressFilter();

    ConvertFrom(value, param);
  }

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Promise> ConferenceUserBinding::GetStats() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceUserBinding::DoGetStats,
                     weak_factory_.GetWeakPtr()),
      base::BindOnce(&ConferenceUserBinding::OnCommandCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise)));

  return handle;
}

void ConferenceUserBinding::DoGetStats() {
  if (user_controller_) {
    user_controller_->GetUserCallStats();
  }
}

v8::Local<v8::Promise> ConferenceUserBinding::SetAudioIngressFilter(
    bool isOpen) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceUserBinding::DoSetAudioIngressFilter,
                     weak_factory_.GetWeakPtr(), isOpen),
      base::BindOnce(&ConferenceUserBinding::OnCommandCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise)));

  return handle;
}

void ConferenceUserBinding::DoSetAudioIngressFilter(bool isOpen) {
  if (user_controller_) {
    user_controller_->SetAudioState(isOpen);
  }
}

v8::Local<v8::Promise> ConferenceUserBinding::SetAudioEgressFilter(
    bool isOpen) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceUserBinding::DoSetAudioEgressFilter,
                     weak_factory_.GetWeakPtr(), isOpen),
      base::BindOnce(&ConferenceUserBinding::OnCommandCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise)));

  return handle;
}

void ConferenceUserBinding::DoSetAudioEgressFilter(bool isOpen) {
  if (user_controller_) {
    user_controller_->SetAudioEgressState(isOpen);
  }
}

v8::Local<v8::Promise> ConferenceUserBinding::SetVideoIngressFilter(
    bool isOpen) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceUserBinding::DoSetVideoIngressFilter,
                     weak_factory_.GetWeakPtr(), isOpen),
      base::BindOnce(&ConferenceUserBinding::OnCommandCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise)));

  return handle;
}

void ConferenceUserBinding::DoSetVideoIngressFilter(bool isOpen) {
  if (user_controller_) {
    user_controller_->SetVideoState(isOpen);
  }
}

v8::Local<v8::Promise> ConferenceUserBinding::SetPermission(
    UserPermissionType params) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceUserBinding::DoSetPermission,
                     weak_factory_.GetWeakPtr(), params),
      base::BindOnce(&ConferenceUserBinding::OnCommandCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise)));

  return handle;
}

void ConferenceUserBinding::DoSetPermission(UserPermissionType params) {
  MemberInfo::Roles::PermissionRole value;

  ConvertFrom(params, value);
  if (user_controller_) {
    user_controller_->ModifyRole(value);
  }
}

v8::Local<v8::Promise> ConferenceUserBinding::SetDemonstrator(
    UserDemoStateType params) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceUserBinding::DoSetDemonstrator,
                     weak_factory_.GetWeakPtr(), params),
      base::BindOnce(&ConferenceUserBinding::OnCommandCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise)));

  return handle;
}

void ConferenceUserBinding::DoSetDemonstrator(UserDemoStateType params) {
  if (user_controller_) {
    if (params == UserDemoStateType::kDemonstrator)
      user_controller_->SetDemonstrator(true);
    else
      user_controller_->SetDemonstrator(false);
  }
}

v8::Local<v8::Promise> ConferenceUserBinding::SetPresenterDemonstrator(
    PresenterDemoStateType params) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceUserBinding::DoSetPresenterDemonstrator,
                     weak_factory_.GetWeakPtr(), params),
      base::BindOnce(&ConferenceUserBinding::OnCommandCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise)));

  return handle;
}

void ConferenceUserBinding::DoSetPresenterDemonstrator(
    PresenterDemoStateType params) {
  if (user_controller_) {
    if (params == PresenterDemoStateType::kDemonstrator)
      user_controller_->SetDemonstrator(true);
    else
      user_controller_->SetDemonstrator(false);
  }
}

v8::Local<v8::Promise> ConferenceUserBinding::Hold() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceUserBinding::DoHold,
                     weak_factory_.GetWeakPtr()),
      base::BindOnce(&ConferenceUserBinding::OnCommandCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise)));

  return handle;
}

void ConferenceUserBinding::DoHold() {
  if (user_controller_) {
    user_controller_->Hold();
  }
}

v8::Local<v8::Promise> ConferenceUserBinding::UnHold() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceUserBinding::DoUnHold,
                     weak_factory_.GetWeakPtr()),
      base::BindOnce(&ConferenceUserBinding::OnCommandCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise)));

  return handle;
}

void ConferenceUserBinding::DoUnHold() {
  if (user_controller_) {
    user_controller_->SetAccess(true);
  }
}

v8::Local<v8::Promise> ConferenceUserBinding::Kick() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceUserBinding::DoKick,
                     weak_factory_.GetWeakPtr()),
      base::BindOnce(&ConferenceUserBinding::OnCommandCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise)));

  return handle;
}

void ConferenceUserBinding::DoKick() {
  if (user_controller_) {
    user_controller_->KickOut();
  }
}

v8::Local<v8::Promise> ConferenceUserBinding::SetDisplayName(
    mate::Arguments* args) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  std::string name;

  if (!args->GetNext(&name)) {
    args->ThrowError("name is required");
  }

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceUserBinding::DoSetDisplayName,
                     weak_factory_.GetWeakPtr(), name),
      base::BindOnce(&ConferenceUserBinding::OnCommandCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise)));

  return handle;
}

void ConferenceUserBinding::DoSetDisplayName(std::string name) {
  if (user_controller_) {
    user_controller_->ModifyUserName(name.c_str());
  }
}

v8::Local<v8::Promise> ConferenceUserBinding::SetFocus(bool isFocus) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceUserBinding::DoSetFocus,
                     weak_factory_.GetWeakPtr(), isFocus),
      base::BindOnce(&ConferenceUserBinding::OnCommandCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise)));

  return handle;
}

void ConferenceUserBinding::DoSetFocus(bool isFocus) {
  if (user_controller_) {
    if (isFocus == true)
      user_controller_->SetFocus(true);
    else
      user_controller_->SetFocus(false);
  }
}

void ConferenceUserBinding::OnCommandCompeleted(Promise promise) {
  std::move(promise).Resolve(true);
}

}  // namespace rtvc

}  // namespace yealink
