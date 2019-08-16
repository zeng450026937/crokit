#include "yealink/rtvc/binding/schedule_binding.h"

#include "base/logging.h"
#include "yealink/native_mate/object_template_builder.h"

namespace yealink {

namespace rtvc {

mate::WrappableBase* ScheduleBinding::New(mate::Arguments* args) {
  return new ScheduleBinding(args->isolate(), args->GetThis());
}

// static
void ScheduleBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "Schedule"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable();
}

ScheduleBinding::ScheduleBinding(v8::Isolate* isolate,
                                 v8::Local<v8::Object> wrapper) {
  InitWith(isolate, wrapper);
}
ScheduleBinding::~ScheduleBinding() {}

}  // namespace rtvc

}  // namespace yealink
