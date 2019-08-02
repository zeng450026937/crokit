#ifndef YEALINK_RTVC_LIB_VIDEO_MANAGER_IMPL_H_
#define YEALINK_RTVC_LIB_VIDEO_MANAGER_IMPL_H_

#include "yealink/rtvc/api/video_manager.h"

namespace yealink {

namespace rtvc {

class VideoManagerImpl : public VideoManager {
 public:
  std::vector<Device> videoInputDeviceList() override;

  std::vector<Device> screenDeviceList() override;
  std::vector<Device> windowDeviceList() override;

  Device videoInputDevice() override;
  void setVideoInputDevice(Device device) override;

  Device secondaryVideoInputDevice() override;
  void setSecondaryVideoInputDevice(Device device) override;

  void SetRotation(int degree, bool is_secondary = false) override;

  void SetLocalVideoSink(VideoSink* sink) override;
  void SetLocalShareVideoSink(VideoSink* sink) override;

 protected:
  friend class VideoManager;

  VideoManagerImpl();
  ~VideoManagerImpl() override;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_LIB_VIDEO_MANAGER_IMPL_H_
