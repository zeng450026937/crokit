#include "yealink/rtvc/binding/conference_state_binding.h"
#include "base/logging.h"
#include "base/task/post_task.h"
#include "yealink/libvc/include/room/room_state_component.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* ConferenceStateBinding::New(mate::Arguments* args) {
  return new ConferenceStateBinding(args->isolate(), args->GetThis());
}

mate::Handle<ConferenceStateBinding> ConferenceStateBinding::Create(
    v8::Isolate* isolate,
    yealink::RoomController* controller) {
  return mate::CreateHandle(isolate,
                            new ConferenceStateBinding(isolate, controller));
}

// static
void ConferenceStateBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "ConferenceState"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("locked", &ConferenceStateBinding::locked)
      .SetProperty("active", &ConferenceStateBinding::active)
      .SetProperty("rollCallStatus", &ConferenceStateBinding::rollCallStatus);
}

void ConferenceStateBinding::UpdateRoomController(RoomController* handler) {
  room_controller_ = handler;
}

ConferenceStateBinding::ConferenceStateBinding(v8::Isolate* isolate,
                                               v8::Local<v8::Object> wrapper)
    : weak_factory_(this) {
  InitWith(isolate, wrapper);
}

ConferenceStateBinding::ConferenceStateBinding(
    v8::Isolate* isolate,
    yealink::RoomController* controller)
    : weak_factory_(this) {
  Init(isolate);
  room_controller_ = controller;
}

ConferenceStateBinding::~ConferenceStateBinding() = default;

bool ConferenceStateBinding::active() {
  bool value = false;

  if (room_controller_)
    ConvertFrom(
        value,
        room_controller_->GetStateComponent().GetConferenceState().active);

  return value;
}
bool ConferenceStateBinding::locked() {
  bool value = false;

  if (room_controller_)
    ConvertFrom(
        value,
        room_controller_->GetStateComponent().GetConferenceState().locked);

  return value;
}
std::string ConferenceStateBinding::rollCallStatus() {
  std::string value;

  if (room_controller_)
    ConvertFrom(value, room_controller_->GetStateComponent()
                           .GetConferenceState()
                           .rollCallStatus);

  return value;
}

}  // namespace rtvc

}  // namespace yealink
