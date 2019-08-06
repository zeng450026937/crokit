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
  LOG(INFO) << __FUNCTIONW__;
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
    : media_(yealink::Media::CreateInstance(
          Context::GetWorkspaceFolder().AsUTF8Unsafe().c_str())) {
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

  record_devices_.clear();

  for (int i = 0; i < count; i++) {
    Device device;
    device.type = DeviceType::kAudioInput;
    device.deviceId = devices[i].strId.ConstData();
    device.label = devices[i].strName.ConstData();
    record_devices_.emplace_back(device);
  }

  count = media_->EnumAudioPlayoutDevices(devices, kMaxAudioDeviceCout);

  playback_devices_.clear();

  for (int i = 0; i < count; i++) {
    Device device;
    device.type = DeviceType::kAudioOutput;
    device.deviceId = devices[i].strId.ConstData();
    device.label = devices[i].strName.ConstData();
    playback_devices_.emplace_back(device);
  }
}

std::vector<Device> AudioManagerBinding::audioInputDeviceList() {
  LOG(INFO) << __FUNCTIONW__;
  return std::vector<Device>();
}
std::vector<Device> AudioManagerBinding::audioOutputDeviceList() {
  LOG(INFO) << __FUNCTIONW__;
  return std::vector<Device>();
}

Device AudioManagerBinding::audioInputDevice() {
  LOG(INFO) << __FUNCTIONW__;
  return Device();
}
void AudioManagerBinding::SetAudioInputDevice(Device device) {
  LOG(INFO) << __FUNCTIONW__;
}

Device AudioManagerBinding::audioOutputDevice() {
  LOG(INFO) << __FUNCTIONW__;
  return Device();
}
void AudioManagerBinding::SetAudioOutputDevice(Device device) {
  LOG(INFO) << __FUNCTIONW__;
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
