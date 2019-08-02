#ifndef YEALINK_RTVC_BINDING_VIDEO_MANAGER_BINDING_H_
#define YEALINK_RTVC_BINDING_VIDEO_MANAGER_BINDING_H_

#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/video_manager.h"

namespace yealink {

namespace rtvc {

class VideoManagerBinding : public mate::Wrappable<VideoManagerBinding>,
                            VideoManager {
 public:
  static mate::Handle<VideoManagerBinding> Create(v8::Isolate* isolate) {
    return mate::CreateHandle(isolate, new VideoManagerBinding(isolate));
  }
  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  VideoManagerBinding(v8::Isolate* isolate);
  ~VideoManagerBinding() override;

  std::vector<Device> videoInputDeviceList() override;

  std::vector<Device> screenDeviceList() override;
  std::vector<Device> windowDeviceList() override;

  Device videoInputDevice() override;
  void setVideoInputDevice(Device device) override;

  // secondary video input device is used for content sharing
  // or when video input device is not usable
  Device secondaryVideoInputDevice() override;
  void setSecondaryVideoInputDevice(Device device) override;

  // only 0 | 90 | 180 | 270 degrees are allowed
  void SetRotation(int degree, bool is_secondary = false) override;

  // as we don't expose 'VideoTrack' interface like webrtc
  // video sink can only be setted here for renderer impl
  // currently, we support two video track at one call,
  // and all calls share the video device setting.
  // hence, remote video sink is set in per call instance
  void SetLocalVideoSink(VideoSink* sink) override;
  void SetLocalShareVideoSink(VideoSink* sink) override;

  void SetLocalVideoSinkAdapted(v8::Local<v8::Object> sink);
  void SetLocalShareVideoSinkAdapted(v8::Local<v8::Object> sink);

};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_VIDEO_MANAGER_BINDING_H_
