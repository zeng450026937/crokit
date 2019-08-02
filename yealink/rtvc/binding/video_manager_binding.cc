#include "yealink/rtvc/binding/video_manager_binding.h"

#include "base/logging.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/api/video/video_sink.h"
#include "yealink/rtvc/binding/converter.h"

namespace yealink {

namespace rtvc {

// static
void VideoManagerBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  LOG(INFO) << __FUNCTIONW__;
  prototype->SetClassName(mate::StringToV8(isolate, "AudioManager"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetMethod("videoInputDeviceList",
                 &VideoManagerBinding::videoInputDeviceList)
      .SetMethod("screenDeviceList", &VideoManagerBinding::screenDeviceList)
      .SetMethod("windowDeviceList", &VideoManagerBinding::windowDeviceList)
      .SetProperty("videoInputDevice", &VideoManagerBinding::videoInputDevice,
                   &VideoManagerBinding::setVideoInputDevice)
      .SetProperty("secondaryVideoInputDevice",
                   &VideoManagerBinding::secondaryVideoInputDevice,
                   &VideoManagerBinding::setSecondaryVideoInputDevice)
      .SetMethod("setRotation", &VideoManagerBinding::SetRotation)
      .SetMethod("setLocalVideoSink", &VideoManagerBinding::SetLocalVideoSinkAdapted)
      .SetMethod("setLocalShareVideoSink",
                 &VideoManagerBinding::SetLocalShareVideoSinkAdapted);
}

VideoManagerBinding::VideoManagerBinding(v8::Isolate* isolate) {
  Init(isolate);
}
VideoManagerBinding::~VideoManagerBinding() = default;

std::vector<Device> VideoManagerBinding::videoInputDeviceList() {
  LOG(INFO) << __FUNCTIONW__;
  return std::vector<Device>();
};

std::vector<Device> VideoManagerBinding::screenDeviceList() {
  LOG(INFO) << __FUNCTIONW__;
  return std::vector<Device>();
};
std::vector<Device> VideoManagerBinding::windowDeviceList() {
  LOG(INFO) << __FUNCTIONW__;
  return std::vector<Device>();
};

Device VideoManagerBinding::videoInputDevice() {
  LOG(INFO) << __FUNCTIONW__;
  return Device();
};
void VideoManagerBinding::setVideoInputDevice(Device device) {
  LOG(INFO) << __FUNCTIONW__;
};

Device VideoManagerBinding::secondaryVideoInputDevice() {
  LOG(INFO) << __FUNCTIONW__;
  return Device();
};
void VideoManagerBinding::setSecondaryVideoInputDevice(Device device) {
  LOG(INFO) << __FUNCTIONW__;
};

void VideoManagerBinding::SetRotation(int degree, bool is_secondary) {
  LOG(INFO) << __FUNCTIONW__;
};

void VideoManagerBinding::SetLocalVideoSink(VideoSink* sink) {
  LOG(INFO) << __FUNCTIONW__;
};
void VideoManagerBinding::SetLocalShareVideoSink(VideoSink* sink) {
  LOG(INFO) << __FUNCTIONW__;
};
void VideoManagerBinding::SetLocalVideoSinkAdapted(v8::Local<v8::Object> sink) {
  LOG(INFO) << __FUNCTIONW__ << " sink hash: " << sink->GetIdentityHash();
};
void VideoManagerBinding::SetLocalShareVideoSinkAdapted(v8::Local<v8::Object> sink) {
  LOG(INFO) << __FUNCTIONW__;
};

}  // namespace rtvc

}  // namespace yealink
