import { VideoSink } from './video';

export enum DeviceType {
  kAudioInput,
  kAudioOutput,
  kVideoInput,
  kScreen,
  kWindow,
  kImageFile,
}

export interface Device {
  deviceId: string;
  label: string;
  type: DeviceType;
}

export interface VideoDevice extends Device {
  type: DeviceType.kVideoInput | DeviceType.kScreen | DeviceType.kWindow | DeviceType.kImageFile;
}

export interface VideoInputDevice extends VideoDevice {
  type: DeviceType.kVideoInput;
}

export interface ScreenDevice extends VideoDevice {
  type: DeviceType.kScreen;
}

export interface WindowDevice extends VideoDevice {
  type: DeviceType.kWindow;
}

export interface ImageFileDevice extends VideoDevice {
  type: DeviceType.kImageFile;
}

export interface AudioDevice extends Device {
  type: DeviceType.kAudioInput | DeviceType.kAudioOutput;
}

export interface AudioInputDevice extends AudioDevice {
  type: DeviceType.kAudioInput;
}

export interface AudioOutputDevice extends AudioDevice {
  type: DeviceType.kAudioOutput;
}

export interface AudioManager {
  volume(): number;
  setVolume(volume: number): void;

  mute(): boolean;
  setMute(mute: boolean): void;

  ans(): boolean;
  setANS(enable: boolean): void;

  aec(): boolean;
  setAEC(enable: boolean): void;

  agc(): boolean;
  setAGC(enable: boolean): void;

  recording(): boolean;
  setRecording(enable: boolean): void;

  playback(): boolean;
  setPlayback(enable: boolean): void;

  playTone(tone: string): void;

  startPlayFile(path: string): void;
  stopPlayFile(): void;

  audioInputDeviceList(): Array<AudioInputDevice>
  audioOutputDeviceList(): Array<AudioOutputDevice>

  audioInputDevice(): AudioInputDevice;
  setAudioInputDevice(device: AudioInputDevice): void;

  audioOutputDevice(): AudioOutputDevice;
  setAudioOutputDevice(device: AudioOutputDevice): void;
}

export type Rotation = 0 | 90 | 180 | 270

export interface VideoManager {
  videoInputDeviceList(): Array<VideoInputDevice>
  screenDeviceList(): Array<ScreenDevice>
  windowDeviceList(): Array<WindowDevice>

  videoInputDevice(): VideoInputDevice;
  setVideoInputDevice(device: VideoInputDevice): void;

  sharedVideoInputDevice(): VideoInputDevice;
  setSharedVideoInputDevice(device: VideoInputDevice | ScreenDevice | WindowDevice): void;

  setRotation(rotation: Rotation): void
  setRotation(device: VideoInputDevice | ScreenDevice | WindowDevice, rotation: Rotation): void

  setLocalVideoSink(sink: VideoSink): void;
  setLocalShareVideoSink(sink: VideoSink): void;
  // 有set 没有remove
  // 追加获取video source
}
