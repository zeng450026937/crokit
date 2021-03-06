#ifndef YEALINK_RTVC_BINDING_BOOTSTRAP_BINDING_CC_
#define YEALINK_RTVC_BINDING_BOOTSTRAP_BINDING_CC_

#include <string>

#include "base/memory/weak_ptr.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/account_info.h"
#include "yealink/rtvc/binding/promise.h"

namespace yealink {

class AccessAgent;

namespace rtvc {

class BootstrapBinding : public mate::Wrappable<BootstrapBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  BootstrapBinding(v8::Isolate* isolate,
                   v8::Local<v8::Object> wrapper,
                   std::string client_id);
  ~BootstrapBinding() override;

  std::string server();
  void SetServer(std::string server);

  std::string username();
  void SetUsername(std::string username);

  std::string password();
  void SetPassword(std::string password);

  bool debug();
  void SetDebug(bool debug);

  v8::Local<v8::Promise> Authenticate();
  v8::Local<v8::Value> GetConnector(std::string uid);

 private:
  void DoAuthenticate(std::vector<AccountInfo>* result);

  std::string server_;
  std::string username_;
  std::string password_;
  std::string client_id_;
  bool debug_;

  v8::Global<v8::Value> connector_;

  AccessAgent* access_agent_;

  base::WeakPtrFactory<BootstrapBinding> weak_factory_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_BOOTSTRAP_BINDING_CC_
