#ifndef YEALINK_RTVC_API_USER_AGENT_H_
#define YEALINK_RTVC_API_USER_AGENT_H_

#include <memory>
#include <string>

#include "base/optional.h"

namespace rtvc {

class UserAgent {
 public:
  struct Config {
    base::Optional<std::string> workspace_folder;
    std::string username;
    std::string password;
    std::string ha1;
    std::string domain;
    std::string display_name;
    std::string useragent;
    std::string client_info;
    std::string sitename;
    int64_t tls_port = 5061;
    int64_t tcp_port = 5060;
    int64_t udp_port = 5060;
    bool ipv4_only = false;
    bool ipv6_only = false;
    base::Optional<std::string> proxy_server;
    int64_t proxy_port = 0;
  };

  virtual ~UserAgent() = default;

  static std::unique_ptr<UserAgent> Create(Config config);

  virtual std::string workspace_folder() = 0;

  virtual std::string username() = 0;
  virtual std::string password() = 0;
  virtual std::string ha1() = 0;
  virtual std::string domain() = 0;
  virtual std::string proxyServer() = 0;
  virtual int64_t proxyPort() = 0;

  virtual void Register() = 0;
  virtual void UnRegister() = 0;

  virtual bool registered() = 0;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_API_USER_AGENT_H_
