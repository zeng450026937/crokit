#include "yealink/rtvc/binding/user_agent_binding.h"

#include <memory>

#include "base/logging.h"
#include "node.h"
#include "yealink/native_mate/constructor.h"
#include "yealink/native_mate/dictionary.h"

namespace yealink {

namespace rtvc {

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
  LOG(INFO) << __FUNCTIONW__;
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
    : config_(std::move(config)) {
  InitWith(isolate, wrapper);
}
UserAgentBinding::~UserAgentBinding() {
  LOG(INFO) << __FUNCTIONW__;
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

void UserAgentBinding::Register() {
  LOG(INFO) << __FUNCTIONW__;
}
void UserAgentBinding::UnRegister() {
  LOG(INFO) << __FUNCTIONW__;
}

bool UserAgentBinding::registered() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}

}  // namespace rtvc

}  // namespace yealink
