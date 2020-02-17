#ifndef YEALINK_RTVC_BINDING_AUDIO_MANAGER_BINDING_H_
#define YEALINK_RTVC_BINDING_AUDIO_MANAGER_BINDING_H_

#include "base/optional.h"
#include "yealink/libvc/include/media/media_api.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/audio_manager.h"

namespace rtvc {
class AudioManagerBinding : public mate::Wrappable<AudioManagerBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<AudioManagerBinding> Create(v8::Isolate* isolate);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  AudioManagerBinding(v8::Isolate* isolate);
  AudioManagerBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ~AudioManagerBinding() override;

  int volume();
  void SetVolume(int volume);

  bool mute();
  void SetMute(bool mute);

  bool ans();
  void SetANS(bool enable);

  bool aec();
  void SetAEC(bool enable);

  bool agc();
  void SetAGC(bool enable);

  bool tns();
  void SetTNS(bool enable);

  bool recording();
  void SetRecording(bool enable);

  bool playback();
  void SetPlayback(bool enable);

  bool desktop_recording();
  void SetDesktopRecording(bool enable);
  // Restart desktop recording without changing record state. As desktop
  // recording always capture the default audio output device, invoke when
  // device changed.
  void RestartDesktopRecording();

  void SetAudioMode(AudioMode mode);

  void EnumerateDevices();

  std::vector<Device> audioInputDeviceList();
  std::vector<Device> audioOutputDeviceList();

  base::Optional<Device> audioInputDevice();
  void SetAudioInputDevice(base::Optional<Device> device);

  base::Optional<Device> audioOutputDevice();
  void SetAudioOutputDevice(base::Optional<Device> device);

  void PlayTone(std::string tone);
  void StartPlayFile(std::string path, mate::Arguments* args);
  void StopPlayFile();

  // calc input audio volume
  uint64_t RequestAudioVolume();

  // used in android device
  // should not touch this interface
  bool BuiltInAECIsAvailable();
  bool BuiltInAGCIsAvailable();
  bool BuiltInNSIsAvailable();
  void EnableBuiltInAEC(bool enable);
  void EnableBuiltInAGC(bool enable);
  void EnableBuiltInNS(bool enable);

 private:
  yealink::Media* media_;

  std::vector<Device> audio_input_device_list_;
  std::vector<Device> audio_output_device_list_;

  base::Optional<Device> audio_input_device_;
  base::Optional<Device> audio_output_device_;

  bool sysc_tns_;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_AUDIO_MANAGER_BINDING_H_
