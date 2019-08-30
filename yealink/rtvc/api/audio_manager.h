#ifndef YEALINK_RTVC_API_AUDIO_MANAGER_H_
#define YEALINK_RTVC_API_AUDIO_MANAGER_H_

#include <string>
#include <vector>

#include "base/optional.h"
#include "yealink/rtvc/api/device_type.h"

namespace yealink {

namespace rtvc {

enum class AudioMode {
  kIdle = 0,
  kHandsetFree,
  kHandset,
};

class AudioManager {
 public:
  static AudioManager* Instance();

  virtual int volume() = 0;
  virtual void SetVolume(int volume) = 0;

  virtual bool mute() = 0;
  virtual void SetMute(bool mute) = 0;

  virtual bool ans() = 0;
  virtual void SetANS(bool enable) = 0;

  virtual bool aec() = 0;
  virtual void SetAEC(bool enable) = 0;

  virtual bool agc() = 0;
  virtual void SetAGC(bool enable) = 0;

  virtual bool recording() = 0;
  virtual void SetRecording(bool enable) = 0;

  virtual bool playback() = 0;
  virtual void SetPlayback(bool enable) = 0;

  virtual std::vector<Device> audioInputDeviceList() = 0;
  virtual std::vector<Device> audioOutputDeviceList() = 0;

  virtual base::Optional<Device> audioInputDevice() = 0;
  virtual void SetAudioInputDevice(Device device) = 0;

  virtual base::Optional<Device> audioOutputDevice() = 0;
  virtual void SetAudioOutputDevice(Device device) = 0;

  // TODO:
  // move these(blow) api out of this class
  virtual void PlayTone(std::string tone) = 0;
  virtual void StartPlayFile(std::string path) = 0;
  virtual void StopPlayFile() = 0;

 protected:
  virtual ~AudioManager() = default;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_AUDIO_MANAGER_H_
