#ifndef YEALINK_RTVC_BINDING_USER_AGENT_BINDING_H_
#define YEALINK_RTVC_BINDING_USER_AGENT_BINDING_H_

#include "base/memory/weak_ptr.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/account_info.h"
#include "yealink/rtvc/api/user_agent.h"
#include "yealink/rtvc/binding/connector_binding.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/binding/sip_poller.h"

namespace rtvc {

class UserAgentBinding : public mate::EventEmitter<UserAgentBinding>,
                         public yealink::ConnectionHandler,
                         public yealink::AuthHandler,
                         public yealink::SIPClientHandler {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  UserAgentBinding(v8::Isolate* isolate,
                   v8::Local<v8::Object> wrapper,
                   yealink::AccessAgent* access_agent,
                   rtvc::UserAgent::Config config);
  ~UserAgentBinding() override;

  std::string workspace_folder();

  std::string username();
  std::string password();
  std::string ha1();
  std::string domain();
  std::string proxyServer();
  int64_t proxyPort();
  std::string language();

  void SetUsername(std::string username);
  void SetPassword(std::string password);
  void SetHa1(std::string ha1);
  void SetDomain(std::string domain);
  void SetProxyServer(std::string server);
  void SetProxyPort(int64_t port);
  void Setlanguage(std::string language);
  void SetConnector(mate::Handle<ConnectorBinding> connector);

  void Set(std::string key, mate::Arguments* args);
  v8::Local<v8::Value> Get(std::string key, mate::Arguments* args);

  void Start();
  void Stop();

  bool running();

  v8::Local<v8::Promise> Register();
  void UnRegister(mate::Arguments* args);

  bool registered();
  bool registering();

  // yealink::ConnectionHandler impl
  bool OnCertificateError(yealink::ConnectCertificateCode code) override;
  void OnConnectFailed(int message) override;
  void OnConnected() override;
  void OnConnectInterruption(int message) override;
  void OnReceivedData() override;

  // yealink::AuthHandler impl
  yealink::SByteData GetAuthParam(yealink::AuthParamType type) override;
  void OnAuthEvent(const yealink::AuthEvent& event) override;
  void OnICEProfile(const yealink::AuthICEProfile& turn,
                    const yealink::AuthICEProfile& stun) override;

  // yealink::SIPClientHandler impl
  void OnOffer(const yealink::SIPMessageReadonly& message,
               yealink::SIPInviteAgent** agent) override;

 private:
  friend class CallBinding;
  friend class ConferenceBinding;

  base::WeakPtr<UserAgentBinding> GetWeakPtr() {
    return weak_factory_.GetWeakPtr();
  }
  base::WeakPtr<yealink::SIPClient> GetWeakSIPClientPtr() {
    return sip_client_weak_factory_.GetWeakPtr();
  }
  yealink::AccessAgent* GetAccessAgent() { return access_agent_; }

  UserAgent::Config config_;

  bool registered_ = false;
  std::unique_ptr<Promise> register_promise_;

  yealink::SIPClient* sip_client_;
  base::WeakPtrFactory<yealink::SIPClient> sip_client_weak_factory_;
  std::unique_ptr<SIPPoller> sip_poller_;

  yealink::AccessAgent* access_agent_;

  base::WeakPtrFactory<UserAgentBinding> weak_factory_;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_USER_AGENT_BINDING_H_
