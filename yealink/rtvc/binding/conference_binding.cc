#include "yealink/rtvc/binding/conference_binding.h"

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/conference_state_binding.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* ConferenceBinding::New(mate::Arguments* args) {
  return new ConferenceBinding(args->isolate(), args->GetThis());
}

mate::Handle<ConferenceBinding> ConferenceBinding::Create(
    v8::Isolate* isolate,
    yealink::RoomController* controller) {
  return mate::CreateHandle(isolate,
                            new ConferenceBinding(isolate, controller));
}

// static
void ConferenceBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "Conference"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetMethod("connect", &ConferenceBinding::Connect)
      .SetMethod("disconnect", &ConferenceBinding::Disconnect)
      //.SetProperty("state", &ConferenceBinding::State)
      .SetProperty("isInProgress", &ConferenceBinding::isInProgress)
      .SetProperty("isEstablished", &ConferenceBinding::isEstablished)
      .SetProperty("isEnded", &ConferenceBinding::isEnded)
      .SetProperty("isChatChannelSupported",
                   &ConferenceBinding::isChatChannelSupported)
      .SetProperty("isChatChannelEstablished",
                   &ConferenceBinding::isChatChannelEstablished);
}

void ConferenceBinding::UpdateRoomController(RoomController* handler) {
  room_controller_ = handler;

  //state_->UpdateRoomController(handler);
}

ConferenceBinding::ConferenceBinding(v8::Isolate* isolate,
                                     v8::Local<v8::Object> wrapper) {
  InitWith(isolate, wrapper);
}
ConferenceBinding::ConferenceBinding(v8::Isolate* isolate,
                                     yealink::RoomController* controller) {
  Init(isolate);
  room_controller_ = controller;
  // state_ = ConferenceStateBinding::Create(isolate, controller);
}

ConferenceBinding::~ConferenceBinding() {
  LOG(INFO) << __FUNCTIONW__;
}

void ConferenceBinding::Connect() {}
void ConferenceBinding::Disconnect() {}

bool ConferenceBinding::isInProgress() {
  return false;
}
bool ConferenceBinding::isEstablished() {
  return false;
}
bool ConferenceBinding::isEnded() {
  return false;
}
bool ConferenceBinding::isChatChannelSupported() {
  return false;
}
bool ConferenceBinding::isChatChannelEstablished() {
  return false;
}

// v8::Local<v8::Value> ConferenceBinding::State() {
//   if (state_controller_.IsEmpty()) {
//     state_controller_.Reset(isolate(), state_.ToV8());
//   }
//   return v8::Local<v8::Value>::New(isolate(), state_controller_);
// }

}  // namespace rtvc

}  // namespace yealink
