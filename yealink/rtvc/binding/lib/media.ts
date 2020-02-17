import { VideoSink, VideoSource } from './video';

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
  volume: number;
  mute: boolean;
  ans: boolean;
  aec: boolean;
  agc: boolean;
  recording: boolean;
  playback: boolean;
  desktopRecording: boolean;
  audioInputDevice: AudioInputDevice;
  audioOutputDevice: AudioOutputDevice;

  enumerateDevices(): void;
  audioInputDeviceList(): Array<AudioInputDevice>;
  audioOutputDeviceList(): Array<AudioOutputDevice>;

  setRecording(enable: boolean): void;
  setPlayback(enable: boolean): void;
  setDesktopRecording(enable: boolean): void;
  restartDesktopRecording(): void;

  playTone(tone: string): void;
  requestAudioVolume(): number;

  builtInAECIsAvailable(): boolean;
  builtInAGCIsAvailable(): boolean;
  builtInNSIsAvailable(): boolean;
  enableBuiltInAEC(enable: boolean): void;
  enableBuiltInAGC(enable: boolean): void;
  enableBuiltInNS(enable: boolean): void;
}

export type VideoRotation = 0 | 90 | 180 | 270

export interface VideoLimitInfo{
  fps: number,
  width: number,
  height: number
}

export interface VideoManager {

  videoInputDevice: VideoInputDevice;
  secondaryVideoInputDevice: VideoInputDevice;

  enumerateDevices(): void;
  videoInputDeviceList(): Array<VideoInputDevice>;
  setRotation(degree: VideoLimitInfo, secondary: boolean): void;
  acquireStream(params: VideoRotation): void;
  releaseStream(): void;
  acquiring(): boolean;

  setLocalVideoSink(sink: VideoSink): void;
  addLocalVideoSink(sink: VideoSink): void;
  removeLocalVideoSink(sink: VideoSink): void;

  setLocalShareVideoSink(sink: VideoSink): void;
  addLocalShareVideoSink(sink: VideoSink): void;
  removeLocalShareVideoSink(sink: VideoSink): void;

  setLocalVideoSource(source: VideoSource): void;
}
