#ifndef YEALINK_RTVC_API_USER_AGENT_H_
#define YEALINK_RTVC_API_USER_AGENT_H_

#include <string>

namespace yealink {

namespace api {

class UserAgentInterface {
 public:
  virtual std::string wockspace_folder() = 0;

 protected:
  virtual ~UserAgentInterface() = default;
};

}  // namespace api

}  // namespace yealink

#endif  // YEALINK_RTVC_API_USER_AGENT_H_
