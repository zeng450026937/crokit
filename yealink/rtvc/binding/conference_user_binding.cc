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

namespace {
static std::unordered_map<std::string, int32_t> g_uid_map_;
}  // namespace

// static
mate::WrappableBase* ConferenceUserBinding::New(mate::Arguments* args) {
  return new ConferenceUserBinding(args->isolate(), args->GetThis());
}

mate::Handle<ConferenceUserBinding> ConferenceUserBinding::Create(
    v8::Isolate* isolate,
    yealink::RoomMember& controller,
    std::unordered_map<std::string, Promise>* handler) {
  auto iter = g_uid_map_.find(controller.GetMemberInfo().entity.ConstData());

  if (iter == g_uid_map_.end()) {
    return mate::CreateHandle(
        isolate, new ConferenceUserBinding(isolate, controller, handler));
  }

  int32_t weak_map_id = iter->second;

  auto binding = mate::TrackableObject<ConferenceUserBinding>::FromWeakMapID(
      isolate, weak_map_id);

  if (binding) {
    binding->UpdateUserController(controller);
    binding->UpdateStatsPendingHandler(handler);
    return mate::CreateHandle(isolate, binding);
  }

  return mate::CreateHandle(
      isolate, new ConferenceUserBinding(isolate, controller, handler));
}

// static
void ConferenceUserBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "ConferenceUser"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("entity", &ConferenceUserBinding::entity)
      .SetProperty("displayText", &ConferenceUserBinding::displayText)
      .SetProperty("displayNumber", &ConferenceUserBinding::displayNumber)
      .SetProperty("displayTextPinyin",
                   &ConferenceUserBinding::displayTextPinyin)
      .SetProperty("uid", &ConferenceUserBinding::uid)
      .SetProperty("protocol", &ConferenceUserBinding::protocol)
      .SetProperty("mediumServerType", &ConferenceUserBinding::mediumServerType)
      .SetProperty("ip", &ConferenceUserBinding::ip)
      .SetProperty("phone", &ConferenceUserBinding::phone)
      .SetProperty("requestUri", &ConferenceUserBinding::requestUri)
      .SetProperty("userAgent", &ConferenceUserBinding::userAgent)
      .SetProperty("roles", &ConferenceUserBinding::roles)
      .SetProperty("endpoint", &ConferenceUserBinding::endpoint)
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
      .SetMethod("hasFECC", &ConferenceUserBinding::HasFECC)
      .SetMethod("isConnected", &ConferenceUserBinding::IsConnected)
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
      .SetMethod("setDisplayName", &ConferenceUserBinding::SetDisplayName)
      .SetMethod("setFocus", &ConferenceUserBinding::SetFocus);
}

void ConferenceUserBinding::UpdateUserController(RoomMember& handler) {
  user_controller_ = handler;
}

RoomMember ConferenceUserBinding::GetUserController() {
  return user_controller_;
}

void ConferenceUserBinding::UpdateStatsPendingHandler(
    std::unordered_map<std::string, Promise>* handler) {
  stats_pending_requests_ = handler;
}

ConferenceUserBinding::ConferenceUserBinding(
    v8::Isolate* isolate,
    yealink::RoomMember& controller,
    std::unordered_map<std::string, Promise>* handler)
    : weak_factory_(this) {
  Init(isolate);
  user_controller_ = controller;
  stats_pending_requests_ = handler;

  g_uid_map_.emplace(user_controller_.GetMemberInfo().entity.ConstData(),
                     weak_map_id_);
}
ConferenceUserBinding::ConferenceUserBinding(v8::Isolate* isolate,
                                             v8::Local<v8::Object> wrapper)
    : weak_factory_(this) {
  InitWith(isolate, wrapper);
}
ConferenceUserBinding::~ConferenceUserBinding() {
  LOG(INFO) << __FUNCTIONW__;
  g_uid_map_.erase(user_controller_.GetMemberInfo().entity.ConstData());
};

std::string ConferenceUserBinding::entity() {
  std::string value;

  ConvertFrom(value, user_controller_.GetMemberInfo().entity);

  return value;
}
std::string ConferenceUserBinding::displayText() {
  std::string value;

  ConvertFrom(value, user_controller_.GetMemberInfo().displayText);

  return value;
}
std::string ConferenceUserBinding::displayNumber() {
  std::string value;

  ConvertFrom(value, user_controller_.GetMemberInfo().displayNumber);

  return value;
}
std::string ConferenceUserBinding::displayTextPinyin() {
  std::string value;

  ConvertFrom(value, user_controller_.GetMemberInfo().displayTextPinyin);

  return value;
}
std::string ConferenceUserBinding::uid() {
  std::string value;

  ConvertFrom(value, user_controller_.GetMemberInfo().uid);

  return value;
}
UserProtocolType ConferenceUserBinding::protocol() {
  UserProtocolType value = UserProtocolType::kInvalid;

  ConvertFrom(value, user_controller_.GetMemberInfo().protocol);

  return value;
}
std::string ConferenceUserBinding::mediumServerType() {
  std::string value;

  ConvertFrom(value, user_controller_.GetMemberInfo().mediumServerType);

  return value;
}
std::string ConferenceUserBinding::ip() {
  std::string value;

  ConvertFrom(value, user_controller_.GetMemberInfo().ip);

  return value;
}
std::string ConferenceUserBinding::phone() {
  std::string value;

  ConvertFrom(value, user_controller_.GetMemberInfo().phone);

  return value;
}
std::string ConferenceUserBinding::requestUri() {
  std::string value;

  ConvertFrom(value, user_controller_.GetMemberInfo().requestUri);

  return value;
}
std::string ConferenceUserBinding::userAgent() {
  std::string value;

  ConvertFrom(value, user_controller_.GetMemberInfo().userAgent);

  return value;
}
UserRolesInfo ConferenceUserBinding::roles() {
  UserRolesInfo value;

  ConvertFrom(value, user_controller_.GetMemberInfo().roles);

  return value;
}
std::vector<UserEndpointInfo> ConferenceUserBinding::endpoint() {
  std::vector<UserEndpointInfo> value;

  ConvertFrom(value, user_controller_.GetMemberInfo().endpointList);

  return value;
}

bool ConferenceUserBinding::IsCurrentUser() {
  bool value = false;

  ConvertFrom(value, user_controller_.IsCurrentUser());

  return value;
}

bool ConferenceUserBinding::IsRtmp() {
  bool value;

  ConvertFrom(value, user_controller_.GetMemberInfo().protocol ==
                         yealink::MemberInfo::Protocol::RTMP);

  return value;
}

bool ConferenceUserBinding::IsSIP() {
  bool value;

  ConvertFrom(value, user_controller_.GetMemberInfo().protocol ==
                         yealink::MemberInfo::Protocol::SIP);

  return value;
}

bool ConferenceUserBinding::IsOrganizer() {
  bool value;

  ConvertFrom(
      value,
      user_controller_.GetMemberInfo().roles.permissionRole ==
          yealink::MemberInfo::Roles::PermissionRole::PERMISSION_ORGANIZER);

  return value;
}

bool ConferenceUserBinding::IsPresenter() {
  bool value = false;

  ConvertFrom(
      value,
      (user_controller_.GetMemberInfo().roles.permissionRole ==
       yealink::MemberInfo::Roles::PermissionRole::PERMISSION_PRESENTER) ||
          (user_controller_.GetMemberInfo().roles.permissionRole ==
           yealink::MemberInfo::Roles::PermissionRole::PERMISSION_ORGANIZER));

  return value;
}

bool ConferenceUserBinding::IsAttendee() {
  bool value = false;

  ConvertFrom(
      value,
      user_controller_.GetMemberInfo().roles.permissionRole ==
          yealink::MemberInfo::Roles::PermissionRole::PERMISSION_ATTENDEE);

  return value;
}

bool ConferenceUserBinding::IsCastViewer() {
  bool value = false;

  ConvertFrom(
      value,
      user_controller_.GetMemberInfo().roles.permissionRole ==
          yealink::MemberInfo::Roles::PermissionRole::PERMISSION_CAST_VIEWER);

  return value;
}

bool ConferenceUserBinding::IsDemonstrator() {
  bool value = false;
  MemberInfo test = user_controller_.GetMemberInfo();
  ConvertFrom(
      value,
      user_controller_.GetMemberInfo().roles.demoStateRole ==
          yealink::MemberInfo::Roles::DemoStateRole::DEMOSTATE_DEMONSTRATOR);

  return value;
}

bool ConferenceUserBinding::IsPresenterDemonstrator() {
  bool value = false;

  ConvertFrom(value,
              user_controller_.GetMemberInfo().roles.presenterDemoStateRole ==
                  yealink::MemberInfo::Roles::PresenterDemoStateRole::
                      PRESENTER_DEMONSTRATOR);

  return value;
}

bool ConferenceUserBinding::IsOnHold() {
  bool value = false;

  ConvertFrom(value, user_controller_.IsHoldOn());

  return value;
}

bool ConferenceUserBinding::IsSharing() {
  bool value = false;

  ConvertFrom(value, user_controller_.IsSharing());

  return value;
}

bool ConferenceUserBinding::IsFocus() {
  bool value = false;

  ConvertFrom(value, user_controller_.IsFocus());

  return value;
}

bool ConferenceUserBinding::IsConnected() {
  bool value = false;
  int i = 0;
  std::vector<UserEndpointInfo> endpoints;

  ConvertFrom(endpoints, user_controller_.GetMemberInfo().endpointList);

  if (endpoints.size() > 0) {
    for (i = 0; i < endpoints.size(); i++) {
      if (endpoints[i].session_type == UserEndpointSeesionType::kAudioVideo) {
        if (endpoints[i].status == UserEndpointStatusType::kConnected) {
          value = true;
          break;
        }
      }
    }
  }

  return value;
}

bool ConferenceUserBinding::HasFECC() {
  std::vector<UserEndpointInfo> endpoints;
  std::vector<UserMediaInfo> medias;
  bool value = false;
  int i = 0;

  ConvertFrom(endpoints, user_controller_.GetMemberInfo().endpointList);

  if (endpoints.size() > 0) {
    for (i = 0; i < endpoints.size(); i++) {
      if (endpoints[i].session_type == UserEndpointSeesionType::kAudioVideo) {
        medias = endpoints[i].media;
        break;
      }
    }

    for (i = 0; i < medias.size(); i++) {
      if (medias[i].label == UserMediaLabelType::kFecc) {
        value = true;
      }
    }
  }

  return value;
}

UserMediaFilterInfo ConferenceUserBinding::GetAudioFilter() {
  UserMediaFilterInfo value;
  yealink::MemberInfo::Endpoint::Media param;

  param.mediaEgressBlockBy =
      yealink::MemberInfo::Endpoint::Media::BlockBy::NONE;
  param.mediaEgressFilter = user_controller_.GetAudioEgressFilter();
  param.mediaIngressBlockBy = user_controller_.GetAudioIngressBlockBy();
  param.mediaIngressFilter = user_controller_.GetAudioIngressFilter();

  ConvertFrom(value, param);

  return value;
}

UserMediaFilterInfo ConferenceUserBinding::GetVideoFilter() {
  UserMediaFilterInfo value;
  yealink::MemberInfo::Endpoint::Media param;

  param.mediaEgressBlockBy =
      yealink::MemberInfo::Endpoint::Media::BlockBy::NONE;
  param.mediaEgressFilter = user_controller_.GetVideoEgressFilter();
  param.mediaIngressBlockBy =
      yealink::MemberInfo::Endpoint::Media::BlockBy::NONE;
  param.mediaIngressFilter = user_controller_.GetVideoIngressFilter();

  ConvertFrom(value, param);

  return value;
}

v8::Local<v8::Promise> ConferenceUserBinding::GetStats() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  user_controller_.GetUserCallStats();

  if (stats_pending_requests_) {
    stats_pending_requests_->emplace(
        std::string(user_controller_.GetMemberInfo().entity.ConstData()),
        std::move(promise));
  } else {
    std::move(promise).Resolve();
  }

  return handle;
}

void ConferenceUserBinding::DoGetStats() {
  user_controller_.GetUserCallStats();
}

v8::Local<v8::Promise> ConferenceUserBinding::SetAudioIngressFilter(
    bool isOpen) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  user_controller_.SetAudioState(!isOpen);

  std::move(promise).Resolve();

  return handle;
}

void ConferenceUserBinding::DoSetAudioIngressFilter(bool isOpen) {
  user_controller_.SetAudioState(isOpen);
}

v8::Local<v8::Promise> ConferenceUserBinding::SetAudioEgressFilter(
    bool isOpen) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  user_controller_.SetAudioEgressState(!isOpen);

  std::move(promise).Resolve();

  return handle;
}

void ConferenceUserBinding::DoSetAudioEgressFilter(bool isOpen) {
  user_controller_.SetAudioEgressState(isOpen);
}

v8::Local<v8::Promise> ConferenceUserBinding::SetVideoIngressFilter(
    bool isOpen) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  user_controller_.SetVideoState(!isOpen);

  std::move(promise).Resolve();

  return handle;
}

void ConferenceUserBinding::DoSetVideoIngressFilter(bool isOpen) {
  user_controller_.SetVideoState(isOpen);
}

v8::Local<v8::Promise> ConferenceUserBinding::SetPermission(
    UserPermissionType params) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  yealink::MemberInfo::Roles::PermissionRole value =
      (yealink::MemberInfo::Roles::PermissionRole)params;

  user_controller_.ModifyRole(value);

  std::move(promise).Resolve();

  return handle;
}

void ConferenceUserBinding::DoSetPermission(UserPermissionType params) {
  MemberInfo::Roles::PermissionRole value =
      MemberInfo::Roles::PermissionRole::PERMISSION_INVALID;

  ConvertFrom(params, value);

  user_controller_.ModifyRole(value);
}

v8::Local<v8::Promise> ConferenceUserBinding::SetDemonstrator(
    UserDemoStateType params) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  if (params == UserDemoStateType::kDemonstrator)
    user_controller_.SetDemonstrator(true);
  else
    user_controller_.SetDemonstrator(false);

  std::move(promise).Resolve();

  return handle;
}

void ConferenceUserBinding::DoSetDemonstrator(UserDemoStateType params) {
  if (params == UserDemoStateType::kDemonstrator)
    user_controller_.SetDemonstrator(true);
  else
    user_controller_.SetDemonstrator(false);
}

v8::Local<v8::Promise> ConferenceUserBinding::SetPresenterDemonstrator(
    PresenterDemoStateType params) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  if (params == PresenterDemoStateType::kDemonstrator)
    user_controller_.SetDemonstrator(true);
  else
    user_controller_.SetDemonstrator(false);

  std::move(promise).Resolve();

  return handle;
}

void ConferenceUserBinding::DoSetPresenterDemonstrator(
    PresenterDemoStateType params) {
  if (params == PresenterDemoStateType::kDemonstrator)
    user_controller_.SetDemonstrator(true);
  else
    user_controller_.SetDemonstrator(false);
}

v8::Local<v8::Promise> ConferenceUserBinding::Hold() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  user_controller_.Hold();

  std::move(promise).Resolve();

  return handle;
}

void ConferenceUserBinding::DoHold() {
  user_controller_.Hold();
}

v8::Local<v8::Promise> ConferenceUserBinding::UnHold() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  user_controller_.SetAccess(true);

  std::move(promise).Resolve();

  return handle;
}

void ConferenceUserBinding::DoUnHold() {
  user_controller_.SetAccess(true);
}

v8::Local<v8::Promise> ConferenceUserBinding::Kick() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  user_controller_.KickOut();

  std::move(promise).Resolve();

  return handle;
}

void ConferenceUserBinding::DoKick() {
  user_controller_.KickOut();
}

v8::Local<v8::Promise> ConferenceUserBinding::SetDisplayName(
    mate::Arguments* args) {
  std::string name;
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  if (!args->GetNext(&name)) {
    args->ThrowError("name is required");
  }

  user_controller_.ModifyUserName(name.c_str());

  std::move(promise).Resolve();

  return handle;
}

void ConferenceUserBinding::DoSetDisplayName(std::string name) {
  user_controller_.ModifyUserName(name.c_str());
}

v8::Local<v8::Promise> ConferenceUserBinding::SetFocus(bool isFocus) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  if (isFocus == true)
    user_controller_.SetFocus(true);
  else
    user_controller_.SetFocus(false);

  std::move(promise).Resolve();

  return handle;
}

void ConferenceUserBinding::DoSetFocus(bool isFocus) {
  if (isFocus == true)
    user_controller_.SetFocus(true);
  else
    user_controller_.SetFocus(false);
}

void ConferenceUserBinding::OnCommandCompeleted(Promise promise) {
  std::move(promise).Resolve(true);
}

}  // namespace rtvc

}  // namespace yealink
