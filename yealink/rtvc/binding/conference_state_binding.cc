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
      .SetProperty("lock", &ConferenceStateBinding::Lock)
      .SetProperty("active", &ConferenceStateBinding::Active)
      .SetMethod("setLock", &ConferenceStateBinding::SetLock);
}

void ConferenceStateBinding::UpdateRoomController(RoomController* handler) {
  room_controller_ = handler;
}

ConferenceStateBinding::ConferenceStateBinding(v8::Isolate* isolate,
                                               v8::Local<v8::Object> wrapper) {
  InitWith(isolate, wrapper);
}

ConferenceStateBinding::ConferenceStateBinding(
    v8::Isolate* isolate,
    yealink::RoomController* controller) {
  Init(isolate);
  room_controller_ = controller;
}

ConferenceStateBinding::~ConferenceStateBinding() = default;

bool ConferenceStateBinding::Lock() {
  if(room_controller_)
    return room_controller_->GetStateComponent().GetConferenceState().locked;
  else
    return false;
}

bool ConferenceStateBinding::Active() {
  if(room_controller_)
    return room_controller_->GetStateComponent().GetConferenceState().active;
  else
    return false;
}

v8::Local<v8::Promise> ConferenceStateBinding::SetLock() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceStateBinding::DoSetLock,
                     base::Unretained(this)),
      base::BindOnce(&ConferenceStateBinding::OnCommandCompeleted,
                     base::Unretained(this), std::move(promise)));

  return handle;
}

void ConferenceStateBinding::DoSetLock() {}

void ConferenceStateBinding::OnCommandCompeleted(Promise promise) {
  std::move(promise).Resolve();
}

}  // namespace rtvc

}  // namespace yealink
