import { EventEmitter } from 'events';
import UserAgent from './user-agent';

/** Chat */
export interface ConferenceChatMessage {
  readonly isPrivate: boolean;
  readonly isRead: boolean;
  readonly bizCode: number;
  readonly index: number;
  readonly text: string;
  readonly status: string;
  readonly senderEntity: string;
  readonly senderName: string;
  readonly direction: string;

  setStatus(read: boolean): Promise<void>;
}
export interface ConferenceChatDialog {
  readonly entity: string;
  readonly isPrivate: boolean;
  readonly unreadCount: number;
  readonly messages: Array<ConferenceChatMessage>

  clearUnread(): boolean;
}
export interface ConferenceChat {
  sendChatMessage(msg: string, entities: Array<string>): Promise<ConferenceChatMessage>;
  retrySendChatMessage(message: ConferenceChatMessage): Promise<void>;

  publicDialog(): ConferenceChatDialog;
  dialogList(): Array<ConferenceChatDialog>;
}

/** Description */
export interface ConferenceDescriptionBanner {
  readonly enabled: boolean;
  readonly displayText: string;
  readonly position: string;  // top | medium | bottom
}
export interface ConferenceDescriptionRtmp {
  readonly enabled: boolean;
  readonly displayText: string;
  readonly mcuSessionType: string;  // AV | AD |AVD
  readonly maxVideoFs: string;      // 360P |  720P | 1080P
  readonly webShareUrl: string;
}
export interface ConferenceDescriptionUriInfo {
  readonly uri: string;
  readonly displayText: string;
  readonly purpose: string;   // applicationsharing | audio-video | chat | coopshare | focus
}
export interface ConferenceDescriptionOrganizer {
  readonly uid: string;
  readonly displayText: string;
  readonly username: string;
  readonly realm: string;
  readonly phone: string;
  readonly domain: string;
}
export interface ConferenceDescriptionLockInfo {
  admissionPolicy: string;  // closedAuthenticated | anonymous | openAuthenticated
  attendeeByPass: boolean;
  autoPromote: number;  // 0 | 32768 | 2147483648
}
export interface ConferenceDescription {
  readonly subject: string;
  readonly startTime: number;
  readonly banner: ConferenceDescriptionBanner;
  readonly defaultRtmp: ConferenceDescriptionRtmp;
  readonly profile: string;
  readonly recordId: string;
  readonly confUris: Array<ConferenceDescriptionUriInfo>;
  readonly organizer: ConferenceDescriptionOrganizer;
  readonly conferenceId: string;
  readonly conferenceNumber: string;
  readonly conferenceType: string;
  readonly conferenceNumberType: string;
  readonly bookStartTime: number;
  readonly bookExpiryTime: number;
  readonly presenterPin: string;
  readonly attendeePin: string;
  readonly maximumUserCount: number;
  readonly admissionPolicy: string;
  readonly lobbyCapable: boolean;
  readonly attendeeByPass: boolean;
  readonly autoPromote: string;
  readonly serverMode: string;
  readonly interactiveBroadcastEnabled: boolean;
  readonly enterpriseId: string;
  readonly videoEnable: boolean;
  readonly ipcallEnable: boolean;
  readonly webrtcEnable: boolean;
  readonly recordServerType: string;    // ylrecord | third-party
  readonly recordPrivilege: string;     // organizer | presenter | attendee
  readonly confInfoUrl: string;

  getDefaultRtmp(): ConferenceDescriptionRtmp;
  GetLock(): ConferenceDescriptionLockInfo;

  setLock(params: ConferenceDescriptionLockInfo): Promise<void>;
  getShareInfo(lang: string): Promise<void>;
}

/** Record */
export interface ConferenceRecordUserInfo {
  recordStatus: string; // pause | pausing | resume | resuming | start | starting | stop | stopping
  recordLastStopDuration: number;
  recordLastStartTime: number;
}
export interface ConferenceRecordInfo {
  bizCode: number;
  user: ConferenceRecordUserInfo
}
export interface ConferenceRecord {
  getRecordStatus(): ConferenceRecordInfo;
  setRecordStatus(status: string): Promise<void>;
}

/** Rtmp */
export interface ConferenceRtmpUserInfo {
  readonly entity: string;
  readonly isDefault: boolean;
  readonly rtmpStatus: string;  // pause | pausing | resume | resuming | start | starting | stop | stopping
  readonly rtmpLastStopDuration: number;
  readonly rtmpLastStartTime: number;
}
export interface ConferenceRtmpInfo {
  readonly enable: boolean;
  readonly bizCode: number;
  readonly users: Array<ConferenceRtmpUserInfo>
}
export interface ConferenceRtmp {
  getRtmpStatus(): ConferenceRtmpInfo;
  setRtmpStatus(status: string): Promise<void>;
}

/** State */
export interface ConferenceState {
  readonly active: boolean;
  readonly locked: boolean;
  readonly rollCallStatus: string;
}
/** Users */
export interface ConferenceUserRoleInfo {
  readonly permission: string;          // attendee | castviewer | organizer | presenter
  readonly demostate: string;           // audience | demonstrator
  readonly presenterDemostate: string;  // audience | demonstrator
}
export interface ConferenceUserMediaInfo {
  readonly id: string;
  readonly type: string;                // application | audio | video
  readonly label: string;               // application | fecc | main-video | main-audio
  readonly status: string;              // inactive | recvonly | sendonly | sendrecv
  readonly mediaIngressFilter: string;  // block | unblock | unblocking
  readonly mediaIngressBlockBy: string; // client | server | none
  readonly mediaEgressFilter: string;   // block | unblock | unblocking
  readonly mediaEgressBlockBy: string;  // client | server | none
}
export interface ConferenceUserEndpointInfo {
  readonly entity: string;
  readonly sessionType: string;   // applicationsharing | audio-video | chat | coopshare | focus
  readonly status: string;        // connected | dialing-in | dialing-out | disconnected | on-hold
  readonly joiningMethod: string; // dialed-in | dialed-out
  readonly when: string;
  readonly mcuCallId: string;
  readonly media: Array<ConferenceUserMediaInfo>
}
export interface ConferenceUserFilterInfo {
  readonly mediaIngressFilter: string;  // block | unblock | unblocking
  readonly mediaIngressBlockBy: string; // client | server | none
  readonly mediaEgressFilter: string;   // block | unblock | unblocking
  readonly mediaEgressBlockBy: string;  // client | server | none
}
export interface ConferenceUserMediaDataInfo {
  enable: boolean;
  ip: string;
  codec: string;
  width: number;
  height: number;
  fr: number;
  sampleRate: number;
  bandwidth: number;
  bitRate: number;
  lossRate: number;
  packetLost: number;
  jitter: number;
  rtt: number;
}
export interface ConferenceUserStatisticsInfo {
  mediaId: string;
  label: string;  // application | fecc | main-audio | main-video
  type: string;   // application | audio | video
  send: ConferenceUserMediaDataInfo;
  recv: ConferenceUserMediaDataInfo;
}

export interface ConferenceUser {
  readonly entity: string;
  readonly displayText: string;
  readonly displayNumber: string;
  readonly displayTextPinyin: string;
  readonly uid: string;
  readonly protocol: string; // SIP | H323 | RTMP
  readonly mediumServerType: string;
  readonly ip: string;
  readonly phone: string;
  readonly requestUri: string;
  readonly roles: ConferenceUserRoleInfo;
  readonly endpoint: Array<ConferenceUserEndpointInfo>;

  isOrganizer(): boolean;
  isPresenter(): boolean;
  isAttendee(): boolean;
  isCastViewer(): boolean;
  isDemonstrator(): boolean;
  isOnHold(): boolean;
  isCurrentUser(): boolean;
  isRtmp(): boolean;
  isSIP(): boolean;
  isSharing(): boolean;
  isFocus(): boolean;
  hasFECC(): boolean;
  isConnected(): boolean;

  getAudioFilter(): ConferenceUserFilterInfo;
  getVideoFilter(): ConferenceUserFilterInfo;
  getStats(): Promise<ConferenceUserStatisticsInfo>;

  setAudioIngressFilter(open: boolean): Promise<void>;
  setAudioEgressFilter(open: boolean): Promise<void>;
  setVideoIngressFilter(open: boolean): Promise<void>;
  setPermission(type: string): Promise<void>;
  setDemonstrator(type: string): Promise<void>;
  setDisplayName(name: string): Promise<void>;
  setFocus(focus: boolean): Promise<void>;

  hold(): Promise<void>;
  unHold(): Promise<void>;
  kick(): Promise<void>;
}
export interface ConferenceUsers {
  currentUser(): ConferenceUser;
  userList(): Array<ConferenceUser>;
  addedUser(): Array<ConferenceUser>;
  deletedUser(): Array<ConferenceUser>;
  updatedUser(): Array<ConferenceUser>;
  presenters(): Array<ConferenceUser>;
  attendees(): Array<ConferenceUser>;
  onHoldUsers(): Array<ConferenceUser>;
  demonstrators(): Array<ConferenceUser>;
  castViewers(): Array<ConferenceUser>;

  invite(uri: string): Promise<void>;
  inviteThird(uri: string, uid: string): Promise<void>;
  inviteBatch(uris: Array<string>): Promise<void>;
  allow(entity: Array<string>, granted: boolean): Promise<void>;
  handUp(granted: boolean): Promise<void>;
}

/** View */
export interface ConferenceViewLayoutInfo {
  speakMode: string;            // free | handUp
  videoLayout: string;          // Equality | SpeechExcitation | Exclusive | Presentation
  videoMaxView: number;
  videoPresenterLayout: string; // Equality | SpeechExcitation | Exclusive
  videoPresenterMaxView: number;
  videoRoundNumber: number;
  videoRoundInterval: number;
  videoSpeechExSensitivity: number;
  videoRoundEnable: boolean;
  videoBigRound: boolean;
  videoSpeechExEnabled: boolean;
  videoDataMixEnabled: boolean;
  hideOsdSitename: boolean;
  hideOsdSitestatus: boolean;
}
export interface ConferenceViewFilterInfo {
  role: string;     // default | attendee
  ingress: string;  // block | unblock
  egress: string;   // block | unblock
}
export interface ConferenceView {
  getLayout(): ConferenceViewLayoutInfo;
  setLayout(params: ConferenceViewLayoutInfo): Promise<void>;

  getInitialFilters(): ConferenceViewFilterInfo;
  setInitialFilters(params: ConferenceViewFilterInfo): Promise<void>;

  getSpeakMode(): string;
  setSpeakMode(mode: string): Promise<void>;
}

export interface CreateInfo {
  subject: string;
  conversationId: string;
}

declare class Conference extends EventEmitter {
  constructor(userAgent: UserAgent);

  emit(event: string | symbol, ...args: any[]): boolean;
  on(event: string, listener: (...args: any[]) => void): this;

  on(event: 'connected', listener: () => void): this;
  on(event: 'connectFailed', listener: () => void): this;
  on(event: 'disconnected', listener: () => void): this;
  on(event: 'finished', listener: () => void): this;
  on(event: 'descriptionUpdated', listener: () => void): this;
  on(event: 'stateUpdated', listener: () => void): this;
  on(event: 'viewUpdated', listener: () => void): this;
  on(event: 'usersUpdated', listener: () => void): this;
  on(event: 'rtmpUpdated', listener: () => void): this;
  on(event: 'recordUpdated', listener: () => void): this;

  on(event: 'user:added', listener: () => void): this;
  on(event: 'user:updated', listener: () => void): this;
  on(event: 'user:removed', listener: () => void): this;

  on(event: 'messageInited', listener: () => void): this;
  on(event: 'messageUpdated', listener: () => void): this;
  on(event: 'dialogUpdated', listener: () => void): this;

  connect(uri: string, entity: string): void;
  disconnect(end: boolean): void;
  create(params: CreateInfo): void;

  readonly isInProgress: boolean;
  readonly isEstablished: boolean;
  readonly isEnded: boolean;
  readonly isChatChannelSupported: boolean;
  readonly isChatChannelEstablished: boolean;

  readonly description: ConferenceDescription;
  readonly view: ConferenceView;
  readonly state: ConferenceState;
  readonly users: ConferenceUsers;
  readonly rtmp: ConferenceRtmp;
  readonly record: ConferenceRecord;
  readonly chat: ConferenceChat;
}

export default Conference;
