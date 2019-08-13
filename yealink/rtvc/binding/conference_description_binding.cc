#include "yealink/rtvc/binding/conference_description_binding.h"

#include "base/logging.h"
#include "yealink/native_mate/object_template_builder.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* ConferenceDescriptionBinding::New(mate::Arguments* args) {
  return new ConferenceDescriptionBinding(args->isolate(), args->GetThis());
}

// static
void ConferenceDescriptionBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "ConferenceDescription"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable();
}

ConferenceDescriptionBinding::ConferenceDescriptionBinding(
    v8::Isolate* isolate,
    v8::Local<v8::Object> wrapper) {}
ConferenceDescriptionBinding::~ConferenceDescriptionBinding() = default;

}  // namespace rtvc

}  // namespace yealink
