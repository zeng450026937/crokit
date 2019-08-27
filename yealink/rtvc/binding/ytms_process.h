#ifndef YEALINK_RTVC_BINDING_YTMS_PROCESS_H_
#define YEALINK_RTVC_BINDING_YTMS_PROCESS_H_

#include <string>

#include "yealink/libvc/include/ytms/ytms_agent_api.h"

#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/ytms_info.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/promise.h"

namespace yealink {

namespace rtvc {

class ProcessObserver : public YTMSProcess {
 public:
  ProcessObserver();
  ~ProcessObserver();

  int bizCode();
  int errorCode();

 protected:
  void SetBizCode(int code) override;
  void SetErrorInfo(int code, const char* msg) override;

 private:
  int biz_code_;
  int error_code_;
  std::string msg_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_YTMS_PROCESS_H_
