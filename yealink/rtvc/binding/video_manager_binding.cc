#include "yealink/rtvc/binding/video_manager_binding.h"

#include "base/logging.h"
#include "yealink/libvc/include/media/media_api.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/api/video/video_sink.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/converter.h"

namespace yealink {

namespace rtvc {

namespace {
const int kMaxVideoDeviceCout = 10;
}  // namespace

// static
mate::WrappableBase* VideoManagerBinding::New(mate::Arguments* args) {
  return new VideoManagerBinding(args->isolate(), args->GetThis());
}

// static
void VideoManagerBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "VideoManager"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetMethod("enumerateDevices", &VideoManagerBinding::EnumerateDevices)
      .SetMethod("enumerateScreenDevices",
                 &VideoManagerBinding::EnumerateScreenDevices)
      .SetMethod("enumerateWindowDevices",
                 &VideoManagerBinding::EnumerateWindowDevices)
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
      .SetMethod("setLocalVideoSink", &VideoManagerBinding::SetLocalVideoSink)
      .SetMethod("setLocalShareVideoSink",
                 &VideoManagerBinding::SetLocalShareVideoSink);
}

VideoManagerBinding::VideoManagerBinding(v8::Isolate* isolate,
                                         v8::Local<v8::Object> wrapper)
    : media_(Context::Instance()->GetMedia()),
      local_video_source_(new VideoSourceAdapter()),
      local_share_video_source_(new VideoSourceAdapter()) {
  InitWith(isolate, wrapper);
  media_->SetVideoCameraDeviceRender(local_video_source_.get());
}
VideoManagerBinding::~VideoManagerBinding() = default;

void VideoManagerBinding::EnumerateDevices() {
  MediaDeviceInfo devices[kMaxVideoDeviceCout] = {};
  int count = 0;

  count = media_->EnumVideoCameraDevice(devices, kMaxVideoDeviceCout);

  video_input_device_list_.clear();

  for (int i = 0; i < count; i++) {
    Device device;
    device.type = DeviceType::kVideoInput;
    device.deviceId = devices[i].strId.ConstData();
    device.label = devices[i].strName.ConstData();
    video_input_device_list_.emplace_back(device);
  }
}
void VideoManagerBinding::EnumerateScreenDevices() {}
void VideoManagerBinding::EnumerateWindowDevices() {}

std::vector<Device> VideoManagerBinding::videoInputDeviceList() {
  return video_input_device_list_;
};

std::vector<Device> VideoManagerBinding::screenDeviceList() {
  LOG(INFO) << __FUNCTIONW__;
  return std::vector<Device>();
};
std::vector<Device> VideoManagerBinding::windowDeviceList() {
  LOG(INFO) << __FUNCTIONW__;
  return std::vector<Device>();
};

base::Optional<Device> VideoManagerBinding::videoInputDevice() {
  return video_input_device_;
};
void VideoManagerBinding::setVideoInputDevice(base::Optional<Device> device) {
  if (!device) {
    // isolate()->ThrowException(v8::Exception::Error(
    //     mate::StringToV8(isolate(), "Invalid device argument.")));
    if (media_->SetCamera(nullptr, false))
      video_input_device_ = device;

    return;
  }

  if (!device->deviceId.size()) {
    isolate()->ThrowException(v8::Exception::Error(
        mate::StringToV8(isolate(), "Invalid device id.")));
    return;
  }

  if (media_->SetCamera(device->deviceId.c_str(), false))
    video_input_device_ = device;
};

base::Optional<Device> VideoManagerBinding::secondaryVideoInputDevice() {
  return secondary_video_input_device_;
};
void VideoManagerBinding::setSecondaryVideoInputDevice(
    base::Optional<Device> device) {
  if (!device) {
    isolate()->ThrowException(v8::Exception::Error(
        mate::StringToV8(isolate(), "Invalid device argument.")));
    return;
  }

  if (!device->deviceId.size()) {
    isolate()->ThrowException(v8::Exception::Error(
        mate::StringToV8(isolate(), "Invalid device id.")));
    return;
  }

  // TBD
  secondary_video_input_device_ = device;
};

void VideoManagerBinding::SetRotation(int degree, bool is_secondary) {
  media_->SetCameraOrientation(degree);
};

void VideoManagerBinding::SetLocalVideoSink(mate::PersistentDictionary sink) {
  if (sink.GetHandle()->IsNullOrUndefined()) {
    for (auto it : local_video_sinks_) {
      local_video_source_->RemoveSink(it.second);
      delete it.second;
    }
    local_video_sinks_.clear();
    return;
  }
  // TODO
  // check sink
  int hash = sink.GetHandle()->GetIdentityHash();
  VideoSinkV8* sink_v8 = new VideoSinkV8(sink);
  local_video_source_->AddOrUpdateSink(sink_v8);
  local_video_sinks_.emplace(hash, sink_v8);
};
void VideoManagerBinding::SetLocalShareVideoSink(
    mate::PersistentDictionary sink) {
  int hash = sink.GetHandle()->GetIdentityHash();
  VideoSinkV8* sink_v8 = new VideoSinkV8(sink);
  local_video_source_->AddOrUpdateSink(sink_v8);
  local_share_video_sinks_.emplace(hash, sink_v8);
};

}  // namespace rtvc

}  // namespace yealink
