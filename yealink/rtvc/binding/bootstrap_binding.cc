#include "yealink/rtvc/binding/bootstrap_binding.h"

#include "base/task/post_task.h"
#include "yealink/libvc/include/access/access_agent_api.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/connector_binding.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace yealink {

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
      .SetMethod("authenticate", &BootstrapBinding::Authenticate)
      .SetMethod("getConnector", &BootstrapBinding::GetConnector);
}

BootstrapBinding::BootstrapBinding(v8::Isolate* isolate,
                                   v8::Local<v8::Object> wrapper,
                                   std::string client_id)
    : client_id_(client_id),
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

v8::Local<v8::Promise> BootstrapBinding::Authenticate() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  std::vector<AccountInfo>* result = new std::vector<AccountInfo>();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&BootstrapBinding::DoAuthenticate,
                     weak_factory_.GetWeakPtr(), base::Unretained(result)),
      base::BindOnce(
          [](Promise promise, const std::vector<AccountInfo>* result) {
            std::move(promise).Resolve(*result);
          },
          std::move(promise), base::Owned(result)));

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

void BootstrapBinding::DoAuthenticate(std::vector<AccountInfo>* result) {
  LoginInfo info;
  info.server = server_.c_str();
  info.username = username_.c_str();
  info.password = password_.c_str();
  ConvertFrom(*result, access_agent_->LoginAccessService(info, nullptr));
}

}  // namespace rtvc

}  // namespace yealink
