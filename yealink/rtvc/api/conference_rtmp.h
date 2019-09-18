#ifndef YEALINK_RTVC_API_CONFERENCE_RTMP_H_
#define YEALINK_RTVC_API_CONFERENCE_RTMP_H_

#include <string>

#include "yealink/rtvc/api/macros.h"

namespace yealink {
namespace rtvc {

enum class RtmpStatusType {
  kInvalid,
  kStarting,
  kStart,
  kStopping,
  kStop,
  kPausing,
  kPause,
  kResuming,
  kResume,
};

struct RtmpUserInfo {
  std::string entity;
  bool is_default;
  RtmpStatusType rtmp_status;
  int64_t rtmp_last_stop_duration;
  int64_t rtmp_last_start_time;
};

struct RtmpInfo {
  bool enable;
  std::vector<RtmpUserInfo> users;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_CONFERENCE_RTMP_H_
