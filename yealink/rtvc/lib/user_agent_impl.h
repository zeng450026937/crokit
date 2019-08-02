#ifndef YEALINK_RTVC_LIB_USER_AGENT_IMPL_H_
#define YEALINK_RTVC_LIB_USER_AGENT_IMPL_H_

#include "base/memory/weak_ptr.h"
#include "yealink/rtvc/api/user_agent.h"

namespace yealink {

namespace rtvc {

class UserAgentImpl : public UserAgent {
 public:
  UserAgentImpl(Config config);
  ~UserAgentImpl() override;

  std::string workspace_folder() override;

  std::string username() override;
  std::string password() override;
  std::string domain() override;

  void Register() override;
  void UnRegister() override;

  bool registered() override;

 private:
  UserAgent::Config config_;
  base::WeakPtrFactory<UserAgentImpl> weak_factory_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_LIB_USER_AGENT_IMPL_H_
