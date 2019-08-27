#ifndef YEALINK_RTVC_BINDING_CONTACT_NODE_BINDING_H_
#define YEALINK_RTVC_BINDING_CONTACT_NODE_BINDING_H_

#include "base/supports_user_data.h"
#include "yealink/native_mate/handle.h"
#include "yealink/rtvc/api/contact.h"
#include "yealink/rtvc/binding/trackable_object.h"

namespace yealink {

namespace rtvc {

class ContactNodeBinding : public mate::TrackableObject<ContactNodeBinding>,
                           public base::SupportsUserData {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<ContactNodeBinding> Create(v8::Isolate* isolate,
                                                 ContactNode contact);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void UpdateWith(ContactNode contact);

 protected:
  ContactNodeBinding(v8::Isolate* isolate, ContactNode contact);
  ContactNodeBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ~ContactNodeBinding() override;

  std::string uid();
  ContactNodeType type();
  std::vector<std::string> parentId();
  uint64_t childCounts();

  std::string name();
  std::string i18nName();
  std::string pinyin();
  std::string pinyinAbbr();
  std::string email();
  std::string phone();
  std::string mobile();
  std::string number();
  std::string fullNumber();

 private:
  ContactNode contact_;

  base::WeakPtrFactory<ContactNodeBinding> weak_factory_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONTACT_NODE_BINDING_H_
