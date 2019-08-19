#include "yealink/rtvc/binding/cloud_contact_binding.h"

#include "base/logging.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/converter.h"
#include "yealink/native_mate/dictionary.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/connector_binding.h"
#include "yealink/rtvc/binding/promise.h"

namespace yealink {

namespace rtvc {

mate::WrappableBase* CloudContactBinding::New(mate::Arguments* args) {
  mate::Dictionary dict;
  mate::Handle<ConnectorBinding> connector;

  if (args->Length() != 1 || !args->GetNext(&dict)) {
    args->ThrowError("Config is required.");
    return nullptr;
  }
  if (!dict.Get("connector", &connector)) {
    args->ThrowError("connector is required.");
    return nullptr;
  }

  return new CloudContactBinding(args->isolate(), args->GetThis(),
                                 connector->GetAccessAgent());
}

// static
void CloudContactBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "Contact"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable();
}

CloudContactBinding::CloudContactBinding(v8::Isolate* isolate,
                                         v8::Local<v8::Object> wrapper,
                                         yealink::AccessAgent* access_agent)
    : access_agent_(access_agent),
      contact_manager_(new yealink::CloudContactManager()),
      weak_factory_(this) {
  DCHECK(access_agent_);
  InitWith(isolate, wrapper);
  contact_manager_->SetCloudPhoneBookConf(access_agent_, "", ".", "");
}
CloudContactBinding::~CloudContactBinding() {
  contact_manager_->ReleaseManager();
}

bool CloudContactBinding::synced() {
  return contact_manager_->IsAvailable();
}

void CloudContactBinding::load_mode() {
  contact_manager_->GetLoadMode();
}

std::string CloudContactBinding::root_id() {
  return contact_manager_->GetCompanyId().ConstData();
}
std::string CloudContactBinding::self_id() {
  return contact_manager_->GetMyId().ConstData();
}

v8::Local<v8::Promise> CloudContactBinding::Sync() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&CloudContactBinding::DoSync, weak_factory_.GetWeakPtr()),
      base::BindOnce(&Promise::ResolveEmptyPromise, std::move(promise)));

  return handle;
}

v8::Local<v8::Promise> CloudContactBinding::Search() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&CloudContactBinding::DoSearch,
                     weak_factory_.GetWeakPtr()),
      base::BindOnce(&Promise::ResolveEmptyPromise, std::move(promise)));

  return handle;
}

void CloudContactBinding::DoSync() {
  contact_manager_->Update();
}
void CloudContactBinding::DoSearch() {}

}  // namespace rtvc

}  // namespace yealink
