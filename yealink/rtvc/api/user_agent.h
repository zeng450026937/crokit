#ifndef YEALINK_RTVC_API_USER_AGENT_H_
#define YEALINK_RTVC_API_USER_AGENT_H_

#include <string>
#include <memory>

#include "base/optional.h"

namespace yealink {

namespace rtvc {

class UserAgent {
 public:
  struct Config {
    base::Optional<std::string> workspace_folder;
    std::string username;
    std::string password;
    std::string ha1;
    std::string domain;
  };

  virtual ~UserAgent() = default;

  static std::unique_ptr<UserAgent> Create(Config config);

  virtual std::string workspace_folder() = 0;

  virtual std::string username() = 0;
  virtual std::string password() = 0;
  virtual std::string domain() = 0;

  virtual void Register() = 0;
  virtual void UnRegister() = 0;

  virtual bool registered() = 0;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_USER_AGENT_H_
