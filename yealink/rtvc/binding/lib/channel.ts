import { EventEmitter } from 'events';
import { VideoSink } from './video';

export enum SignalingState {
  kStable,
  kHaveLocalOffer,
  kHaveLocalPrAnswer,
  kHaveRemoteOffer,
  kHaveRemotePrAnswer,
  kClosed,
}

export enum IceGatheringState {
  kNew,
  kGathering,
  kComplete,
}

export enum IceConnectionState {
  kNew,
  kConnectin,
  kConnected,
  kDisconnected,
  kFailed,
  kClosed,
}

export enum RTCSessionState {
  kNew,
  kConnectin,
  kConnected,
  kDisconnected,
  kFailed,
  kClosed,
}

export interface RTCCodec {
  payloadType: number;
  codec: string;
  clockRate: number;
  parameters: string;
}

export interface RTCTransportStats {
  bytesSent: number;
  bytesReceived: number;
  packetSent: number;
  packetLost: number;
  packetLostRate: number;
  bitrate: number;
  jitter: number;
  rtt: number;
}

export interface RTCStreamStats extends RTCTransportStats {
  isRemote: boolean;
  ssrc: string;
  codec: RTCCodec;
}

export interface RTCAudioStreamStats extends RTCStreamStats {
  sampelrate: number;
  channel: number;
  delay: number;
}
export interface RTCVideoStreamStats extends RTCStreamStats {
  width: number;
  height: number;
  frameRate: number;
}

export interface RTCMediaStats {
  audio: RTCAudioStreamStats;
  video: RTCVideoStreamStats;
}

export interface RTCStats {
  inbound: RTCMediaStats;
  outbound: RTCMediaStats;
}

// yealink version of webrtc peerconnection
export interface RTCSession extends EventEmitter {
  on(event: 'close', listener: () => void): this;

  createOffer(): void;
  createAnswer(): void;

  close(): void;

  ice(): boolean;
  setICE(enable: boolean): void;

  dtls(): boolean;
  setDTLS(enable: boolean): void;

  localDescription(): string;
  setLocalDescription(desc: string): void;

  remoteDescription(): string;
  setRemoteDescription(desc: string): void;

  setLocalVideoSink(sink: VideoSink): void;
  setRemoteVideoSink(sink: VideoSink): void;

  insertDTMF(tones: string, duration?: number, interToneGap?: number): void;

  getStats(): RTCStats;

  setBitrate(bitrate: number): void;
}

export enum ChannelState {
  kConnecting,
  kConnected,
  kFailed,
  kFinished,
}

export enum ChannelDirection {
  kNone,
  kIncoming,
  kOutgoing,
}

export interface Channel extends EventEmitter {
  emit(event: string | symbol, ...args: any[]): boolean;
  on(event: string, listener: (...args: any[]) => void): this;

  // singaling state
  on(event: 'connecting', listener: () => void): this;
  on(event: 'connected', listener: () => void): this;
  on(event: 'failed', listener: () => void): this;
  on(event: 'ended', listener: () => void): this;
  // p2p
  on(event: 'ringing', listener: () => void): this;
  on(event: 'forward', listener: () => void): this;
  on(event: 'refer', listener: () => void): this;
  on(event: 'replace', listener: () => void): this;
  on(event: 'hold', listener: (local: boolean, remote: boolean) => void): this;
  on(event: 'newInfo', listener: () => void): this;
  on(event: 'newDTMF', listener: () => void): this;
  // media state
  on(event: 'rtc:negotiateFailed', listener: () => void): this;
  on(event: 'rtc:connectFailed', listener: () => void): this;
  on(event: 'rtc:connected', listener: () => void): this;

  // chat
  on(event: 'chatMessage', listener: () => void): this;

  state(): ChannelState;
  direction(): ChannelDirection;
  localIdentity(): string;
  remoteIdentity(): string;
  // custom data
  data(): any;
  setData(data: any): void;

  isInProgress(): boolean;
  isEstablished(): boolean;
  isEnded(): boolean;

  offer(): void;
  answer(): void;

  refer(): void;

  sendDTMF(): void;
  sendInfo(): void;

  renegotiate(): void;
}

export interface MediaChannel extends Channel {

  // ready for hold() unhold() renegotiate()
  isReadyForReOffer(): boolean;

  hold(): void;
  unhold(): void;

  mute(): void;
  unmute(): void;
}

export interface ChatChannel extends Channel {
  sendMessage(msg: string, users: Array<string>): void;
}
