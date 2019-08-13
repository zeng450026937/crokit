#include "yealink/rtvc/binding/conference_view_binding.h"

#include "base/logging.h"
#include "yealink/native_mate/object_template_builder.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* ConferenceViewBinding::New(mate::Arguments* args) {
  return new ConferenceViewBinding(args->isolate(), args->GetThis());
}

// static
void ConferenceViewBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "ConferenceView"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable();
}

ConferenceViewBinding::ConferenceViewBinding(
    v8::Isolate* isolate,
    v8::Local<v8::Object> wrapper) {}
ConferenceViewBinding::~ConferenceViewBinding() = default;

}  // namespace rtvc

}  // namespace yealink
