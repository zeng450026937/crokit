#include "yealink/rtvc/binding/contact_node_binding.h"

#include <unordered_map>

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace rtvc {

namespace {
static std::unordered_map<std::string, int32_t> g_uid_map_;
}  // namespace

mate::WrappableBase* ContactNodeBinding::New(mate::Arguments* args) {
  return new ContactNodeBinding(args->isolate(), args->GetThis());
}

// static
mate::Handle<ContactNodeBinding> ContactNodeBinding::Create(
    v8::Isolate* isolate,
    ContactNode contact) {
  auto iter = g_uid_map_.find(contact.uid);

  if (iter == g_uid_map_.end()) {
    return mate::CreateHandle(isolate,
                              new ContactNodeBinding(isolate, contact));
  }

  int32_t weak_map_id = iter->second;

  auto binding = mate::TrackableObject<ContactNodeBinding>::FromWeakMapID(
      isolate, weak_map_id);

  if (binding) {
    binding->UpdateWith(contact);
    return mate::CreateHandle(isolate, binding);
  }

  return mate::CreateHandle(isolate, new ContactNodeBinding(isolate, contact));
}

// static
void ContactNodeBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  // prototype->SetClassName(mate::StringToV8(isolate, "ContactNode"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("uid", &ContactNodeBinding::uid)
      .SetProperty("type", &ContactNodeBinding::type)
      .SetProperty("parentId", &ContactNodeBinding::parentId)
      .SetProperty("childCounts", &ContactNodeBinding::childCounts)
      .SetProperty("name", &ContactNodeBinding::name)
      .SetProperty("i18nName", &ContactNodeBinding::i18nName)
      .SetProperty("pinyin", &ContactNodeBinding::pinyin)
      .SetProperty("pinyinAbbr", &ContactNodeBinding::pinyinAbbr)
      .SetProperty("email", &ContactNodeBinding::email)
      .SetProperty("phone", &ContactNodeBinding::phone)
      .SetProperty("mobile", &ContactNodeBinding::mobile)
      .SetProperty("number", &ContactNodeBinding::number)
      .SetProperty("fullNumber", &ContactNodeBinding::fullNumber);
}

ContactNodeBinding::ContactNodeBinding(v8::Isolate* isolate,
                                       ContactNode contact)
    : contact_(std::move(contact)), weak_factory_(this) {
  Init(isolate);
  g_uid_map_.emplace(contact_.uid, weak_map_id_);
}

ContactNodeBinding::ContactNodeBinding(v8::Isolate* isolate,
                                       v8::Local<v8::Object> wrapper)
    : weak_factory_(this) {
  InitWith(isolate, wrapper);
  NOTREACHED() << "Can not create ContactNode from javascript.";
}
ContactNodeBinding::~ContactNodeBinding() {
  g_uid_map_.erase(contact_.uid);
}

void ContactNodeBinding::UpdateWith(ContactNode contact) {
  contact_ = contact;
}

std::string ContactNodeBinding::uid() {
  return contact_.uid;
}
ContactNodeType ContactNodeBinding::type() {
  return contact_.type;
}
std::vector<std::string> ContactNodeBinding::parentId() {
  return contact_.parentId;
}
uint64_t ContactNodeBinding::childCounts() {
  return contact_.childCounts;
}

std::string ContactNodeBinding::name() {
  return contact_.name;
}
std::string ContactNodeBinding::i18nName() {
  return contact_.i18nName;
}
std::string ContactNodeBinding::pinyin() {
  return contact_.pinyin;
}
std::string ContactNodeBinding::pinyinAbbr() {
  return contact_.pinyinAbbr;
}
std::string ContactNodeBinding::email() {
  return contact_.email;
}
std::string ContactNodeBinding::phone() {
  return contact_.phone;
}
std::string ContactNodeBinding::mobile() {
  return contact_.mobile;
}
std::string ContactNodeBinding::number() {
  return contact_.number;
}
std::string ContactNodeBinding::fullNumber() {
  return contact_.fullNumber;
}

}  // namespace rtvc
