#include "ytms_process.h"

namespace rtvc {

ProcessObserver::ProcessObserver() {
  biz_code_ = 0;
  error_code_ = 0;
  msg_ = "";
}

ProcessObserver::~ProcessObserver() {}

int ProcessObserver::bizCode() {
  return biz_code_;
}

int ProcessObserver::errorCode() {
  return error_code_;
}

void ProcessObserver::SetBizCode(int code) {
  LOG(INFO) << __FUNCTIONW__;

  biz_code_ = code;
}

void ProcessObserver::SetErrorInfo(int code, const char* msg) {
  LOG(INFO) << __FUNCTIONW__;

  error_code_ = code;
  msg_ = msg;
}

}  // namespace rtvc
