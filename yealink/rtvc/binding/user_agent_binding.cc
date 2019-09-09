#include "yealink/rtvc/binding/user_agent_binding.h"

#include "base/logging.h"
#include "base/task/post_task.h"
#include "yealink/libvc/include/media/media_api.h"
#include "yealink/libvc/include/sip_agent/sip_agent_api.h"
#include "yealink/native_mate/dictionary.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/call_binding.h"
#include "yealink/rtvc/binding/context.h"

namespace yealink {

namespace rtvc {

namespace {
unsigned char falsy_value = 0;
unsigned char truthy_value = 0;
}  // namespace

// static
mate::WrappableBase* UserAgentBinding::New(mate::Arguments* args) {
  UserAgent::Config config;
  mate::Dictionary options;

  if (!args->GetNext(&options)) {
    args->ThrowError();
    return nullptr;
  }

  options.Get("username", &config.username);
  options.Get("password", &config.password);
  options.Get("domain", &config.domain);

  return new UserAgentBinding(args->isolate(), args->GetThis(), config);
}

// static
void UserAgentBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "UserAgent"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("workspaceFolder", &UserAgentBinding::workspace_folder)
      .SetProperty("username", &UserAgentBinding::username)
      .SetProperty("password", &UserAgentBinding::password)
      .SetProperty("domain", &UserAgentBinding::domain)
      .SetMethod("register", &UserAgentBinding::Register)
      .SetMethod("unregister", &UserAgentBinding::UnRegister)
      .SetProperty("registered", &UserAgentBinding::registered);
}

UserAgentBinding::UserAgentBinding(v8::Isolate* isolate,
                                   v8::Local<v8::Object> wrapper,
                                   UserAgent::Config config)
    : config_(std::move(config)),
      sip_client_(yealink::CreateSIPClient()),
      sip_client_weak_factory_(sip_client_),
      weak_factory_(this) {
  InitWith(isolate, wrapper);

  // TODO
  // move all settings to config
  sip_client_->SetUserAgent("Yealink VCD");
  sip_client_->SetClientInfo("Yealink VCD");
  sip_client_->SetSiteName("Yealink VCD");

  yealink::Address local_address;
  local_address.port = 5061;
  local_address.family = yealink::AF_IP_UNSPEC;
  sip_client_->AddTransport(local_address, yealink::TLS);
  local_address.port = 5060;
  sip_client_->AddTransport(local_address, yealink::TCP);
  sip_client_->AddTransport(local_address, yealink::UDP);

  sip_client_->SetConnectionHandler(this);
  sip_client_->SetAuthHandler(this);
  sip_client_->SetClientHandler(this);
}
UserAgentBinding::~UserAgentBinding() {
  UnRegister();
  sip_client_->SetClientHandler(nullptr);
  sip_client_->SetAuthHandler(nullptr);
  sip_client_->SetConnectionHandler(nullptr);
  Context::Instance()->PostTask(FROM_HERE,
                                base::BindOnce(
                                    [](yealink::SIPClient* sip_client) {
                                      yealink::RealseSIPClient(sip_client);
                                    },
                                    sip_client_));
};

std::string UserAgentBinding::workspace_folder() {
  return config_.workspace_folder.value_or("");
}

std::string UserAgentBinding::username() {
  return config_.username;
}
std::string UserAgentBinding::password() {
  return config_.password;
}
std::string UserAgentBinding::domain() {
  return config_.domain;
}

v8::Local<v8::Promise> UserAgentBinding::Register() {
  DCHECK(sip_client_);

  if (!register_promise_) {
    register_promise_.reset(new Promise(isolate()));
    sip_poller_.reset(new SIPPoller(Context::Instance()->GetTaskRunner(),
                                    sip_client_weak_factory_.GetWeakPtr()));

    yealink::ConnectionParam params;
    params.addrHost = config_.domain.c_str();
    params.hostPort = 5061;
    params.addrProxy = "";
    params.proxyPort = 0;

    sip_client_->Connect(params);
  }

  return register_promise_->GetHandle();
}

void UserAgentBinding::UnRegister() {
  if (!registered() && !registering())
    return;

  DCHECK(sip_client_);
  DCHECK(sip_poller_);

  sip_client_->Disconnect();
  Context::Instance()->GetTaskRunner()->DeleteSoon(FROM_HERE,
                                                   sip_poller_.release());

  register_promise_.reset();
  registered_ = false;
}

bool UserAgentBinding::registered() {
  return registered_;
}
bool UserAgentBinding::registering() {
  return !registered_ && register_promise_;
}

void UserAgentBinding::OnConnectFailed(int message) {
  Emit("connectFailed");
}
void UserAgentBinding::OnConnected() {
  Emit("connected");
}
void UserAgentBinding::OnConnectInterruption(int message) {
  Emit("connectFailed");
}
void UserAgentBinding::OnReceivedData() {}

yealink::SByteData UserAgentBinding::GetAuthParam(yealink::AuthParamType type) {
  switch (type) {
    case yealink::AUTH_PARAM_USERNAME:
      return yealink::SByteData(
          reinterpret_cast<const unsigned char*>(config_.username.c_str()),
          config_.username.size());
    case yealink::AUTH_PARAM_PASSWORD:
      return yealink::SByteData(
          reinterpret_cast<const unsigned char*>(config_.password.c_str()),
          config_.password.size());
    case yealink::AUTH_PARAM_PASSWORD_IS_A1HASH:
      return yealink::SByteData(
          reinterpret_cast<const unsigned char*>(&falsy_value), 1);
    case yealink::AUTH_PARAM_DISPLAY_NAME:
      break;
    default:
      NOTREACHED();
      break;
  }
  return yealink::SByteData();
}
void UserAgentBinding::OnAuthEvent(const yealink::AuthEvent& event) {
  DCHECK(register_promise_);

  switch (event.id) {
    case yealink::AEID_SUCCESS:
      register_promise_->Resolve(this);
      registered_ = true;
      Emit("registered");
      break;
    case yealink::AEID_FAILED:
      // TODO
      // reject error
      register_promise_->Reject();
      registered_ = false;
      Emit("registerFailed");
      break;
    default:
      NOTREACHED();
      break;
  }

  isolate()->RunMicrotasks();
}
void UserAgentBinding::OnICEProfile(const yealink::AuthICEProfile& turn,
                                    const yealink::AuthICEProfile& stun) {
  yealink::ICEProfile profile;
  profile.strServer = turn.strServer;
  profile.strUserName = turn.strUserName;
  profile.strPassword = turn.strPassword;
  profile.nUDPPort = turn.nUDPPort;
  profile.nTCPPort = turn.nTCPPort;
  Context::Instance()->GetMedia()->SetICEProfile(profile, false);
}

void UserAgentBinding::OnOffer(const SIPMessageReadonly& message,
                               SIPInviteAgent** agent) {
  auto call = CallBinding::Create(isolate(), this, true);
  *agent = call->GetMeeting()->MediaCallAgent();
}

}  // namespace rtvc

}  // namespace yealink
