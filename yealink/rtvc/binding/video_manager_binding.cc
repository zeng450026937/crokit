#include "yealink/rtvc/binding/video_manager_binding.h"

#include "base/logging.h"
#include "yealink/libvc/include/media/media_api.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/api/video/video_sink.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/converter.h"

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
      .SetMethod("acquiring", &VideoManagerBinding::acquiring)
      .SetMethod("setLocalVideoSink", &VideoManagerBinding::SetLocalVideoSink)
      .SetMethod("addLocalVideoSink", &VideoManagerBinding::AddLocalVideoSink)
      .SetMethod("removeLocalVideoSink",
                 &VideoManagerBinding::RemoveLocalVideoSink)
      .SetMethod("setLocalShareVideoSink",
                 &VideoManagerBinding::SetLocalShareVideoSink)
      .SetMethod("addLocalShareVideoSink",
                 &VideoManagerBinding::AddLocalShareVideoSink)
      .SetMethod("removeLocalShareVideoSink",
                 &VideoManagerBinding::RemoveLocalShareVideoSink)
      .SetMethod("setLocalVideoSource",
                 &VideoManagerBinding::SetLocalVideoSource);
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

  for (auto it : local_video_source_->sinks()) {
    RemoveLocalVideoSink(static_cast<VideoSinkV8*>(it)->GetHandle());
  }
  local_video_source_->RemoveAllSinks();

  for (auto it : local_share_video_source_->sinks()) {
    RemoveLocalShareVideoSink(static_cast<VideoSinkV8*>(it)->GetHandle());
  }
  local_share_video_source_->RemoveAllSinks();
}

void VideoManagerBinding::EnumerateDevices() {
  yealink::MediaDeviceInfo devices[kMaxVideoDeviceCout] = {};
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
  yealink::CaptureInfo cam;

  if (!device) {
    // isolate()->ThrowException(v8::Exception::Error(
    //     mate::StringToV8(isolate(), "Invalid device argument.")));
    media_->SetCamera(cam);
    video_input_device_ = device;
    return;
  }

  if (!device->deviceId.size()) {
    isolate()->ThrowException(v8::Exception::Error(
        mate::StringToV8(isolate(), "Invalid device id.")));
    return;
  }

  video_input_device_ = device;

  cam.strId = device->deviceId.c_str();

  if (device->fps > 0)
    cam.nMaxFPS = device->fps;
  else
    cam.nMaxFPS = 30;

  if (device->height > 0 && device->width > 0) {
    cam.nMaxWidth = device->width;
    cam.nMaxHeight = device->height;
  } else {
    cam.nMaxWidth = 1920;
    cam.nMaxHeight = 1080;
  }

  if (acquiring_stream_) {
    switch (device->type) {
      case DeviceType::kImageFile:
        cam.fmtDevice = yealink::CaptureDeviceFormat::CD_FILE_JPEG_24;
        media_->SetCamera(cam);
        break;
      case DeviceType::kVideoInput:
        cam.fmtDevice = yealink::CaptureDeviceFormat::CD_WEBCAM_AUTO;
        media_->SetCamera(cam);
      default:
        break;
    }
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

bool VideoManagerBinding::AcquireStream(mate::Arguments* args) {
  bool ret = false;

  if (acquiring_stream_)
    return ret;

  yealink::CaptureInfo cam;
  CameraLimitInfo limit;

  acquiring_stream_ = true;
  cam.strId = video_input_device_->deviceId.c_str();

  if (args->Length() == 1)
    args->GetNext(&limit);

  if (limit.fps > 0)
    cam.nMaxFPS = limit.fps;
  else
    cam.nMaxFPS = 30;

  if (limit.height > 0 && limit.width > 0) {
    cam.nMaxWidth = limit.width;
    cam.nMaxHeight = limit.height;
  } else {
    cam.nMaxWidth = 1920;
    cam.nMaxHeight = 1080;
  }

  if (video_input_device_) {
    switch (video_input_device_->type) {
      case DeviceType::kImageFile:
        cam.fmtDevice = yealink::CaptureDeviceFormat::CD_FILE_JPEG_24;
        ret = media_->SetCamera(cam);
        break;
      case DeviceType::kVideoInput:
      default:
        cam.fmtDevice = yealink::CaptureDeviceFormat::CD_WEBCAM_AUTO;
        ret = media_->SetCamera(cam);
        break;
    }
  }

  return ret;
}
void VideoManagerBinding::ReleaseStream() {
  if (!acquiring_stream_)
    return;

  acquiring_stream_ = false;
  yealink::CaptureInfo cam;

  media_->SetCamera(cam);
}
bool VideoManagerBinding::acquiring() {
  return acquiring_stream_;
}

void VideoManagerBinding::SetLocalVideoSink(mate::Arguments* args) {
  mate::PersistentDictionary sink;
  if (!args->GetNext(&sink)) {
    for (auto it : local_video_source_->sinks()) {
      RemoveLocalVideoSink(static_cast<VideoSinkV8*>(it)->GetHandle());
    }
    local_video_source_->RemoveAllSinks();
    return;
  }

  AddLocalVideoSink(sink);
};

void VideoManagerBinding::AddLocalVideoSink(mate::PersistentDictionary sink) {
  intptr_t hash;
  VideoSinkV8* sink_v8;

  if (!sink.GetHidden("hash", &hash)) {
    sink_v8 = new VideoSinkV8(sink);
    sink.SetHidden("hash", reinterpret_cast<intptr_t>(sink_v8));
  } else {
    sink_v8 = reinterpret_cast<VideoSinkV8*>(hash);
  }

  local_video_source_->AddOrUpdateSink(sink_v8);
}

void VideoManagerBinding::RemoveLocalVideoSink(
    mate::PersistentDictionary sink) {
  intptr_t hash;
  VideoSinkV8* sink_v8;

  if (!sink.GetHidden("hash", &hash))
    return;

  sink_v8 = reinterpret_cast<VideoSinkV8*>(hash);
  sink_v8->GetHandle().DeletePrivate("hash");
  local_video_source_->RemoveSink(sink_v8);

  delete sink_v8;
  sink_v8 = nullptr;
}

void VideoManagerBinding::SetLocalShareVideoSink(mate::Arguments* args) {
  mate::PersistentDictionary sink;
  if (!args->GetNext(&sink)) {
    for (auto it : local_share_video_source_->sinks()) {
      RemoveLocalShareVideoSink(static_cast<VideoSinkV8*>(it)->GetHandle());
    }
    local_share_video_source_->RemoveAllSinks();
    return;
  }

  AddLocalShareVideoSink(sink);
};

void VideoManagerBinding::AddLocalShareVideoSink(
    mate::PersistentDictionary sink) {
  intptr_t hash;
  VideoSinkV8* sink_v8;

  if (!sink.GetHidden("hash", &hash)) {
    sink_v8 = new VideoSinkV8(sink);
    sink.SetHidden("hash", reinterpret_cast<intptr_t>(sink_v8));
  } else {
    sink_v8 = reinterpret_cast<VideoSinkV8*>(hash);
  }

  local_share_video_source_->AddOrUpdateSink(sink_v8);
};

void VideoManagerBinding::RemoveLocalShareVideoSink(
    mate::PersistentDictionary sink) {
  intptr_t hash;
  VideoSinkV8* sink_v8;

  if (!sink.GetHidden("hash", &hash))
    return;

  sink_v8 = reinterpret_cast<VideoSinkV8*>(hash);
  sink_v8->GetHandle().DeletePrivate("hash");
  local_share_video_source_->RemoveSink(sink_v8);

  delete sink_v8;
  sink_v8 = nullptr;
}

void VideoManagerBinding::SetLocalVideoSource(mate::Arguments* args) {
  mate::PersistentDictionary source;
  if (!args->GetNext(&source)) {
    local_video_source_v8_.reset();
    return;
  }
  local_video_source_v8_.reset(new VideoSourceV8(source));
}

}  // namespace rtvc
