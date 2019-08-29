#include "yealink/rtvc/binding/conference_description_binding.h"

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* ConferenceDescriptionBinding::New(mate::Arguments* args) {
  return new ConferenceDescriptionBinding(args->isolate(), args->GetThis());
}

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
      .SetProperty("profile", &ConferenceDescriptionBinding::Profile);
}

void ConferenceDescriptionBinding::UpdateRoomController(
    RoomController* handler) {
  room_controller_ = handler;

  // state_->UpdateRoomController(handler);
}

ConferenceDescriptionBinding::ConferenceDescriptionBinding(
    v8::Isolate* isolate,
    v8::Local<v8::Object> wrapper) {
  InitWith(isolate, wrapper);
}

ConferenceDescriptionBinding::ConferenceDescriptionBinding(
    v8::Isolate* isolate,
    yealink::RoomController* controller) {
  Init(isolate);
  room_controller_ = controller;
  // state_ = ConferenceStateBinding::Create(isolate, controller);
}

ConferenceDescriptionBinding::~ConferenceDescriptionBinding() = default;

int ConferenceDescriptionBinding::Profile()
{
  if(room_controller_)
    return room_controller_->GetDescriptionComponent().GetConferenceDescription().profile;
  else
    return yealink::ConferenceDescription::Profile::TEACHING;
}

}  // namespace rtvc

}  // namespace yealink
