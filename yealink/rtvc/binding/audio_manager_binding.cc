#include "yealink/rtvc/binding/audio_manager_binding.h"

#include "base/logging.h"
#include "yealink/libvc/include/media/media_api.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/converter.h"

namespace rtvc {

namespace {
const int kMaxAudioDeviceCout = 10;
}  // namespace

// static
mate::WrappableBase* AudioManagerBinding::New(mate::Arguments* args) {
  return new AudioManagerBinding(args->isolate(), args->GetThis());
}
// static
mate::Handle<AudioManagerBinding> AudioManagerBinding::Create(
    v8::Isolate* isolate) {
  return mate::CreateHandle(isolate, new AudioManagerBinding(isolate));
}

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
      .SetMethod("setRecording", &AudioManagerBinding::SetRecording)
      .SetProperty("playback", &AudioManagerBinding::playback,
                   &AudioManagerBinding::SetPlayback)
      .SetMethod("setPlayback", &AudioManagerBinding::SetPlayback)
      .SetProperty("desktopRecording", &AudioManagerBinding::desktop_recording,
                   &AudioManagerBinding::SetDesktopRecording)
      .SetMethod("setDesktopRecording",
                 &AudioManagerBinding::SetDesktopRecording)
      .SetMethod("restartDesktopRecording",
                 &AudioManagerBinding::RestartDesktopRecording)
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
      .SetMethod("requestAudioVolume", &AudioManagerBinding::RequestAudioVolume)
      .SetMethod("builtInAECIsAvailable",
                 &AudioManagerBinding::BuiltInAECIsAvailable)
      .SetMethod("builtInAGCIsAvailable",
                 &AudioManagerBinding::BuiltInAGCIsAvailable)
      .SetMethod("builtInNSIsAvailable",
                 &AudioManagerBinding::BuiltInNSIsAvailable)
      .SetMethod("enableBuiltInAEC", &AudioManagerBinding::EnableBuiltInAEC)
      .SetMethod("enableBuiltInAGC", &AudioManagerBinding::EnableBuiltInAGC)
      .SetMethod("enableBuiltInNS", &AudioManagerBinding::EnableBuiltInNS);
}

AudioManagerBinding::AudioManagerBinding(v8::Isolate* isolate)
    : media_(Context::Instance()->GetMedia()) {
  Init(isolate);
}
AudioManagerBinding::AudioManagerBinding(v8::Isolate* isolate,
                                         v8::Local<v8::Object> wrapper)
    : media_(Context::Instance()->GetMedia()) {
  InitWith(isolate, wrapper);
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
  return media_->GetEnableAEC();
}

void AudioManagerBinding::SetAEC(bool enable) {
  media_->SetEnableAEC(enable);
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
    media_->StopAudioPlayout();

  if (enable)
    media_->SetAudioMode(yealink::AudioMode::AM_HANDSET_FREE);
  else
    media_->SetAudioMode(yealink::AudioMode::AM_IDLE);
}

bool AudioManagerBinding::desktop_recording() {
  return media_->IsAudioPlaying();
}

void AudioManagerBinding::SetDesktopRecording(bool enable) {
  media_->EnableSoundShare(enable);
}

void AudioManagerBinding::RestartDesktopRecording() {
  media_->RestartSoundShare();
}

void AudioManagerBinding::SetAudioMode(AudioMode mode) {
  media_->SetAudioMode(static_cast<yealink::AudioMode>(mode));
}

void AudioManagerBinding::EnumerateDevices() {
  yealink::MediaDeviceInfo devices[kMaxAudioDeviceCout] = {};
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

void AudioManagerBinding::PlayTone(std::string tone) {
  for (char s : tone) {
    media_->PlayTone(s);
  }
}

uint64_t AudioManagerBinding::RequestAudioVolume() {
  return media_->GetRecentVolume();
}

bool AudioManagerBinding::BuiltInAECIsAvailable() {
  return media_->BuiltInAECIsAvailable();
}

bool AudioManagerBinding::BuiltInAGCIsAvailable() {
  return media_->BuiltInAGCIsAvailable();
}

bool AudioManagerBinding::BuiltInNSIsAvailable() {
  return media_->BuiltInNSIsAvailable();
}

void AudioManagerBinding::EnableBuiltInAEC(bool enable) {
  media_->EnableBuiltInAEC(enable);
}

void AudioManagerBinding::EnableBuiltInAGC(bool enable) {
  media_->EnableBuiltInAGC(enable);
}

void AudioManagerBinding::EnableBuiltInNS(bool enable) {
  media_->EnableBuiltInNS(enable);
}

}  // namespace rtvc
