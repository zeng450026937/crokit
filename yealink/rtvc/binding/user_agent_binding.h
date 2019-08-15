#ifndef YEALINK_RTVC_BINDING_USER_AGENT_BINDING_H_
#define YEALINK_RTVC_BINDING_USER_AGENT_BINDING_H_

#include "base/memory/weak_ptr.h"
#include "yealink/libvc/include/sip_agent/sip_agent_api.h"
#include "yealink/native_mate/handle.h"
#include "yealink/rtvc/api/user_agent.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/binding/sip_poller.h"

namespace yealink {

class SIPClient;

namespace rtvc {

class UserAgentBinding : public mate::EventEmitter<UserAgentBinding>,
                         public yealink::ConnectionHandler,
                         public yealink::AuthHandler {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  UserAgentBinding(v8::Isolate* isolate,
                   v8::Local<v8::Object> wrapper,
                   UserAgent::Config config);
  ~UserAgentBinding() override;

  std::string workspace_folder();

  std::string username();
  std::string password();
  std::string domain();

  v8::Local<v8::Promise> Register();
  void UnRegister();

  bool registered();
  bool registering();

  // yealink::ConnectionHandler impl
  void OnConnectFailed(int message) override;
  void OnConnected() override;
  void OnConnectInterruption(int message) override;
  void OnReceivedData() override;

  // yealink::AuthHandler impl
  yealink::SByteData GetAuthParam(yealink::AuthParamType type) override;
  void OnAuthEvent(const yealink::AuthEvent& event) override;
  void OnICEProfile(const yealink::AuthICEProfile& turn,
                    const yealink::AuthICEProfile& stun) override;

 private:
  UserAgent::Config config_;

  bool registered_ = false;
  std::unique_ptr<Promise> register_promise_;

  struct SIPClientDeleter {
    void operator()(yealink::SIPClient* c) { yealink::RealseSIPClient(c); }
  };
  std::unique_ptr<yealink::SIPClient, SIPClientDeleter> sip_client_;
  base::WeakPtrFactory<yealink::SIPClient> sip_client_weak_factory_;
  std::unique_ptr<SIPPoller> sip_poller_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_USER_AGENT_BINDING_H_
