#ifndef YEALINK_RTVC_BINDING_CLOUD_CONTACT_BINDING_H_
#define YEALINK_RTVC_BINDING_CLOUD_CONTACT_BINDING_H_

#include "base/memory/weak_ptr.h"
#include "yealink/libvc/include/contact/cloud_contact_api.h"
#include "yealink/native_mate/handle.h"
#include "yealink/rtvc/binding/event_emitter.h"

namespace yealink {

class AccessAgent;

namespace rtvc {

class CloudContactBinding : public mate::EventEmitter<CloudContactBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  CloudContactBinding(v8::Isolate* isolate,
                      v8::Local<v8::Object> wrapper,
                      yealink::AccessAgent* access_agent);
  ~CloudContactBinding() override;

  bool synced();
  void load_mode();

  std::string root_id();
  std::string self_id();

  v8::Local<v8::Promise> Sync();
  v8::Local<v8::Promise> Search();

 private:
  void DoSync();
  void DoSearch();

  yealink::AccessAgent* access_agent_;
  std::unique_ptr<yealink::CloudContactManager> contact_manager_;

  base::WeakPtrFactory<CloudContactBinding> weak_factory_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CLOUD_CONTACT_BINDING_H_
