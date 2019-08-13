#include "yealink/rtvc/binding/conference_state_binding.h"

#include "base/logging.h"
#include "yealink/native_mate/object_template_builder.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* ConferenceStateBinding::New(mate::Arguments* args) {
  return new ConferenceStateBinding(args->isolate(), args->GetThis());
}

// static
void ConferenceStateBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "ConferenceState"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable();
}

ConferenceStateBinding::ConferenceStateBinding(
    v8::Isolate* isolate,
    v8::Local<v8::Object> wrapper) {}
ConferenceStateBinding::~ConferenceStateBinding() = default;

}  // namespace rtvc

}  // namespace yealink
