#include "yealink/rtvc/binding/user_agent_binding.h"

#include "base/logging.h"
#include "base/task/post_task.h"
#include "yealink/libvc/include/media/media_api.h"
#include "yealink/libvc/include/sip_agent/sip_agent_api.h"
#include "yealink/native_mate/dictionary.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/call_binding.h"
#include "yealink/rtvc/binding/context.h"

namespace rtvc {

namespace {
unsigned char falsy_value = 0;
unsigned char truthy_value = 1;
char* default_useragent = (char*)"Yealink VCD-H5";
char* default_client_info = (char*)"Yealink VCD-H5";
char* default_sitename = (char*)"Yealink VCD-H5";
}  // namespace

// static
mate::WrappableBase* UserAgentBinding::New(mate::Arguments* args) {
  UserAgent::Config config;
  mate::Dictionary options;
  mate::Handle<ConnectorBinding> connector;
  yealink::AccessAgent* access_agent = nullptr;

  config.useragent = default_useragent;
  config.client_info = default_client_info;
  config.sitename = default_sitename;

  std::string proxy_server;

  if (args->GetNext(&options)) {
    options.Get("username", &config.username);
    options.Get("password", &config.password);
    options.Get("ha1", &config.ha1);
    options.Get("domain", &config.domain);
    options.Get("displayName", &config.display_name);
    options.Get("userAgent", &config.useragent);
    options.Get("clientInfo", &config.client_info);
    options.Get("sitename", &config.sitename);
    options.Get("tlsPort", &config.tls_port);
    options.Get("tcpPort", &config.tcp_port);
    options.Get("udpPort", &config.udp_port);
    options.Get("ipv4Only", &config.ipv4_only);
    options.Get("ipv6Only", &config.ipv6_only);
    options.Get("proxyServer", &proxy_server);
    options.Get("proxyPort", &config.proxy_port);
    options.Get("connector", &connector);

    config.proxy_server = proxy_server;
  }

  if (!connector.IsEmpty()) {
    access_agent = connector->GetAccessAgent();
  }

  return new UserAgentBinding(args->isolate(), args->GetThis(), access_agent,
                              config);
}

// static
void UserAgentBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "UserAgent"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("workspaceFolder", &UserAgentBinding::workspace_folder)
      .SetProperty("username", &UserAgentBinding::username,
                   &UserAgentBinding::SetUsername)
      .SetProperty("password", &UserAgentBinding::password,
                   &UserAgentBinding::SetPassword)
      .SetProperty("ha1", &UserAgentBinding::ha1, &UserAgentBinding::SetHa1)
      .SetProperty("domain", &UserAgentBinding::domain,
                   &UserAgentBinding::SetDomain)
      .SetProperty("proxyServer", &UserAgentBinding::proxyServer,
                   &UserAgentBinding::SetProxyServer)
      .SetProperty("proxyPort", &UserAgentBinding::proxyPort,
                   &UserAgentBinding::SetProxyPort)
      .SetMethod("set", &UserAgentBinding::Set)
      .SetMethod("get", &UserAgentBinding::Get)
      .SetMethod("start", &UserAgentBinding::Start)
      .SetMethod("stop", &UserAgentBinding::Stop)
      .SetProperty("running", &UserAgentBinding::running)
      .SetMethod("register", &UserAgentBinding::Register)
      .SetMethod("unregister", &UserAgentBinding::UnRegister)
      .SetProperty("registered", &UserAgentBinding::registered)
      .SetMethod("setConnector", &UserAgentBinding::SetConnector);
}

UserAgentBinding::UserAgentBinding(v8::Isolate* isolate,
                                   v8::Local<v8::Object> wrapper,
                                   yealink::AccessAgent* access_agent,
                                   UserAgent::Config config)
    : config_(std::move(config)),
      sip_client_(yealink::CreateSIPClient()),
      sip_client_weak_factory_(sip_client_),
      access_agent_(access_agent),
      weak_factory_(this) {
  InitWith(isolate, wrapper);

  sip_client_->SetUserAgent(config_.useragent.c_str());
  sip_client_->SetClientInfo(config_.client_info.c_str());
  sip_client_->SetSiteName(config_.sitename.c_str());

  yealink::Address local_address;
  local_address.family =
      config_.ipv4_only
          ? yealink::AF_IPV4
          : config_.ipv6_only ? yealink::AF_IPV6 : yealink::AF_IP_UNSPEC;

  local_address.port = config_.tls_port;
  while (!sip_client_->AddTransport(local_address, yealink::TLS)) {
    local_address.port++;
  }

  local_address.port = config_.tcp_port;
  while (!sip_client_->AddTransport(local_address, yealink::TCP)) {
    local_address.port++;
  }

  local_address.port = config_.udp_port;
  while (!sip_client_->AddTransport(local_address, yealink::UDP)) {
    local_address.port++;
  }

  sip_client_->SetConnectionHandler(this);
  sip_client_->SetAuthHandler(this);
  sip_client_->SetClientHandler(this);
}
UserAgentBinding::~UserAgentBinding() {
  Stop();
  sip_client_->SetClientHandler(nullptr);
  sip_client_->SetAuthHandler(nullptr);
  sip_client_->SetConnectionHandler(nullptr);
  yealink::RealseSIPClient(sip_client_);
  // Context::Instance()->PostTask(FROM_HERE,
  //                               base::BindOnce(
  //                                   [](yealink::SIPClient* sip_client) {
  //                                     yealink::RealseSIPClient(sip_client);
  //                                   },
  //                                   sip_client_));
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
std::string UserAgentBinding::ha1() {
  return config_.ha1;
}
std::string UserAgentBinding::domain() {
  return config_.domain;
}
std::string UserAgentBinding::proxyServer() {
  return config_.proxy_server.value_or("");
}
int64_t UserAgentBinding::proxyPort() {
  return config_.proxy_port;
}

void UserAgentBinding::SetUsername(std::string username) {
  config_.username = username;
}
void UserAgentBinding::SetPassword(std::string password) {
  config_.password = password;
}
void UserAgentBinding::SetHa1(std::string ha1) {
  config_.ha1 = ha1;
}
void UserAgentBinding::SetDomain(std::string domain) {
  config_.domain = domain;
}

void UserAgentBinding::SetProxyServer(std::string server) {
  config_.proxy_server = server;
}
void UserAgentBinding::SetProxyPort(int64_t port) {
  config_.proxy_port = port;
}

void UserAgentBinding::SetConnector(mate::Handle<ConnectorBinding> connector) {
  if (!connector.IsEmpty())
    access_agent_ = connector->GetAccessAgent();
}

void UserAgentBinding::Set(std::string key, mate::Arguments* args) {
  if (key == "username") {
    std::string value;
    if (args->GetNext(&value)) {
      config_.username = value;
    }
  } else if (key == "password") {
    std::string value;
    if (args->GetNext(&value)) {
      config_.password = value;
    }
  } else if (key == "ha1") {
    std::string value;
    if (args->GetNext(&value)) {
      config_.ha1 = value;
    }
  } else if (key == "domain") {
    std::string value;
    if (args->GetNext(&value)) {
      config_.domain = value;
    }
  } else if (key == "proxyServer") {
    std::string value;
    if (args->GetNext(&value)) {
      config_.proxy_server = value;
    }
  } else if (key == "proxyPort") {
    int64_t value;
    if (args->GetNext(&value)) {
      config_.proxy_port = value;
    }
  } else {
    args->ThrowError("Unknown setting key");
  }
}
v8::Local<v8::Value> UserAgentBinding::Get(std::string key,
                                           mate::Arguments* args) {
  if (key == "username") {
    return mate::ConvertToV8(isolate(), config_.username);
  } else if (key == "password") {
    return mate::ConvertToV8(isolate(), config_.password);
  } else if (key == "ha1") {
    return mate::ConvertToV8(isolate(), config_.ha1);
  } else if (key == "domain") {
    return mate::ConvertToV8(isolate(), config_.domain);
  } else if (key == "proxyServer") {
    return mate::ConvertToV8(isolate(), config_.proxy_server.value_or(""));
  } else if (key == "proxyPort") {
    return mate::ConvertToV8(isolate(), config_.proxy_port);
  } else {
    args->ThrowError("Unknown setting key");
    return v8::Null(isolate());
  }
}

void UserAgentBinding::Start() {
  if (running())
    return;
  sip_poller_.reset(new SIPPoller(Context::Instance()->GetTaskRunner(),
                                  sip_client_weak_factory_.GetWeakPtr()));
}
void UserAgentBinding::Stop() {
  if (!running())
    return;

  if (registered() || registering()) {
    sip_client_->Disconnect();
    register_promise_.reset();
    registered_ = false;
  }

  Context::Instance()->GetTaskRunner()->DeleteSoon(FROM_HERE,
                                                   sip_poller_.release());
}
bool UserAgentBinding::running() {
  return !!sip_poller_;
}

v8::Local<v8::Promise> UserAgentBinding::Register() {
  DCHECK(sip_client_);

  if (!register_promise_) {
    register_promise_.reset(new Promise(isolate()));

    yealink::ConnectionParam params;
    params.addrHost = config_.domain.c_str();
    params.hostPort = 0;

    std::string proxy_server = config_.proxy_server.value_or("");
    params.addrProxy = proxy_server.c_str();
    params.proxyPort = config_.proxy_port > 0 ? config_.proxy_port : 5061;

    sip_client_->Connect(params);

    Start();
  }

  return register_promise_->GetHandle();
}

void UserAgentBinding::UnRegister(mate::Arguments* args) {
  if (!registered() && !registering())
    return;

  bool stop_running = false;

  args->GetNext(&stop_running);

  DCHECK(sip_client_);

  sip_client_->Disconnect();
  register_promise_.reset();
  registered_ = false;

  if (stop_running)
    Stop();
}

bool UserAgentBinding::registered() {
  return registered_;
}
bool UserAgentBinding::registering() {
  return !registered_ && register_promise_;
}

bool UserAgentBinding::OnCertificateError(
    yealink::ConnectCertificateCode code) {
  Emit("certificateError", (int64_t)code);
  return true;  // ignore error
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
  bool is_ha1 = !!config_.ha1.size();

  switch (type) {
    case yealink::AUTH_PARAM_USERNAME:
      return yealink::SByteData(
          reinterpret_cast<const unsigned char*>(config_.username.c_str()),
          config_.username.size());
    case yealink::AUTH_PARAM_PASSWORD:
      return yealink::SByteData(
          reinterpret_cast<const unsigned char*>(
              is_ha1 ? config_.ha1.c_str() : config_.password.c_str()),
          is_ha1 ? config_.ha1.size() : config_.password.size());
    case yealink::AUTH_PARAM_PASSWORD_IS_A1HASH:
      return yealink::SByteData(reinterpret_cast<const unsigned char*>(
                                    is_ha1 ? &truthy_value : &falsy_value),
                                1);
    case yealink::AUTH_PARAM_DISPLAY_NAME:
      break;
    case yealink::AUTH_PARAM_CLIENT_ID:
      break;
    case yealink::AUTH_PARAM_SUBJECT_ID:
      break;
    case yealink::AUTH_PARAM_GRUU:
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
      register_promise_->Reject();
      registered_ = false;
      Emit("registerFailed");
      break;
    case yealink::AEID_UPDATED: {
      size_t i;
      int bizCode = 900599;  // default unknown code
      std::string strScheme;

      for (i = 0; i < event.reasons.Size(); i++) {
        strScheme = event.reasons[i].strScheme.ConstData();
        if (strScheme.find("APOLLO-BIZ", 0) != -1) {
          bizCode = event.reasons[i].nCode;
          break;
        }
      }

      Emit("reconnectNeeded", bizCode);
      break;
    }
    default:
      NOTREACHED();
      break;
  }

  // isolate()->RunMicrotasks();
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

void UserAgentBinding::OnOffer(const yealink::SIPMessageReadonly& message,
                               yealink::SIPInviteAgent** agent) {
  auto call = CallBinding::Create(isolate(), this, access_agent_);
  *agent = call->GetMeeting()->MediaCallAgent();
}

}  // namespace rtvc
