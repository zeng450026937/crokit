#ifndef YEALINK_RTVC_BINDING_LOCAL_CONTACT_BINDING_CC_
#define YEALINK_RTVC_BINDING_LOCAL_CONTACT_BINDING_CC_

#include "base/memory/weak_ptr.h"
#include "yealink/libvc/include/contact/local_contact_api.h"
#include "yealink/native_mate/dictionary.h"
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
  LocalContactBinding(v8::Isolate* isolate,
                      v8::Local<v8::Object> wrapper,
                      LocalContactConfig config);
  ~LocalContactBinding() override;

  int64_t Create(mate::Dictionary dict);
  int64_t Add(mate::Dictionary dict);

  bool Remove(int64_t uid);

  bool Update(int64_t uid, mate::Dictionary dict);
  bool Modify(int64_t uid, mate::Dictionary dict);

  v8::Local<v8::Value> Search(std::string keyword, mate::Arguments* args);
  v8::Local<v8::Value> SearchWith(std::string key,
                                  std::string value,
                                  mate::Arguments* args);

  v8::Local<v8::Value> Find(std::string key,
                            std::string value,
                            mate::Arguments* args);
  v8::Local<v8::Value> FindById(int64_t uid);
  v8::Local<v8::Value> FindByName(std::string name, mate::Arguments* args);

  v8::Local<v8::Value> GetNode(int64_t uid);
  v8::Local<v8::Value> GetNodeList(mate::Arguments* args);

 private:
  yealink::Array<yealink::LocalContactExternInfo> ExactFromDict(
      mate::Dictionary dict);

  LocalContactConfig config_;
  std::unique_ptr<LocalContactManager> contact_manager_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_LOCAL_CONTACT_BINDING_CC_
