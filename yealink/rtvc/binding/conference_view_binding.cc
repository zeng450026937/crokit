#include "yealink/rtvc/binding/conference_view_binding.h"

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* ConferenceViewBinding::New(mate::Arguments* args) {
  return new ConferenceViewBinding(args->isolate(), args->GetThis());
}

mate::Handle<ConferenceViewBinding> ConferenceViewBinding::Create(
    v8::Isolate* isolate,
    yealink::RoomController* controller) {
  return mate::CreateHandle(isolate,
                            new ConferenceViewBinding(isolate, controller));
}

// static
void ConferenceViewBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "ConferenceView"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetMethod("setLayout", &ConferenceViewBinding::SetLayout)
      .SetMethod("getLayout", &ConferenceViewBinding::GetLayout)
      .SetMethod("setInitialFilters", &ConferenceViewBinding::SetInitialFilters)
      .SetMethod("getInitialFilters",
                 &ConferenceViewBinding::GetInitialFilters);
}

void ConferenceViewBinding::UpdateRoomController(RoomController* handler) {
  room_controller_ = handler;
}

ConferenceViewBinding::ConferenceViewBinding(
    v8::Isolate* isolate,
    yealink::RoomController* controller)
    : weak_factory_(this) {
  Init(isolate);
  room_controller_ = controller;
}

ConferenceViewBinding::ConferenceViewBinding(v8::Isolate* isolate,
                                             v8::Local<v8::Object> wrapper)
    : weak_factory_(this) {}
ConferenceViewBinding::~ConferenceViewBinding() = default;

v8::Local<v8::Promise> ConferenceViewBinding::SetLayout(SetLayoutInfo params) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  if (room_controller_)
    room_controller_->GetViewComponent().ModifyLayout(
        (yealink::ConferenceView::EntityState::VideoLayout)params.video_layout,
        params.video_max_view);

  std::move(promise).Resolve();

  return handle;
}

void ConferenceViewBinding::DoSetLayout(SetLayoutInfo params) {
  if (room_controller_)
    room_controller_->GetViewComponent().ModifyLayout(
        (yealink::ConferenceView::EntityState::VideoLayout)params.video_layout,
        params.video_max_view);
}

GetLayoutInfo ConferenceViewBinding::GetLayout() {
  GetLayoutInfo value;

  if (room_controller_)
    ConvertFrom(
        value,
        room_controller_->GetViewComponent().GetConferenceView().entityState);

  return value;
}

v8::Local<v8::Promise> ConferenceViewBinding::SetInitialFilters(
    ViewFilterRuleInfo params) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  if (params.role == yealink::rtvc::ViewFilterRoleType::kDefault &&
      params.ingress == yealink::rtvc::ViewFilterType::kBlock) {
    if (room_controller_)
      room_controller_->GetViewComponent().MuteAll();
  } else if (params.role == yealink::rtvc::ViewFilterRoleType::kDefault &&
             params.ingress == yealink::rtvc::ViewFilterType::kUnBlock) {
    if (room_controller_)
      room_controller_->GetViewComponent().UnMuteAll();
  } else {
  }

  std::move(promise).Resolve();

  return handle;
}

void ConferenceViewBinding::DoSetInitialFilters(ViewFilterRuleInfo params) {
  if (params.role == yealink::rtvc::ViewFilterRoleType::kDefault &&
      params.ingress == yealink::rtvc::ViewFilterType::kBlock) {
    if (room_controller_)
      room_controller_->GetViewComponent().MuteAll();
  } else if (params.role == yealink::rtvc::ViewFilterRoleType::kDefault &&
             params.ingress == yealink::rtvc::ViewFilterType::kUnBlock) {
    if (room_controller_)
      room_controller_->GetViewComponent().UnMuteAll();
  } else {
  }
}

std::vector<ViewFilterRuleInfo> ConferenceViewBinding::GetInitialFilters() {
  std::vector<ViewFilterRuleInfo> value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetViewComponent()
                           .GetConferenceView()
                           .entityState.mediaFiltersRules.initialFilters);

  return value;
}

// v8::Local<v8::Promise> ConferenceViewBinding::SetSpeakMode(
//     ViewSpeakMode params) {
//   Promise promise(isolate());
//   v8::Local<v8::Promise> handle = promise.GetHandle();
//   HttpResponseInfo response;

//   if (room_controller_) {
//     ConvertFrom(response, room_controller_->GetViewComponent().SetSpeakMode(
//                               (yealink::ConferenceViewSpeakMode)params));
//     std::move(promise).Resolve(response);
//   } else {
//     std::move(promise).Reject();
//   }

//   return handle;
// }

void ConferenceViewBinding::OnCommandCompeleted(Promise promise) {
  std::move(promise).Resolve(true);
}

}  // namespace rtvc

}  // namespace yealink
