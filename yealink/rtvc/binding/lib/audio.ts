export enum MediaDeviceType {
    kAudioInput,
    kAudioOutput,
    kVideoInput,
    kScreen,
    kWindow,
    kImageFile,
}

export interface MediaDevice {
    deviceId: string;
    label: string;
    type: MediaDeviceType;
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
    audioInputDevice: MediaDevice;
    audioOutputDevice: MediaDevice;

    setRecording(enable: boolean): void;
    setPlayback(enable: boolean): void;
    setDesktopRecording(enable: boolean): void;
    restartDesktopRecording(): void;
    enumerateDevices(): void;
    audioInputDeviceList(): Array<MediaDevice>;
    audioOutputDeviceList(): Array<MediaDevice>;

    playTone(tone: string): void;
    requestAudioVolume(): number;
    builtInAECIsAvailable(): boolean;
    builtInAGCIsAvailable(): boolean;
    builtInNSIsAvailable(): boolean;
    enableBuiltInAEC(enable: boolean): void;
    enableBuiltInAGC(enable: boolean): void;
    enableBuiltInNS(enable: boolean): void;
}