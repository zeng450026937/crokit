#ifndef YEALINK_RTVC_BINDING_VIDEO_MANAGER_BINDING_H_
#define YEALINK_RTVC_BINDING_VIDEO_MANAGER_BINDING_H_

#include <map>
#include <memory>

#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/video_manager.h"
#include "yealink/rtvc/binding/video_sink_v8.h"
#include "yealink/rtvc/binding/video_source_adapter.h"
#include "base/macros.h"

namespace yealink {

class Media;

namespace rtvc {

class VideoManagerBinding : public mate::Wrappable<VideoManagerBinding> {
 public:
  static mate::Handle<VideoManagerBinding> Create(v8::Isolate* isolate) {
    return mate::CreateHandle(isolate, new VideoManagerBinding(isolate));
  }
  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  VideoManagerBinding(v8::Isolate* isolate);
  ~VideoManagerBinding() override;

  void EnumerateDevices();
  void EnumerateScreenDevices();
  void EnumerateWindowDevices();

  std::vector<Device> videoInputDeviceList();

  std::vector<Device> screenDeviceList();
  std::vector<Device> windowDeviceList();

  base::Optional<Device> videoInputDevice();
  void setVideoInputDevice(base::Optional<Device> device);

  base::Optional<Device> secondaryVideoInputDevice();
  void setSecondaryVideoInputDevice(base::Optional<Device> device);

  void SetRotation(int degree, bool is_secondary = false);

  void SetLocalVideoSink(mate::PersistentDictionary sink);
  void SetLocalShareVideoSink(mate::PersistentDictionary sink);

 private:
  yealink::Media* media_;

  std::vector<Device> video_input_device_list_;
  base::Optional<Device> video_input_device_;
  base::Optional<Device> secondary_video_input_device_;

  std::unique_ptr<VideoSourceAdapter> local_video_source_;
  std::unique_ptr<VideoSourceAdapter> local_share_video_source_;

  std::map<int, VideoSinkV8*> local_video_sinks_;
  std::map<int, VideoSinkV8*> local_share_video_sinks_;

  DISALLOW_COPY_AND_ASSIGN(VideoManagerBinding);
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_VIDEO_MANAGER_BINDING_H_
