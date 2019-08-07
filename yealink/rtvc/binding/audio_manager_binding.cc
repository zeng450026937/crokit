#include "yealink/rtvc/binding/audio_manager_binding.h"

#include "base/logging.h"
#include "yealink/libvc/include/media/media_api.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/converter.h"

namespace yealink {

namespace rtvc {

namespace {
const int kMaxAudioDeviceCout = 10;
}  // namespace

// static
void AudioManagerBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "AudioManager"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("volume", &AudioManagerBinding::volume,
                   &AudioManagerBinding::SetVolume)
      .SetProperty("mute", &AudioManagerBinding::mute,
                   &AudioManagerBinding::SetMute)
      .SetProperty("ans", &AudioManagerBinding::ans,
                   &AudioManagerBinding::SetANS)
      .SetProperty("aec", &AudioManagerBinding::aec,
                   &AudioManagerBinding::SetAEC)
      .SetProperty("agc", &AudioManagerBinding::agc,
                   &AudioManagerBinding::SetAGC)
      .SetProperty("recording", &AudioManagerBinding::recording,
                   &AudioManagerBinding::SetRecording)
      .SetProperty("playback", &AudioManagerBinding::playback,
                   &AudioManagerBinding::SetPlayback)
      .SetMethod("enumerateDevices", &AudioManagerBinding::EnumerateDevices)
      .SetMethod("audioInputDeviceList",
                 &AudioManagerBinding::audioInputDeviceList)
      .SetMethod("audioOutputDeviceList",
                 &AudioManagerBinding::audioOutputDeviceList)
      .SetProperty("audioInputDevice", &AudioManagerBinding::audioInputDevice,
                   &AudioManagerBinding::SetAudioInputDevice)
      .SetProperty("audioOutputDevice", &AudioManagerBinding::audioOutputDevice,
                   &AudioManagerBinding::SetAudioOutputDevice)
      .SetMethod("playTone", &AudioManagerBinding::PlayTone)
      .SetMethod("startPlayFile", &AudioManagerBinding::StartPlayFile)
      .SetMethod("stopPlayFile", &AudioManagerBinding::StopPlayFile);
}

AudioManagerBinding::AudioManagerBinding(v8::Isolate* isolate)
    : media_(Context::Instance()->GetMedia()) {
  Init(isolate);
}
AudioManagerBinding::~AudioManagerBinding() = default;

int AudioManagerBinding::volume() {
  return media_->GetVolume();
}
void AudioManagerBinding::SetVolume(int volume) {
  media_->SetVolume(volume);
}

bool AudioManagerBinding::mute() {
  return media_->IsMute();
}
void AudioManagerBinding::SetMute(bool mute) {
  media_->Mute(mute);
}

bool AudioManagerBinding::ans() {
  return media_->GetEnableANS();
}
void AudioManagerBinding::SetANS(bool enable) {
  media_->SetEnableANS(enable);
}

bool AudioManagerBinding::aec() {
  return false;
}
void AudioManagerBinding::SetAEC(bool enable) {
  LOG(INFO) << __FUNCTIONW__ << " No Impl";
}

bool AudioManagerBinding::agc() {
  return media_->GetEnableAGC();
}
void AudioManagerBinding::SetAGC(bool enable) {
  media_->SetEnableAGC(enable);
}

bool AudioManagerBinding::recording() {
  return media_->IsAudioRecording();
}
void AudioManagerBinding::SetRecording(bool enable) {
  if (enable)
    media_->StartAudioRecord();
  else
    media_->StopAudioRecord();
}

bool AudioManagerBinding::playback() {
  return media_->IsAudioPlaying();
}
void AudioManagerBinding::SetPlayback(bool enable) {
  if (enable)
    media_->StartAudioPlayout();
  else
    media_->StartAudioPlayout();
}

void AudioManagerBinding::EnumerateDevices() {
  MediaDeviceInfo devices[kMaxAudioDeviceCout] = {};
  int count = 0;

  count = media_->EnumAudioRecordDevices(devices, kMaxAudioDeviceCout);

  audio_input_device_list_.clear();

  for (int i = 0; i < count; i++) {
    Device device;
    device.type = DeviceType::kAudioInput;
    device.deviceId = devices[i].strId.ConstData();
    device.label = devices[i].strName.ConstData();
    audio_input_device_list_.emplace_back(device);
  }

  count = media_->EnumAudioPlayoutDevices(devices, kMaxAudioDeviceCout);

  audio_output_device_list_.clear();

  for (int i = 0; i < count; i++) {
    Device device;
    device.type = DeviceType::kAudioOutput;
    device.deviceId = devices[i].strId.ConstData();
    device.label = devices[i].strName.ConstData();
    audio_output_device_list_.emplace_back(device);
  }
}

std::vector<Device> AudioManagerBinding::audioInputDeviceList() {
  return audio_input_device_list_;
}
std::vector<Device> AudioManagerBinding::audioOutputDeviceList() {
  return audio_output_device_list_;
}

base::Optional<Device> AudioManagerBinding::audioInputDevice() {
  return audio_input_device_;
}
void AudioManagerBinding::SetAudioInputDevice(base::Optional<Device> device) {
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

  if (media_->SetAudioRecordDevice(device->deviceId.c_str()))
    audio_input_device_ = device;
}

base::Optional<Device> AudioManagerBinding::audioOutputDevice() {
  return audio_output_device_;
}
void AudioManagerBinding::SetAudioOutputDevice(base::Optional<Device> device) {
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

  if (media_->SetAudioRecordDevice(device->deviceId.c_str()))
    audio_output_device_ = device;
}

// TODO:
// move these(blow) api out of this class
void AudioManagerBinding::PlayTone(std::string tone) {
  for (char s : tone) {
    media_->PlayTone(s);
  }
}
void AudioManagerBinding::StartPlayFile(std::string path) {
  media_->PlayRingFile(path.c_str(), false);
}
void AudioManagerBinding::StopPlayFile() {
  media_->StopPlayRing();
}

}  // namespace rtvc

}  // namespace yealink
