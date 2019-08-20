#include "yealink/rtvc/binding/local_contact_binding.h"

#include "base/logging.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/converter.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* LocalContactBinding::New(mate::Arguments* args) {
  return new LocalContactBinding(args->isolate(), args->GetThis());
}

// static
void LocalContactBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "LocalContact"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable();
}

LocalContactBinding::LocalContactBinding(v8::Isolate* isolate,
                                         v8::Local<v8::Object> wrapper)
    : contact_manager_(new yealink::LocalContactManager()) {
  InitWith(isolate, wrapper);
  contact_manager_->Init(".", "");
}
LocalContactBinding::~LocalContactBinding() {}

void LocalContactBinding::Create() {}
void LocalContactBinding::Remove() {}
void LocalContactBinding::Update() {}
void LocalContactBinding::Search() {}
void LocalContactBinding::Add() {}
void LocalContactBinding::Modify() {}
void LocalContactBinding::Find() {}

}  // namespace rtvc

}  // namespace yealink
