#ifndef YEALINK_RTVC_BINDING_LOCAL_CONTACT_BINDING_CC_
#define YEALINK_RTVC_BINDING_LOCAL_CONTACT_BINDING_CC_

#include "base/memory/weak_ptr.h"
#include "yealink/libvc/include/contact/local_contact_api.h"
#include "yealink/native_mate/handle.h"
#include "yealink/rtvc/api/contact.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/promise.h"

namespace yealink {

namespace rtvc {

class LocalContactBinding : public mate::EventEmitter<LocalContactBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  LocalContactBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ~LocalContactBinding() override;

  void Create();
  void Remove();
  void Update();
  void Search();
  void Add();
  void Modify();
  void Find();

 private:
  std::unique_ptr<LocalContactManager> contact_manager_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_LOCAL_CONTACT_BINDING_CC_
