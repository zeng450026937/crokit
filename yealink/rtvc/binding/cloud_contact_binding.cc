#include "yealink/rtvc/binding/cloud_contact_binding.h"

#include "base/logging.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/converter.h"
#include "yealink/native_mate/dictionary.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/connector_binding.h"
#include "yealink/rtvc/binding/contact_node_binding.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace mate {
template <>
struct Converter<yealink::rtvc::ContactNode> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::ContactNode& val) {
    return yealink::rtvc::ContactNodeBinding::Create(isolate, val).ToV8();
  }

  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ContactNode* out) {
    Dictionary dict;
    if (!ConvertFromV8(isolate, val, &dict))
      return false;
    dict.Get("uid", &(out->uid));
    dict.Get("type", &(out->type));
    dict.Get("parentId", &(out->parentId));
    dict.Get("childCounts", &(out->childCounts));
    dict.Get("name", &(out->name));
    dict.Get("i18nName", &(out->i18nName));
    dict.Get("pinyin", &(out->pinyin));
    dict.Get("pinyinAbbr", &(out->pinyinAbbr));
    dict.Get("email", &(out->email));
    dict.Get("phone", &(out->phone));
    dict.Get("mobile", &(out->mobile));
    dict.Get("number", &(out->number));
    dict.Get("fullNumber", &(out->fullNumber));
    return true;
  }
};
}  // namespace mate

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
  prototype->SetClassName(mate::StringToV8(isolate, "CloudContact"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("synced", &CloudContactBinding::synced)
      .SetProperty("loadMode", &CloudContactBinding::load_mode)
      .SetProperty("rootId", &CloudContactBinding::root_id)
      .SetMethod("sync", &CloudContactBinding::Sync)
      .SetMethod("search", &CloudContactBinding::Search)
      .SetMethod("getNode", &CloudContactBinding::GetNode)
      .SetMethod("getNodeChild", &CloudContactBinding::GetNodeChild);
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
  contact_manager_->AddObserver(this);
}
CloudContactBinding::~CloudContactBinding() {
  contact_manager_->RemoveObserver(this);
  contact_manager_->ReleaseManager();
}

bool CloudContactBinding::synced() {
  return contact_manager_->IsAvailable();
}

ContactLoadMode CloudContactBinding::load_mode() {
  ContactLoadMode mode = ContactLoadMode::kAuto;
  ConvertFrom(mode, contact_manager_->GetLoadMode());
  return mode;
}

std::string CloudContactBinding::root_id() {
  return contact_manager_->GetCompanyId().ConstData();
}

v8::Local<v8::Promise> CloudContactBinding::Sync() {
  if (!sync_promise_) {
    sync_promise_.reset(new Promise(isolate()));
    base::PostTask(FROM_HERE, base::BindOnce(&CloudContactBinding::DoSync,
                                             weak_factory_.GetWeakPtr()));
  }

  return sync_promise_->GetHandle();
}

v8::Local<v8::Promise> CloudContactBinding::Search(std::string keyword,
                                                   uint64_t offset,
                                                   uint64_t limit) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  std::vector<ContactNode>* result = new std::vector<ContactNode>();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&CloudContactBinding::DoSearch, weak_factory_.GetWeakPtr(),
                     std::move(keyword), offset, limit,
                     base::Unretained(result)),
      base::BindOnce(
          [](Promise promise, const std::vector<ContactNode>* result) {
            std::move(promise).Resolve(*result);
          },
          std::move(promise), base::Owned(result)));

  return handle;
}

ContactNode CloudContactBinding::GetNode(std::string nodeId) {
  ContactNode node;
  ConvertFrom(node, contact_manager_->GetNodeInfoById(nodeId.c_str()));
  return node;
}
std::vector<ContactNode> CloudContactBinding::GetNodeChild(std::string nodeId,
                                                           bool recursive) {
  std::vector<ContactNode> child;
  ConvertFrom(child,
              contact_manager_->GetSubNodeInfo(nodeId.c_str(), recursive, 0, 0,
                                               yealink::CC_NODE_ALL));
  return child;
}

void CloudContactBinding::OnUpdating() {
  LOG(INFO) << __FUNCTIONW__;
  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    context->PostTask(FROM_HERE,
                      base::BindOnce(&CloudContactBinding::OnUpdating,
                                     base::Unretained(this)));
    return;
  }
}
void CloudContactBinding::OnUpdateFinished() {
  LOG(INFO) << __FUNCTIONW__;

  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    context->PostTask(FROM_HERE,
                      base::BindOnce(&CloudContactBinding::OnUpdateFinished,
                                     base::Unretained(this)));
    return;
  }

  if (sync_promise_) {
    sync_promise_->Resolve();
    sync_promise_.reset();
    // isolate()->RunMicrotasks();
  }
}
void CloudContactBinding::OnEnableStatusChanged(bool available) {
  LOG(INFO) << __FUNCTIONW__;
}
void CloudContactBinding::OnNodeChange(
    const Array<CloudNodeChangeNotifyEntity>& changeData) {
  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    context->PostTask(FROM_HERE,
                      base::BindOnce(&CloudContactBinding::OnNodeChange,
                                     base::Unretained(this), changeData));
    return;
  }

  Emit("changed");
}

void CloudContactBinding::DoSync() {
  contact_manager_->Update();
}
void CloudContactBinding::DoSearch(std::string keyword,
                                   uint64_t offset,
                                   uint64_t limit,
                                   std::vector<ContactNode>* result) {
  ConvertFrom(*result, contact_manager_->SearchContactInfo(keyword.c_str(),
                                                           offset, limit));
}

}  // namespace rtvc

}  // namespace yealink
