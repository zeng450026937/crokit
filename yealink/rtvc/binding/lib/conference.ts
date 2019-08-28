import { EventEmitter } from 'events';

export interface ConferenceDescription {
  readonly subject: string;
  readonly note: string;
  readonly locations: string;
  readonly banner: string;
  readonly procedure: string;
  readonly scheduleId: string;
  readonly profile: string;
  readonly confUris: string;
  readonly applicant: string;
  readonly organizer: string;
  readonly invitees: string;
  readonly rtmpInvitees: string;
  readonly conferenceId: string;
  readonly conferenceNumber: string;
  readonly conferenceType: string;
  readonly isRecurrence: string;
  readonly presenterPin: string;
  readonly attendeePin: string;
  readonly maximumUserCount: string;
  readonly startTime: string;
  readonly endTime: string;
  readonly bookStartTime: string;
  readonly bookExpiryTime: string;
  readonly remindEarly: string;
  readonly createEarly: string;
  readonly recurrencePattern: string;
  readonly admissionPolicy: string;
  readonly attendeeByPass: string;
  readonly lobbyCapable: string;
  readonly joinUrl: string;
  readonly confInfoUrl: string;
  readonly autopromote: string;
  readonly serverMode: string;
  readonly hideOsd: string;
  readonly interactiveBroadcastEnabled: string;
  readonly defaultRtmp: string;
  readonly recordId: string;
  readonly planId: string;
  readonly speechMode: string;
  readonly recordServerType: string;
  readonly recordPrivilege: string;
  readonly forwardEnabled: string;
  readonly enterpriseId: string;

  // for internal uses
  getUri(purpose: 'focus' | 'audio-video' | 'applicationsharing'): string

  getBanner(): any;
  getPresetBanner(): any;
  setBanner(banner: any): void;
  saveBanner(banner: any): void;

  getProcedure(): any;
  setProcedure(): void;
  saveProcedure(): void;

  getTitle(): any;
  setTitle(): void;
  saveTitle(): void;
  cancelTitle(): void;

  getDefaultRTMP(): any;
  setDefaultRTMP(): void;

  getRecordServerType(): any;

  getSpeechMode(): any;
  setSpeechMode(): void;
}
export interface ConferenceState {
  readonly active: boolean;
  readonly locked: boolean;
  readonly applicationsharer: any;
  readonly rollCallStatus: any;
  readonly forwarder: any;

  sharingUser(): ConferenceUser;

  getLock(): any;
  setLock(): void;

  getForwarder(): any;
}
export interface ConferenceView {
  readonly entityView: any;
  readonly subtitle: string;

  getEntityView(): any;

  getMediaView(): any;
  setMediaView(): void;

  getInitialFilters(type: 'audio' | 'video'): any;
  setInitialFilters(type: 'audio' | 'video'): any;

  getDefaultFilter(): any;
  setDefaultFilter(): any;

  getAttendeeFilter(): any;
  getAttendeeFilter(): any;

  getLayout(): any;
  setLayout(): void;

  getBroadcastLayout(): any;
  getBroadcastLayout(): void;

  getSupervisionLayout(): any;
  setSupervisionLayout(): void;

  getStudentAudioFilter(): any;
  setStudentAudioFilter(): void;

  setPerspective(): void;
}

export interface RTMPCon {
  readonly participantCount: number;

  defaultRTMPUser(): any;
  // default rtmp from conference description
  config(): any;
  // default status, alias for defaultRTMPUser
  status(): any;
  getStatus(entity: string): any;

  // apply conference default rtmp options
  apply(): void;

  start(entity: string | null): void;
  stop(entity: string | null): void;
  pause(entity: string | null): void;
  resume(entity: string | null): void;

  invite(user: string): void;
  // modify rtmp user options
  modify(user: string, options: any): void;

  getInfo(options: any): void;
}
export interface RecordCon {
  readonly participantCount: number;

  defaultRecordUser(): any;
  // default status, alias for defaultRecordUser
  status(): any;

  getRecordList(): void;

  start(entity: string): void;
  stop(entity: string): void;
  pause(entity: string): void;
  resume(entity: string): void;
}
export interface LobbyCon {
  // apply conference lock options
  apply(options: any): void;

  hold(): void;
  unhold(): void;
  allow(): void;
  refuse(): void;
  // alias for refuse()
  kick(): void;
}
export interface RollCallCon {
  apply(): void;
  modify(entity: string, options: any): void;
  reset(): void;

  start(): void;
  stop(): void;
  pause(): void;
  resume(options: any): void;

  getStatus(): any;
  getResult(): any;
}
export interface UserCon {
  readonly participantCount: number;
  readonly broadcastUserCount: number;
  readonly interactiveUserCount: number;

  users(): Array<ConferenceUser>;

  currentUser(): ConferenceUser;
  sharingUser(): ConferenceUser;
  organizer(): ConferenceUser;

  getUser(entity: string): ConferenceUser;
  hasUser(entity: string): boolean;

  // invite user
  invite(users: Array<any> | any): void;
  // invite user with command batched
  inviteBatch(users: Array<any> | any): void;

  setDemonstrator(entitys: Array<string> | string, enable: boolean): void;
  // server do not support
  // setDemonstratorBatch(entitys: Array<string> | string, enable: boolean): void;
  setPresenterDemonstrator(entitys: Array<string> | string, enable: boolean): void;
  // server do not support
  // setPresenterDemonstratorBatch(entitys: Array<string> | string, enable: boolean): void;
  setPermission(entitys: Array<string> | string, role: any): void;
  setPermissionBatch(entitys: Array<string> | string, role: any): void;

  setFilter(entitys: Array<string> | string, filter: object): void;
  setAudioFilter(entitys: Array<string> | string, filter: object): void;
  setVideoFilter(entitys: Array<string> | string, filter: object): void;

  hold(entitys: Array<string> | string): void;
  unhold(entitys: Array<string> | string): void;
  allow(entitys: Array<string> | string, granted: boolean): void;

  kick(entitys: Array<string> | string): void;

  getStatistics(entitys: Array<string> | string): any;
  getStatisticsBatch(entitys: Array<string> | string): any;
}
export enum CameraAction {
  LEFT = 0,
  RIGHT = 1,
  DOWN = 2,
  UP = 3,
  ZOOMOUT = 4,
  ZOOMIN = 5,
}
export interface CameraCon {
  action(type: CameraAction, step: number): void;

  up(step: number): void;
  down(step: number): void;
  left(step: number): void;
  right(step: number): void;
  zoomin(step: number): void;
  zoomout(step: number): void;
}
export interface ConferenceUser {
  readonly entity: number;
  readonly uid: string;
  readonly displayText: string;
  readonly displayTextPinyin: string;
  readonly protocol: string;
  readonly ip: string;
  readonly phone: string;
  readonly userAgent: string;
  readonly roles: string;
  readonly endpoint: string;
  readonly videoLimitByLicence: string;
  readonly requestUri: string;

  rolesEntry(): any;
  mediaList(): Array<any>;

  getEndpoint(type: 'focus' | 'audio-video' | 'applicationsharing' | 'chat'): any;
  getMedia(type: 'main-audio' | 'main-video' | 'applicationsharing' | 'fecc'): any;
  getAudioFilter(): any;
  getVideoFilter(): any;

  isConnected(): boolean;
  isRegistered(): boolean;
  isAudioApplicant(): boolean;
  isVideoApplicant(): boolean;
  isRTMP(): boolean;
  isSIP(): boolean;
  isPresenter(): boolean;
  isAttendee(): boolean;
  isCastViewer(): boolean;
  isDemonstrator(): boolean;
  isPresenterDemonstrator(): boolean;
  isOnHold(): boolean;
  isFocusAvariable(): boolean;
  isMediaAvariable(): boolean;
  isSharing(): boolean;
  // user camera can be controlled through fecc session
  hasFECC(): boolean;

  // user extended
  isShareAvariable(): boolean;
  isCurrentUser(): boolean;
  isOrganizer(): boolean;
  isForwarder(): boolean;

  // get camera controller
  camera(): CameraCon | null;

  setFilter(): void;
  setAudioFilter(): void;
  setVideoFilter(): void;

  setPermission(): void;
  setDemonstrator(): void;
  setPresenterDemonstrator(): void;

  // hold user in conference room
  // user will be moved to conference lobby
  hold(): void;
  // move user into conference room from conference lobby
  unhold(): void;
  // unhold or delete user from conference lobby
  allow(granted: boolean): void;

  kick(): void;
  // send sms message to the user
  sendSMSMessage(msg: string): void;

  getStatistics(): any;
}
export interface ConferenceRTMPUser extends ConferenceUser {
  readonly rtmpType: string;
  readonly rtmpStatus: string;
  readonly maxVideoFs: string;
  readonly mcuSessionType: string;
  readonly rtmpDuration: string;
  readonly rtmpLastStopDuration: string;
  readonly rtmpLastStartTime: string;

  // user extended
  start(): void;
  stop(): void;
  pause(): void;
  resume(): void;
}
export interface ConferenceRecordUser extends ConferenceUser {
  readonly recordType: string;
  readonly recordStatus: string;
  readonly recordDuration: string;
  readonly recordLastStopDuration: string;
  readonly recordLastStartTime: string;
  readonly recordServerType: string;

  // user extended
  start(): void;
  stop(): void;
  pause(): void;
  resume(): void;
}

export interface ConferenceSupervisionUser extends ConferenceUser {}

export interface ConferenceCon {
  // TODO
  // list all supported conference command
}

export interface Conference extends EventEmitter {
  // TODO
  // emit more events about focus channel or connection state
  // emit more events about chat channel
  //
  on(event: 'descriptionUpdated', listener: () => void): this;
  on(event: 'stateUpdated', listener: () => void): this;
  on(event: 'viewUpdated', listener: () => void): this;
  on(event: 'usersUpdated', listener: () => void): this;
  on(event: 'rtmpUserUpdated', listener: () => void): this;
  on(event: 'recordUserUpdated', listener: () => void): this;
  on(event: 'privateDataUpdated', listener: () => void): this;

  on(event: 'userAdded', listener: () => void): this;
  on(event: 'userUpdated', listener: () => void): this;
  on(event: 'userDeleted', listener: () => void): this;

  on(event: 'chatMessage', listener: () => void): this;

  // the original conference control command/interface, for advanced use.
  controller(): ConferenceCon;

  description(): ConferenceDescription;
  state(): ConferenceState;
  view(): ConferenceView;
  // user parts
  usercon(): UserCon;
  // rtmp parts
  rtmpcon(): RTMPCon;
  // record parts
  recordcon(): RecordCon;
  // lobby parts
  lobbycon(): LobbyCon;
  // roll call parts
  rollcallcon(): RollCallCon;
  // custom data which was setted when user create conference with open api
  data(): any;
  // modify custom data
  setData(data: any): void;

  connect(): void;
  disconnect(): void;

  isConnected(): boolean;
  // this conference support chat channel
  isChatChannelSupported(): boolean;
  isChatChannelEstablished(): boolean;

  sendMessageWithChatChannel(msg: string, users: Array<string>): void;
}

export interface ConferenceManager {}
