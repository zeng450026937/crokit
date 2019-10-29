#include "yealink/rtvc/binding/bootstrap_binding.h"

#include "base/task/post_task.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/connector_binding.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace rtvc {

// static
mate::WrappableBase* BootstrapBinding::New(mate::Arguments* args) {
  std::string clientId;

  if (!(args->Length() == 1 && args->GetNext(&clientId))) {
    args->ThrowError("An unique client id is required.");
    return nullptr;
  }

  return new BootstrapBinding(args->isolate(), args->GetThis(), clientId);
}

// static
void BootstrapBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "Bootstrap"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("server", &BootstrapBinding::server,
                   &BootstrapBinding::SetServer)
      .SetProperty("username", &BootstrapBinding::username,
                   &BootstrapBinding::SetUsername)
      .SetProperty("password", &BootstrapBinding::password,
                   &BootstrapBinding::SetPassword)
      .SetProperty("debug", &BootstrapBinding::debug,
                   &BootstrapBinding::SetDebug)
      .SetProperty("smsVerify", &BootstrapBinding::smsVerify,
                   &BootstrapBinding::SetSmsVerify)
      .SetProperty("ha1", &BootstrapBinding::ha1, &BootstrapBinding::SetHa1)
      .SetProperty("language", &BootstrapBinding::language,
                   &BootstrapBinding::SetLanguage)
      .SetMethod("authenticate", &BootstrapBinding::Authenticate)
      .SetMethod("getConnector", &BootstrapBinding::GetConnector)
      .SetMethod("getToken", &BootstrapBinding::GetToken)
      .SetMethod("getPartyInviteInfo", &BootstrapBinding::GetPartyInviteInfo)
      .SetMethod("pushVerifyCode", &BootstrapBinding::PushVerifyCode);
}

BootstrapBinding::BootstrapBinding(v8::Isolate* isolate,
                                   v8::Local<v8::Object> wrapper,
                                   std::string client_id)
    : client_id_(client_id),
      debug_(false),
      sms_verify_(false),
      ha1_(""),
      access_agent_(yealink::CreateAccessAgent(client_id.c_str())),
      weak_factory_(this) {
  InitWith(isolate, wrapper);
}
BootstrapBinding::~BootstrapBinding() {
  yealink::ReleaseAccessAgent(access_agent_);
}

std::string BootstrapBinding::server() {
  return server_;
}
void BootstrapBinding::SetServer(std::string server) {
  server_ = server;
}

std::string BootstrapBinding::username() {
  return username_;
}
void BootstrapBinding::SetUsername(std::string username) {
  username_ = username;
}

std::string BootstrapBinding::password() {
  return password_;
}
void BootstrapBinding::SetPassword(std::string password) {
  password_ = password;
}

bool BootstrapBinding::debug() {
  return debug_;
}
void BootstrapBinding::SetDebug(bool debug) {
  debug_ = debug;
}

bool BootstrapBinding::smsVerify() {
  return sms_verify_;
}
void BootstrapBinding::SetSmsVerify(bool smsVerify) {
  sms_verify_ = smsVerify;
}

std::string BootstrapBinding::ha1() {
  return ha1_;
}
void BootstrapBinding::SetHa1(std::string ha1) {
  ha1_ = ha1;
}

std::string BootstrapBinding::language() {
  return language_;
}
void BootstrapBinding::SetLanguage(std::string language) {
  language_ = language;

  if (access_agent_)
    access_agent_->SetLanguage(language_.c_str());
}

v8::Local<v8::Promise> BootstrapBinding::Authenticate() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  AccessInfo* result = new AccessInfo();
  ProcessObserver* observer = new ProcessObserver();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&BootstrapBinding::DoAuthenticate,
                     weak_factory_.GetWeakPtr(), base::Unretained(result),
                     observer),
      base::BindOnce(
          [](Promise promise, const AccessInfo* result,
             ProcessObserver* observer) {
            int code = observer ? observer->bizCode() : 900500;

            if (code != 900200) {
              ErrorInfo error_result;
              error_result.biz_code = code;
              std::move(promise).Reject(error_result);
            }

            else
              std::move(promise).Resolve(*result);

            if (observer)
              delete observer;
          },
          std::move(promise), base::Owned(result), observer));

  return handle;
}

v8::Local<v8::Value> BootstrapBinding::GetConnector(std::string uid) {
  DCHECK(access_agent_);
  access_agent_->StartAccessPushService(uid.c_str());
  if (connector_.IsEmpty()) {
    auto handle = ConnectorBinding::Create(isolate(), access_agent_);
    connector_.Reset(isolate(), handle.ToV8());
  }
  return v8::Local<v8::Value>::New(isolate(), connector_);
}

std::string BootstrapBinding::GetToken(std::string uid) {
  DCHECK(access_agent_);
  yealink::LoginUserInfo info;
  info = access_agent_->GetLoginUserInfoById(uid.c_str());
  return std::string(info.token.ConstData());
}

v8::Local<v8::Promise> BootstrapBinding::GetPartyInviteInfo() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  PartyInviteInfos* result = new PartyInviteInfos();
  ProcessObserver* observer = new ProcessObserver();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&BootstrapBinding::DoGetPartyInviteInfo,
                     weak_factory_.GetWeakPtr(), base::Unretained(result),
                     observer),
      base::BindOnce(
          [](Promise promise, const PartyInviteInfos* result,
             ProcessObserver* observer) {
            int code = observer ? observer->bizCode() : 900500;

            if (code != 900200) {
              ErrorInfo error_result;
              error_result.biz_code = code;
              std::move(promise).Reject(error_result);
            }

            else
              std::move(promise).Resolve(*result);

            if (observer)
              delete observer;
          },
          std::move(promise), base::Owned(result), observer));

  return handle;
}

v8::Local<v8::Promise> BootstrapBinding::PushVerifyCode() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  bool* result = new bool();
  ProcessObserver* observer = new ProcessObserver();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&BootstrapBinding::DoPushVerifyCode,
                     weak_factory_.GetWeakPtr(), base::Unretained(result),
                     observer),
      base::BindOnce(
          [](Promise promise, const bool* result, ProcessObserver* observer) {
            int code = observer ? observer->bizCode() : 900500;

            if (code != 900200) {
              ErrorInfo error_result;
              error_result.biz_code = code;
              std::move(promise).Reject(error_result);
            }

            else
              std::move(promise).Resolve(*result);

            if (observer)
              delete observer;
          },
          std::move(promise), base::Owned(result), observer));

  return handle;
}

void BootstrapBinding::DoAuthenticate(AccessInfo* result,
                                      ProcessObserver* observer) {
  yealink::LoginInfo info;
  yealink::LoginUserInfos ret;
  info.server = server_.c_str();
  info.username = username_.c_str();
  info.password = ha1_.size() > 0 ? ha1_.c_str() : password_.c_str();
  info.isSmsVerify = sms_verify_;
  info.algorithm = ha1_.size() > 0 ? "a1_hash" : "";

  if (debug_ == true) {
    ret = access_agent_->UnscheduledLoginAccessService(info, observer);
  } else {
    ret = access_agent_->LoginAccessService(info, observer);
  }

  ConvertFrom(*result, ret);
}

void BootstrapBinding::DoGetPartyInviteInfo(PartyInviteInfos* result,
                                            ProcessObserver* observer) {
  if (result != nullptr && access_agent_ != nullptr) {
    ConvertFrom(*result, access_agent_->GetPartyInviteInfo(observer));
  }
}

void BootstrapBinding::DoPushVerifyCode(bool* result,
                                        ProcessObserver* observer) {
  if (result != nullptr && access_agent_ != nullptr) {
    if (debug_ == true)
      *result = access_agent_->UnscheduledSendMobileLoginVerifyCode(
          server_.c_str(), username_.c_str(), observer);
    else
      *result = access_agent_->SendMobileLoginVerifyCode(
          server_.c_str(), username_.c_str(), observer);
  }
}

}  // namespace rtvc
