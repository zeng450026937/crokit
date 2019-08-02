#ifndef YEALINK_RTVC_BINDING_AUDIO_MANAGER_BINDING_H_
#define YEALINK_RTVC_BINDING_AUDIO_MANAGER_BINDING_H_

#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/audio_manager.h"

namespace yealink {

namespace rtvc {

class AudioManagerBinding : public mate::Wrappable<AudioManagerBinding>,
                            AudioManager {
 public:
  static mate::Handle<AudioManagerBinding> Create(v8::Isolate* isolate) {
    return mate::CreateHandle(isolate, new AudioManagerBinding(isolate));
  }
  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  AudioManagerBinding(v8::Isolate* isolate);
  ~AudioManagerBinding() override;

  int volume() override;
  void SetVolume(int volume) override;

  bool mute() override;
  void SetMute(bool mute) override;

  bool ans() override;
  void SetANS(bool enable) override;

  bool aec() override;
  void SetAEC(bool enable) override;

  bool agc() override;
  void SetAGC(bool enable) override;

  bool recording() override;
  void SetRecording(bool enable) override;

  bool playback() override;
  void SetPlayback(bool enable) override;

  std::vector<Device> audioInputDeviceList() override;
  std::vector<Device> audioOutputDeviceList() override;

  Device audioInputDevice() override;
  void SetAudioInputDevice(Device device) override;

  Device audioOutputDevice() override;
  void SetAudioOutputDevice(Device device) override;

  // TODO:
  // move these(blow) api out of this class
  void PlayTone(std::string tone) override;
  void StartPlayFile(std::string path) override;
  void StopPlayFile() override;

};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_AUDIO_MANAGER_BINDING_H_
