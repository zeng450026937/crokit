#ifndef YEALINK_RTVC_API_TIME_UTILS_H_
#define YEALINK_RTVC_API_TIME_UTILS_H_

#include <stdint.h>

namespace rtvc {

static const int64_t kNumMillisecsPerSec = INT64_C(1000);
static const int64_t kNumMicrosecsPerSec = INT64_C(1000000);
static const int64_t kNumNanosecsPerSec = INT64_C(1000000000);

static const int64_t kNumMicrosecsPerMillisec =
    kNumMicrosecsPerSec / kNumMillisecsPerSec;
static const int64_t kNumNanosecsPerMillisec =
    kNumNanosecsPerSec / kNumMillisecsPerSec;
static const int64_t kNumNanosecsPerMicrosec =
    kNumNanosecsPerSec / kNumMicrosecsPerSec;

}  // namespace rtvc

#endif  // YEALINK_RTVC_API_TIME_UTILS_H_
