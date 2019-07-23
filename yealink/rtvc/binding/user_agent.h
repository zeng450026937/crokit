#ifndef YEALINK_RTVC_BINDING_USER_AGENT_H_
#define YEALINK_RTVC_BINDING_USER_AGENT_H_

#include "yealink/native_mate/handle.h"
#include "yealink/rtvc/api/user_agent.h"
#include "yealink/rtvc/binding/event_emitter.h"

namespace yealink {

namespace node {

class UserAgent : public mate::EventEmitter<UserAgent>, api::UserAgent {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  UserAgent(v8::Isolate* isolate,
            v8::Local<v8::Object> wrapper,
            api::UserAgent::Config config);
  ~UserAgent() override;

  std::string workspace_folder() override;

  std::string username() override;
  std::string password() override;
  std::string domain() override;

  void Register() override;
  void UnRegister() override;

  bool registered() override;

  void Call(std::string target) override;
  void Send(std::string target, std::string msg) override;

 private:
  api::UserAgent::Config config_;
};

}  // namespace node

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_USER_AGENT_H_
