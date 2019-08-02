#ifndef YEALINK_RTVC_BINDING_USER_AGENT_BINDING_H_
#define YEALINK_RTVC_BINDING_USER_AGENT_BINDING_H_

#include "yealink/native_mate/handle.h"
#include "yealink/rtvc/api/user_agent.h"
#include "yealink/rtvc/binding/event_emitter.h"

namespace yealink {

namespace rtvc {

class UserAgentBinding : public mate::EventEmitter<UserAgentBinding>,
                         UserAgent {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  UserAgentBinding(v8::Isolate* isolate,
                   v8::Local<v8::Object> wrapper,
                   std::unique_ptr<UserAgent> impl);
  ~UserAgentBinding() override;

  std::string workspace_folder() override;

  std::string username() override;
  std::string password() override;
  std::string domain() override;

  void Register() override;
  void UnRegister() override;

  bool registered() override;

 private:
  std::unique_ptr<UserAgent> impl_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_USER_AGENT_BINDING_H_
