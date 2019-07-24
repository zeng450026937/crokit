#include "yealink/rtvc/binding/user_agent.h"

#include "base/logging.h"
#include "node.h"
#include "yealink/native_mate/constructor.h"
#include "yealink/native_mate/dictionary.h"

namespace yealink {

namespace node {

// static
mate::WrappableBase* UserAgent::New(mate::Arguments* args) {
  api::UserAgent::Config config;

  mate::Dictionary options;
  if (args->GetNext(&options)) {
    options.Get("username", &config.username);
    options.Get("password", &config.password);
    options.Get("domain", &config.domain);
  }

  return new UserAgent(args->isolate(), args->GetThis(), config);
}

// static
void UserAgent::BuildPrototype(v8::Isolate* isolate,
                               v8::Local<v8::FunctionTemplate> prototype) {
  LOG(INFO) << __FUNCTIONW__;
  prototype->SetClassName(mate::StringToV8(isolate, "UserAgent"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetMethod("workspaceFolder", &UserAgent::workspace_folder)
      .SetMethod("username", &UserAgent::username)
      .SetMethod("password", &UserAgent::password)
      .SetMethod("domain", &UserAgent::domain)
      .SetMethod("register", &UserAgent::Register)
      .SetMethod("unregister", &UserAgent::UnRegister)
      .SetMethod("registered", &UserAgent::registered)
      .SetMethod("call", &UserAgent::Call)
      .SetMethod("send", &UserAgent::Send);
}

UserAgent::UserAgent(v8::Isolate* isolate,
                     v8::Local<v8::Object> wrapper,
                     api::UserAgent::Config config)
    : config_(std::move(config)) {
  InitWith(isolate, wrapper);
}
UserAgent::~UserAgent() = default;

std::string UserAgent::workspace_folder() {
  LOG(INFO) << __FUNCTIONW__;
  return config_.workspace_folder.value_or("");
}

std::string UserAgent::username() {
  LOG(INFO) << __FUNCTIONW__;
  return config_.username;
}
std::string UserAgent::password() {
  LOG(INFO) << __FUNCTIONW__;
  return config_.password;
}
std::string UserAgent::domain() {
  LOG(INFO) << __FUNCTIONW__;
  return config_.domain;
}

void UserAgent::Register() {
  LOG(INFO) << __FUNCTIONW__;
}
void UserAgent::UnRegister() {
  LOG(INFO) << __FUNCTIONW__;
}

bool UserAgent::registered() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}

void UserAgent::Call(std::string target) {
  LOG(INFO) << __FUNCTIONW__;
}
void UserAgent::Send(std::string target, std::string msg) {
  LOG(INFO) << __FUNCTIONW__;
}

}  // namespace node

}  // namespace yealink

// namespace {

// void Initialize(v8::Local<v8::Object> exports,
//                 v8::Local<v8::Value> unused,
//                 v8::Local<v8::Context> context,
//                 void* priv) {
//   LOG(INFO) << __FUNCTIONW__;
//   v8::Isolate* isolate = context->GetIsolate();
//   mate::Dictionary dict(isolate, exports);
//   dict.Set("UserAgent", yealink::node::UserAgent::GetConstructor(isolate)
//                             ->GetFunction(context)
//                             .ToLocalChecked());
// }

// }  // namespace

// NODE_MODULE_CONTEXT_AWARE(yealink_rtvc, Initialize)
