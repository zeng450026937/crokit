#include "yealink/rtvc/binding/conference_user_binding.h"

#include "base/logging.h"
#include "yealink/native_mate/object_template_builder.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* ConferenceUserBinding::New(mate::Arguments* args) {
  return new ConferenceUserBinding(args->isolate(), args->GetThis());
}

// static
void ConferenceUserBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "ConferenceUser"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable();
}

ConferenceUserBinding::ConferenceUserBinding(
    v8::Isolate* isolate,
    v8::Local<v8::Object> wrapper) {}
ConferenceUserBinding::~ConferenceUserBinding() = default;

}  // namespace rtvc

}  // namespace yealink
