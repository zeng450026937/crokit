#include "yealink/rtvc/lib/user_agent_impl.h"

#include "base/logging.h"

namespace yealink {

namespace rtvc {

UserAgentImpl::UserAgentImpl(UserAgent::Config config)
    : config_(std::move(config)), weak_factory_(this) {}
UserAgentImpl::~UserAgentImpl() {
  LOG(INFO) << __FUNCTIONW__;
}

std::string UserAgentImpl::workspace_folder() {
  LOG(INFO) << __FUNCTIONW__;
  return config_.workspace_folder.value_or("");
}

std::string UserAgentImpl::username() {
  LOG(INFO) << __FUNCTIONW__;
  return config_.username;
}
std::string UserAgentImpl::password() {
  LOG(INFO) << __FUNCTIONW__;
  return config_.password;
}
std::string UserAgentImpl::domain() {
  LOG(INFO) << __FUNCTIONW__;
  return config_.domain;
}

void UserAgentImpl::Register() {
  LOG(INFO) << __FUNCTIONW__;
}
void UserAgentImpl::UnRegister() {
  LOG(INFO) << __FUNCTIONW__;
}

bool UserAgentImpl::registered() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}

// static
std::unique_ptr<UserAgent> UserAgent::Create(UserAgent::Config config) {
  return std::unique_ptr<UserAgent>(new UserAgentImpl(config));
}
}  // namespace rtvc

}  // namespace yealink
