import { EventEmitter } from 'events';
import { VideoSink, VideoSource } from './video';
import { Conference } from './conference';
import { RTCStats } from './channel';

/* eslint-disable import/prefer-default-export */
export interface Call extends EventEmitter {
  // TODO
  // emit chat channel ready and focus channel ready event
  //
  // p2p upgrade to conference
  //
  connect(target: string, options: any): void;
  answer(): void;
  hangup(): void;

  // when conference aware is enabled, and current call is a conference
  // media session, conference session will be auto connected
  conferenceAware(): boolean;
  setConferenceAware(enable: boolean): void;

  // join conference with conference number & conference pin
  dialin(number: string, pin: string): void;

  isReadyForConference(): boolean;
  // access conference info/control api/interface
  conference(): Conference | null;

  forward(): void;
  refer(): void;
  replace(): void;

  hold(): void;
  unhold(): void;

  mute(): void;
  unmute(): void;

  sendDTMF(): void;
  sendInfo(): void;
  // send sms message to remote peer
  sendMessage(): void;

  // useful when network environment changed
  renegotiate(): void;

  isLocalSharing(): boolean;
  isRemoteSharing(): boolean;
  isReadyForSharing(): boolean;
  isSharingSupported(): boolean;

  startShare(): void;
  stopShare(): void;

  setMediaBitrate(bitrate: number): void;
  setShareBitrate(bitrate: number): void;

  // set custom video source instead of using device setted in VideoManager.
  // use selected device for local video streaming by default.
  setLocalVideoSource(source: VideoSource | null): void;
  setLocalShareVideoSource(source: VideoSource | null): void;

  // local video sink is setted in VideoManager
  setRemoteVideoSink(sink: VideoSink): void;
  setRemoteShareVideoSink(sink: VideoSink): void;

  getMediaStats(): RTCStats;
  getShareStats(): RTCStats;
}
