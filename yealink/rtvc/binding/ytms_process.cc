#include "ytms_process.h"

namespace yealink {

namespace rtvc {

ProcessObserver::ProcessObserver() {
  biz_code_ = 0;
}

ProcessObserver::~ProcessObserver() {}

int ProcessObserver::bizCode()
{
  return biz_code_;
}

int ProcessObserver::errorCode()
{
  return error_code_;
}

void ProcessObserver::SetBizCode(int code)
{
  LOG(INFO) << __FUNCTIONW__;
  printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");

  biz_code_ = code;
}

void ProcessObserver::SetErrorInfo(int code, const char* msg)
{
  LOG(INFO) << __FUNCTIONW__;
  printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
  error_code_ = code;
  msg = msg;
}

}
}
