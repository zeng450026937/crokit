#ifndef YEALINK_RTVC_BINDING_CLOUD_CONTACT_BINDING_H_
#define YEALINK_RTVC_BINDING_CLOUD_CONTACT_BINDING_H_

#include "base/memory/weak_ptr.h"
#include "yealink/libvc/include/contact/cloud_contact_api.h"
#include "yealink/native_mate/handle.h"
#include "yealink/rtvc/api/contact.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/promise.h"

namespace yealink {

class AccessAgent;

namespace rtvc {

class CloudContactBinding : public mate::EventEmitter<CloudContactBinding>,
                            public yealink::CloudContactObserver {
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
  ContactLoadMode load_mode();

  std::string root_id();

  v8::Local<v8::Promise> Sync();
  v8::Local<v8::Promise> Search(std::string keyword,
                                uint64_t offset,
                                uint64_t limit);

  ContactNode GetNode(std::string nodeId);
  std::vector<ContactNode> GetNodeChild(std::string nodeId, bool recursive);
  uint64_t GetNodeChildCounts(std::string nodeId, bool recursive);

  // CloudContactObserver impl
  void OnUpdating() override;
  void OnUpdateFinished() override;
  void OnEnableStatusChanged(bool available) override;
  void OnNodeChange(
      const Array<CloudNodeChangeNotifyEntity>& changeData) override;

 private:
  void DoSync();
  void DoSearch(std::string keyword,
                uint64_t offset,
                uint64_t limit,
                std::vector<ContactNode>* result);

  yealink::AccessAgent* access_agent_;
  std::unique_ptr<yealink::CloudContactManager> contact_manager_;

  std::unique_ptr<Promise> sync_promise_;

  base::WeakPtrFactory<CloudContactBinding> weak_factory_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CLOUD_CONTACT_BINDING_H_
