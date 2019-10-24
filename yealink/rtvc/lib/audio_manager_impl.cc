#include "yealink/rtvc/lib/audio_manager_impl.h"

#include "base/logging.h"

namespace rtvc {

AudioManagerImpl::AudioManagerImpl() {}
AudioManagerImpl::~AudioManagerImpl() = default;

int AudioManagerImpl::volume() {
  LOG(INFO) << __FUNCTIONW__;
  return 0;
}
void AudioManagerImpl::SetVolume(int volume) {
  LOG(INFO) << __FUNCTIONW__;
}

bool AudioManagerImpl::mute() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
void AudioManagerImpl::SetMute(bool mute) {
  LOG(INFO) << __FUNCTIONW__;
}

bool AudioManagerImpl::ans() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
void AudioManagerImpl::SetANS(bool enable) {
  LOG(INFO) << __FUNCTIONW__;
}

bool AudioManagerImpl::aec() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
void AudioManagerImpl::SetAEC(bool enable) {
  LOG(INFO) << __FUNCTIONW__;
}

bool AudioManagerImpl::agc() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
void AudioManagerImpl::SetAGC(bool enable) {
  LOG(INFO) << __FUNCTIONW__;
}

bool AudioManagerImpl::recording() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
void AudioManagerImpl::SetRecording(bool enable) {
  LOG(INFO) << __FUNCTIONW__;
}

bool AudioManagerImpl::playback() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
void AudioManagerImpl::SetPlayback(bool enable) {
  LOG(INFO) << __FUNCTIONW__;
}

std::vector<Device> AudioManagerImpl::audioInputDeviceList() {
  LOG(INFO) << __FUNCTIONW__;
  return std::vector<Device>();
}
std::vector<Device> AudioManagerImpl::audioOutputDeviceList() {
  LOG(INFO) << __FUNCTIONW__;
  return std::vector<Device>();
}

base::Optional<Device> AudioManagerImpl::audioInputDevice() {
  LOG(INFO) << __FUNCTIONW__;
  return Device();
}
void AudioManagerImpl::SetAudioInputDevice(Device device) {
  LOG(INFO) << __FUNCTIONW__;
}

base::Optional<Device> AudioManagerImpl::audioOutputDevice() {
  LOG(INFO) << __FUNCTIONW__;
  return Device();
}
void AudioManagerImpl::SetAudioOutputDevice(Device device) {
  LOG(INFO) << __FUNCTIONW__;
}

void AudioManagerImpl::PlayTone(std::string tone) {
  LOG(INFO) << __FUNCTIONW__;
}
void AudioManagerImpl::StartPlayFile(std::string path) {
  LOG(INFO) << __FUNCTIONW__;
}
void AudioManagerImpl::StopPlayFile() {
  LOG(INFO) << __FUNCTIONW__;
}

// statc
AudioManager* AudioManager::Instance() {
  static AudioManagerImpl* audio_manager = new AudioManagerImpl();
  return audio_manager;
}

}  // namespace rtvc
