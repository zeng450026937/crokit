#ifndef API_MEDIA_H_
#define API_MEDIA_H_

#include <string>
#include <vector>

namespace yealink {

class VideoSink;

enum class DeviceType {
  kAudioInput,
  kAudioOutput,
  kVideoInput,
  kScreen,
  kWindow,
  kImageFile,
};

struct Device {
  std::string deviceId;
  std::string label;
  DeviceType type;
};

class AudioManager {
 public:
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

  virtual void playTone(std::string tone) = 0;
  virtual void startPlayFile(std::string path) = 0;
  virtual void stopPlayFile() = 0;

  virtual std::vector<Device> audioInputDeviceList() = 0;
  virtual std::vector<Device> audioOutputDeviceList() = 0;

  virtual Device audioInputDevice() = 0;
  virtual void setAudioInputDevice(Device device) = 0;

  virtual Device audioOutputDevice() = 0;
  virtual void setAudioOutputDevice(Device device) = 0;

 protected:
  virtual ~AudioManager() {}
};

class VideoManager {
 public:
  virtual std::vector<Device> videoInputDeviceList() = 0;
  virtual std::vector<Device> screenDeviceList() = 0;
  virtual std::vector<Device> windowDeviceList() = 0;
  
  virtual Device videoInputDevice() = 0;
  virtual void setVideoInputDevice(Device device) = 0;
  
  virtual Device sharedVideoInputDevice() = 0;
  virtual void setSharedVideoInputDevice(Device device) = 0;

  virtual void SetRotation(int rotation) = 0;
  virtual void SetRotation(Device device, int rotation) = 0;
  
  virtual void SetLocalVideoSink(VideoSink* sink) = 0;
  virtual void SetLocalShareVideoSink(VideoSink* sink) = 0;

 protected:
  virtual ~VideoManager() {}
};

}  // namespace yealink

#endif  // API_MEDIA_H_