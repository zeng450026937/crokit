#ifndef YEALINK_RTVC_API_CONFERENCE_RECORD_H_
#define YEALINK_RTVC_API_CONFERENCE_RECORD_H_

#include <string>

#include "yealink/rtvc/api/macros.h"

namespace rtvc {

enum class RecordStatusType {
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

struct RecordUserInfo {
  RecordStatusType record_status;
  int64_t record_last_stop_duration;
  int64_t record_last_start_time;
};

struct RecordUsers {
  int32_t biz_code;
  RecordUserInfo user;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_API_CONFERENCE_RECORD_H_
