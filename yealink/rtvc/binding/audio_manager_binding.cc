#include "yealink/rtvc/binding/audio_manager_binding.h"

#include "base/logging.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/converter.h"

namespace yealink {

namespace rtvc {

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
      .SetMethod("audioInputDeviceList", &AudioManagerBinding::audioInputDeviceList)
      .SetMethod("audioOutputDeviceList", &AudioManagerBinding::audioOutputDeviceList)
      .SetProperty("audioInputDevice", &AudioManagerBinding::audioInputDevice,
                   &AudioManagerBinding::SetAudioInputDevice)
      .SetProperty("audioOutputDevice", &AudioManagerBinding::audioOutputDevice,
                   &AudioManagerBinding::SetAudioOutputDevice)
      .SetMethod("playTone", &AudioManagerBinding::PlayTone)
      .SetMethod("startPlayFile", &AudioManagerBinding::StartPlayFile)
      .SetMethod("stopPlayFile", &AudioManagerBinding::StopPlayFile);
}

AudioManagerBinding::AudioManagerBinding(v8::Isolate* isolate) {
  Init(isolate);
}
AudioManagerBinding::~AudioManagerBinding() = default;

int AudioManagerBinding::volume() {
  LOG(INFO) << __FUNCTIONW__;
  return 0;
}
void AudioManagerBinding::SetVolume(int volume) {
  LOG(INFO) << __FUNCTIONW__;
}

bool AudioManagerBinding::mute() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
void AudioManagerBinding::SetMute(bool mute) {
  LOG(INFO) << __FUNCTIONW__;
}

bool AudioManagerBinding::ans() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
void AudioManagerBinding::SetANS(bool enable) {
  LOG(INFO) << __FUNCTIONW__;
}

bool AudioManagerBinding::aec() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
void AudioManagerBinding::SetAEC(bool enable) {
  LOG(INFO) << __FUNCTIONW__;
}

bool AudioManagerBinding::agc() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
void AudioManagerBinding::SetAGC(bool enable) {
  LOG(INFO) << __FUNCTIONW__;
}

bool AudioManagerBinding::recording() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
void AudioManagerBinding::SetRecording(bool enable) {
  LOG(INFO) << __FUNCTIONW__;
}

bool AudioManagerBinding::playback() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
void AudioManagerBinding::SetPlayback(bool enable) {
  LOG(INFO) << __FUNCTIONW__;
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
  LOG(INFO) << __FUNCTIONW__;
}
void AudioManagerBinding::StartPlayFile(std::string path) {
  LOG(INFO) << __FUNCTIONW__;
}
void AudioManagerBinding::StopPlayFile() {
  LOG(INFO) << __FUNCTIONW__;
}

}  // namespace rtvc

}  // namespace yealink
