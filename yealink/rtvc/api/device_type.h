#ifndef YEALINK_RTVC_API_DEVICE_TYPE_H_
#define YEALINK_RTVC_API_DEVICE_TYPE_H_

#include <string>

namespace yealink {

namespace rtvc {

enum class DeviceType {
  kAudioInput,
  kAudioOutput,
  kVideoInput,
  kScreen,
  kWindow,
  kImageFile,
};

// TODO:
// add more property to support screen & file device
struct Device {
  std::string deviceId;
  std::string label;
  DeviceType type;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_DEVICE_TYPE_H_
