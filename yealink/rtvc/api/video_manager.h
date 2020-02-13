#ifndef YEALINK_RTVC_API_VIDEO_MANAGER_H_
#define YEALINK_RTVC_API_VIDEO_MANAGER_H_

#include <string>
#include <vector>

#include "yealink/rtvc/api/device_type.h"
#include "yealink/rtvc/api/video/video_sink.h"

namespace rtvc {

struct CameraLimitInfo {
  int width;
  int height;
  int fps;
  CameraLimitInfo() : width(0), height(0), fps(0) {}
};

class VideoManager {
 public:
  static VideoManager* Instance();

  virtual std::vector<Device> videoInputDeviceList() = 0;

  virtual std::vector<Device> screenDeviceList() = 0;
  virtual std::vector<Device> windowDeviceList() = 0;

  virtual Device videoInputDevice() = 0;
  virtual void setVideoInputDevice(Device device) = 0;

  // secondary video input device is used for content sharing
  // or when video input device is not usable
  virtual Device secondaryVideoInputDevice() = 0;
  virtual void setSecondaryVideoInputDevice(Device device) = 0;

  // only 0 | 90 | 180 | 270 degrees are allowed
  virtual void SetRotation(int degree, bool is_secondary = false) = 0;

  // as we don't expose 'VideoTrack' interface like webrtc
  // video sink can only be setted here for renderer impl
  // currently, we support two video track at one call,
  // and all calls share the video device setting.
  // hence, remote video sink is set in per call instance
  virtual void SetLocalVideoSink(VideoSink* sink) = 0;
  virtual void SetLocalShareVideoSink(VideoSink* sink) = 0;

 protected:
  virtual ~VideoManager() {}
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_API_VIDEO_MANAGER_H_
