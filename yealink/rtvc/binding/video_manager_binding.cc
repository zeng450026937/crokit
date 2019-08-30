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
      .SetMethod("videoInputDeviceList",
                 &VideoManagerBinding::videoInputDeviceList)
      .SetProperty("videoInputDevice", &VideoManagerBinding::videoInputDevice,
                   &VideoManagerBinding::setVideoInputDevice)
      .SetProperty("secondaryVideoInputDevice",
                   &VideoManagerBinding::secondaryVideoInputDevice,
                   &VideoManagerBinding::setSecondaryVideoInputDevice)
      .SetMethod("setRotation", &VideoManagerBinding::SetRotation)
      .SetMethod("acquireStream", &VideoManagerBinding::AcquireStream)
      .SetMethod("releaseStream", &VideoManagerBinding::ReleaseStream)
      .SetMethod("setLocalVideoSink", &VideoManagerBinding::SetLocalVideoSink)
      .SetMethod("removeLocalVideoSink",
                 &VideoManagerBinding::RemoveLocalVideoSink)
      .SetMethod("setLocalShareVideoSink",
                 &VideoManagerBinding::SetLocalShareVideoSink)
      .SetMethod("removeLocalShareVideoSink",
                 &VideoManagerBinding::RemoveLocalShareVideoSink);
}

VideoManagerBinding::VideoManagerBinding(v8::Isolate* isolate,
                                         v8::Local<v8::Object> wrapper)
    : media_(Context::Instance()->GetMedia()),
      local_video_source_(new VideoSourceAdapter()),
      local_share_video_source_(new VideoSourceAdapter()) {
  InitWith(isolate, wrapper);
  media_->SetVideoCameraDeviceRender(local_video_source_.get());
}
VideoManagerBinding::~VideoManagerBinding() {
  media_->SetVideoCameraDeviceRender(nullptr);
}

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

std::vector<Device> VideoManagerBinding::videoInputDeviceList() {
  return video_input_device_list_;
};

base::Optional<Device> VideoManagerBinding::videoInputDevice() {
  return video_input_device_;
};
void VideoManagerBinding::setVideoInputDevice(base::Optional<Device> device) {
  if (!device) {
    // isolate()->ThrowException(v8::Exception::Error(
    //     mate::StringToV8(isolate(), "Invalid device argument.")));
    media_->SetCamera(nullptr, false);
    video_input_device_ = device;
    return;
  }

  if (!device->deviceId.size()) {
    isolate()->ThrowException(v8::Exception::Error(
        mate::StringToV8(isolate(), "Invalid device id.")));
    return;
  }

  video_input_device_ = device;

  if (acquiring_stream_) {
    media_->SetCamera(device->deviceId.c_str(), false);
  }
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

void VideoManagerBinding::SetRotation(int64_t degree, bool is_secondary) {
  media_->SetCameraOrientation(degree);
};

void VideoManagerBinding::AcquireStream() {
  acquiring_stream_ = true;
  if (video_input_device_) {
    media_->SetCamera(video_input_device_->deviceId.c_str(), false);
  }
}
void VideoManagerBinding::ReleaseStream() {
  acquiring_stream_ = false;
  media_->SetCamera(nullptr, false);
}

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

void VideoManagerBinding::RemoveLocalVideoSink(mate::Dictionary sink) {
  if (sink.GetHandle()->IsNullOrUndefined())
    return;

  int hash = sink.GetHandle()->GetIdentityHash();
  auto it = local_video_sinks_.find(hash);
  if (it != local_video_sinks_.end()) {
    local_video_source_->RemoveSink(it->second);
    delete it->second;
    local_video_sinks_.erase(it);
  }
}

void VideoManagerBinding::SetLocalShareVideoSink(
    mate::PersistentDictionary sink) {
  if (sink.GetHandle()->IsNullOrUndefined()) {
    for (auto it : local_share_video_sinks_) {
      local_share_video_source_->RemoveSink(it.second);
      delete it.second;
    }
    local_share_video_sinks_.clear();
    return;
  }
  int hash = sink.GetHandle()->GetIdentityHash();
  VideoSinkV8* sink_v8 = new VideoSinkV8(sink);
  local_share_video_source_->AddOrUpdateSink(sink_v8);
  local_share_video_sinks_.emplace(hash, sink_v8);
};

void VideoManagerBinding::RemoveLocalShareVideoSink(mate::Dictionary sink) {
  if (sink.GetHandle()->IsNullOrUndefined())
    return;

  int hash = sink.GetHandle()->GetIdentityHash();
  auto it = local_share_video_sinks_.find(hash);
  if (it != local_share_video_sinks_.end()) {
    local_share_video_source_->RemoveSink(it->second);
    delete it->second;
    local_share_video_sinks_.erase(it);
  }
}

}  // namespace rtvc

}  // namespace yealink
