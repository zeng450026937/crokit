#ifndef YEALINK_RTVC_API_USER_AGENT_H_
#define YEALINK_RTVC_API_USER_AGENT_H_

#include <string>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_refptr.h"
#include "base/optional.h"

namespace yealink {

namespace api {

class UserAgent {
 public:
  struct Config {
    base::Optional<std::string> workspace_folder;
    std::string username;
    std::string password;
    std::string domain;
  };

  static scoped_refptr<UserAgent> Create(UserAgent::Config config);

  virtual std::string workspace_folder() = 0;

  virtual std::string username() = 0;
  virtual std::string password() = 0;
  virtual std::string domain() = 0;

  virtual void Register() = 0;
  virtual void UnRegister() = 0;

  virtual bool registered() = 0;

  virtual void Call(std::string target) = 0;
  virtual void Send(std::string target, std::string msg) = 0;

 protected:
  virtual ~UserAgent() = default;
};

}  // namespace api

}  // namespace yealink

#endif  // YEALINK_RTVC_API_USER_AGENT_H_
