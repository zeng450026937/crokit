#include "yealink/rtvc/binding/bootstrap_binding.h"

#include "base/synchronization/waitable_event.h"
#include "base/task/post_task.h"
#include "base/task/task_traits.h"
#include "base/threading/platform_thread.h"
#include "yealink/libvc/include/access/access_agent_api.h"
#include "yealink/native_mate/object_template_builder.h"

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
      .SetMethod("authenticate", &BootstrapBinding::Authenticate);
}

BootstrapBinding::BootstrapBinding(v8::Isolate* isolate,
                                   v8::Local<v8::Object> wrapper,
                                   std::string client_id)
    : client_id_(client_id),
      access_agent_(yealink::CreateAccessAgent(client_id.c_str())) {
  InitWith(isolate, wrapper);
}
BootstrapBinding::~BootstrapBinding() {}

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

  base::PostTaskWithTraitsAndReply(
      FROM_HERE,
      {base::TaskShutdownBehavior::BLOCK_SHUTDOWN,
       base::TaskPriority::BEST_EFFORT, base::MayBlock()},
      base::BindOnce(&BootstrapBinding::DoAuthenticate, base::Unretained(this)),
      base::BindOnce(&BootstrapBinding::OnAuthenticateCompeleted,
                     base::Unretained(this), std::move(promise)));

  return handle;
}

void BootstrapBinding::DoAuthenticate() {
  LoginInfo info;
  info.server = server_.c_str();
  info.username = username_.c_str();
  info.password = password_.c_str();

  Array<LoginUserInfo> account_list_ =
      access_agent_->LoginAccessService(info, nullptr);
}
void BootstrapBinding::OnAuthenticateCompeleted(Promise promise) {
  std::move(promise).Resolve("resolved");
}

}  // namespace rtvc

}  // namespace yealink
