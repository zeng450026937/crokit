#include "yealink/rtvc/binding/local_contact_binding.h"

#include "base/logging.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/converter.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace mate {
template <>
struct Converter<yealink::LocalContactInfo> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::LocalContactInfo& val) {
    if (val.uid <= 0)
      return v8::Null(isolate);

    Dictionary dict = Dictionary::CreateEmpty(isolate);
    dict.Set("uid", val.uid);
    dict.Set("name", val.name);
    dict.Set("indexed", val.searchKey);

    auto& infos = val.externInfoList;

    for (size_t i = 0; i < infos.Size(); i++) {
      dict.Set(infos[i].type.ConstData(), infos[i].info.ConstData());
    }
    return dict.GetHandle();
  }
};
}  // namespace mate

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
      .MakeDestroyable()
      .SetMethod("create", &LocalContactBinding::Create)
      .SetMethod("add", &LocalContactBinding::Add)
      .SetMethod("remove", &LocalContactBinding::Remove)
      .SetMethod("update", &LocalContactBinding::Update)
      .SetMethod("modify", &LocalContactBinding::Modify)
      .SetMethod("search", &LocalContactBinding::Search)
      .SetMethod("searchWith", &LocalContactBinding::SearchWith)
      .SetMethod("find", &LocalContactBinding::Find)
      .SetMethod("findById", &LocalContactBinding::FindById)
      .SetMethod("findByName", &LocalContactBinding::FindByName)
      .SetMethod("getNode", &LocalContactBinding::GetNode)
      .SetMethod("getNodeList", &LocalContactBinding::GetNodeList);
}

LocalContactBinding::LocalContactBinding(v8::Isolate* isolate,
                                         v8::Local<v8::Object> wrapper)
    : contact_manager_(new yealink::LocalContactManager()) {
  InitWith(isolate, wrapper);
  contact_manager_->Init(".", "");
}
LocalContactBinding::~LocalContactBinding() {}

int64_t LocalContactBinding::Create(mate::Dictionary dict) {
  if (dict.IsEmpty()) {
    isolate()->ThrowException(v8::Exception::TypeError(
        mate::StringToV8(isolate(), "Object is required.")));
    return -1;
  }

  std::string name;
  if (!dict.Get("name", &name)) {
    isolate()->ThrowException(v8::Exception::Error(mate::StringToV8(
        isolate(), "Name is required as default indexed key.")));
    return -1;
  }
  std::string indexed;
  dict.Get("indexed", &indexed);

  return contact_manager_->AddContact(name.c_str(), indexed.c_str(),
                                      ExactFromDict(dict));
}

int64_t LocalContactBinding::Add(mate::Dictionary dict) {
  return Create(dict);
}

bool LocalContactBinding::Remove(int64_t uid) {
  return contact_manager_->DeleteContact(uid);
}

bool LocalContactBinding::Update(int64_t uid, mate::Dictionary dict) {
  std::string name;
  if (!dict.Get("name", &name)) {
    isolate()->ThrowException(v8::Exception::Error(mate::StringToV8(
        isolate(), "Name is required as default indexed key.")));
    return -1;
  }
  std::string indexed;
  dict.Get("indexed", &indexed);

  return contact_manager_->ModifyContact(uid, name.c_str(), indexed.c_str(),
                                         ExactFromDict(dict));
}

bool LocalContactBinding::Modify(int64_t uid, mate::Dictionary dict) {
  return Update(uid, dict);
}

v8::Local<v8::Value> LocalContactBinding::Search(std::string keyword,
                                                 mate::Arguments* args) {
  int64_t limit = 0;
  int64_t offset = 0;

  args->GetNext(&limit);
  args->GetNext(&offset);

  return mate::ConvertToV8(isolate(), contact_manager_->SearchContact(
                                          keyword.c_str(), limit, offset));
}
v8::Local<v8::Value> LocalContactBinding::SearchWith(std::string key,
                                                     std::string value,
                                                     mate::Arguments* args) {
  int64_t limit = 0;
  int64_t offset = 0;

  args->GetNext(&limit);
  args->GetNext(&offset);

  return mate::ConvertToV8(isolate(),
                           contact_manager_->SearchContactFuzzy(
                               key.c_str(), value.c_str(), limit, offset));
}

v8::Local<v8::Value> LocalContactBinding::Find(std::string key,
                                               std::string value,
                                               mate::Arguments* args) {
  int64_t limit = 0;
  int64_t offset = 0;

  args->GetNext(&limit);
  args->GetNext(&offset);

  return mate::ConvertToV8(
      isolate(),
      contact_manager_->FindContact(key.c_str(), value.c_str(), limit, offset));
}
v8::Local<v8::Value> LocalContactBinding::FindById(int64_t uid) {
  return mate::ConvertToV8(isolate(), contact_manager_->SearchContact(uid));
}
v8::Local<v8::Value> LocalContactBinding::FindByName(std::string name,
                                                     mate::Arguments* args) {
  int64_t limit = 0;
  int64_t offset = 0;

  args->GetNext(&limit);
  args->GetNext(&offset);

  return mate::ConvertToV8(
      isolate(), contact_manager_->FindContact(name.c_str(), limit, offset));
}

v8::Local<v8::Value> LocalContactBinding::GetNode(int64_t uid) {
  return FindById(uid);
}
v8::Local<v8::Value> LocalContactBinding::GetNodeList(mate::Arguments* args) {
  int64_t limit = 0;
  int64_t offset = 0;

  args->GetNext(&limit);
  args->GetNext(&offset);

  return mate::ConvertToV8(isolate(),
                           contact_manager_->GetContactList(limit, offset));
}

yealink::Array<yealink::LocalContactExternInfo>
LocalContactBinding::ExactFromDict(mate::Dictionary dict) {
  yealink::Array<yealink::LocalContactExternInfo> infos;

  auto properties = dict.GetHandle()
                        ->GetPropertyNames(isolate()->GetCurrentContext())
                        .ToLocalChecked();

  uint32_t length = properties->Length();
  for (uint32_t i = 0; i < length; ++i) {
    std::string key;
    if (!mate::ConvertFromV8(
            isolate(),
            properties->Get(isolate()->GetCurrentContext(), i).ToLocalChecked(),
            &key))
      return -1;
    if (key == "name")
      continue;
    std::string value;
    if (!dict.Get(key, &value))
      return -1;
    yealink::LocalContactExternInfo info;
    ConvertTo(key, info.type);
    ConvertTo(value, info.info);
    infos.Append(info);
  }

  return infos;
}

}  // namespace rtvc

}  // namespace yealink
