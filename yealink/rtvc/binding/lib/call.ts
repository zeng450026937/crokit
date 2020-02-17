import { EventEmitter } from 'events';
import { VideoSink, VideoSource } from './video';
import { Conference } from './conference';
import { UserAgent } from './user-agent'

export enum CallSvcSubscribeType {
  kShare,
  kMedia,
}

export interface CallConfig {
  userAgent: UserAgent;
  incoming: boolean;
}

export interface CallMedia {
  audio: boolean;
  video: boolean;
}

export interface CallLocalInfo {
  number: string;
  domain: string;
  displayName: string;
  userAgent: string;
}

export interface CallRemoteInfo {
  number: string;
  domain: string;
  displayName: string;
  userAgent: string;
}

export interface CallInfo {
  audio: boolean;
  video: boolean;
  encrypted: boolean;
  succeed: boolean;
  established: boolean;
  finished: boolean;
  remoteHold: boolean;
  localHold: boolean;
  incoming: boolean;
  outgoing: boolean;
  supportReplace: boolean;
  reason: string;
  localIdentity: CallLocalInfo;
  remoteIdentity: CallRemoteInfo;
}

export interface CallAudioStatsInfo {
  codec: string;
  bitrate: number;
  samplerate: number;
  lossRate: number;
  totalLostPackets: number;
  jitter: number;
  delay: number;
}

export interface CallVideoStatsInfo {
  codec: string;
  profile: string;
  width: number;
  height: number;
  frame_rate: number;
  bit_rate: number;
  loss_rate: number;
  total_loss_packets: number;
  jitter: number;
  rtt: number;
}

export interface CallRTCVideoStats {
  outbound: CallVideoStatsInfo;
  inbound: Array<CallVideoStatsInfo>;
}

export interface CallRTCAudioStats {
  outbound: CallAudioStatsInfo;
  inbound: CallAudioStatsInfo;
}

export interface CallRTCStats {
  audio: CallRTCAudioStats;
  video: CallRTCVideoStats;
}

export interface CallRTCStatsInfo {
  media: CallRTCStats;
  share: CallRTCStats;
}

export interface CallVideoSubscribe {
  enable: boolean;
  id: number;
  width: number;
  height: number;
}

export interface Call extends EventEmitter {
  new(config: CallConfig);

  emit(event: string | symbol, ...args: any[]): boolean;
  on(event: string, listener: (...args: any[]) => void): this;

  on(event: 'progress', listener: () => void): this;
  on(event: 'trying', listener: () => void): this;
  on(event: 'ringing', listener: () => void): this;
  on(event: 'redirect', listener: () => void): this;
  on(event: 'established', listener: () => void): this;
  on(event: 'refered', listener: () => void): this;
  on(event: 'replaced', listener: () => void): this;

  on(event: 'finished', listener: () => void): this;
  on(event: 'update', listener: () => void): this;
  on(event: 'referFailed', listener: () => void): this;
  on(event: 'replaceFailed', listener: () => void): this;

  on(event: 'upgraded', listener: () => void): this;
  on(event: 'upgradeFailed', listener: () => void): this;

  on(event: 'focus:ready', listener: () => void): this;
  on(event: 'focus:prepare', listener: () => void): this;
  on(event: 'focus:established', listener: () => void): this;
  on(event: 'focus:finished', listener: () => void): this;

  on(event: 'share:ready', listener: () => void): this;
  on(event: 'share:established', listener: () => void): this;
  on(event: 'share:finished', listener: () => void): this;

  on(event: 'rtc:audioStart', listener: () => void): this;
  on(event: 'rtc:audioStop', listener: () => void): this;
  on(event: 'rtc:audioBroken', listener: () => void): this;
  on(event: 'rtc:videoStart', listener: () => void): this;
  on(event: 'rtc:videoStop', listener: () => void): this;
  on(event: 'rtc:videoBroken', listener: () => void): this;
  on(event: 'rtc:shareRecvStart', listener: () => void): this;
  on(event: 'rtc:shareRecvStop', listener: () => void): this;
  on(event: 'rtc:shareSendStart', listener: () => void): this;
  on(event: 'rtc:shareSendStop', listener: () => void): this;
  on(event: 'rtc:shareBroken', listener: () => void): this;

  connect(target: string, options: CallMedia): void;
  answer(options: CallMedia): void;
  hangup(reason: string): void;
  upgrade(options: CallMedia): Promise<void>;

  hold(): void;
  unhold(): void;
  mute(): void;
  unmute(): void;
  sendDTMF(tone: string): void;

  getStats(): Promise<CallRTCStatsInfo>;
  getInfos(): CallInfo;
  asConference(): Conference;

  setRemoteVideoSink(sink: VideoSink): void;
  setRemoteShareVideoSink(sink: VideoSink): void;

  addRemoteVideoSink(sink: VideoSink): void;
  addRemoteShareVideoSink(sink: VideoSink): void;

  removeRemoteVideoSink(sink: VideoSink): void;
  removeRemoteShareVideoSink(sink: VideoSink): void;

  setShareBitrate(send: number, recv: number): void;
  setMediaBitrate(send: number, recv: number): void;

  startShare(): void;
  stopShare(): void;

  isSupportSvcSubscribe(type: CallSvcSubscribeType): boolean;
  setSvcSubscribe(type: CallSvcSubscribeType, list: Array<CallVideoSubscribe>): boolean;
  setSvcEnable(enable: boolean): void;

  readonly isInProgress: boolean;
  readonly isEstablished: boolean;
  readonly isEnded: boolean;
  readonly isRefering: boolean;
  readonly isUpgrading: boolean;
  readonly isReadyForShare: boolean;
  readonly isShareChannelSupported: boolean;
  readonly isShareChannelEstablished: boolean;
  readonly localSharing: boolean;
  readonly remoteSharing: boolean;
  readonly incoming: boolean;
  readonly outgoing: boolean;
  portraitMode: boolean;
  readonly conference: Conference;
}
