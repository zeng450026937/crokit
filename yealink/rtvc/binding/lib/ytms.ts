
import { EventEmitter } from 'events';

export interface TerminalInfo {
  name: string;
  type: string;
  category: string;
  model: string;
  platform: string;
  version: string;
  arch: string;
  updateChannel: string;
  customId: string;
  configId: string;
  remarks: string;
  deviceModel: string;
  deviceResolution: string;
  deviceOs: string;
  deviceIp: string;
  deviceMac: string;
  deviceHostname: string;
  deviceCpu: string;
  deviceMemory: string;
  account: string;
  displayName: string;
  serverType: string;
  serverAddress: string;
  serverDomain: string;
  serverOutbound: string;
  registerStatus: string;
  enterpriseDomain: string;
  enterpriseId: string;
  enterpriseName: string;
}

export interface AlarmInfo {
  filePath: string;
  code: string;
  name: string;
  type: string;
  level: string;
  desc: string;
}

export interface FeedbackInfo {
  title: string;
  content: string;
  category: string;
  contact: string;
  filePath: string;
  imagePath: string;
  videoPath: string;
}

export interface PackageInfo {
  version: string;
  date: string;
  note: string;
  name: string;
  url: string;
  md5: string;
  size: number;
  forceUpdate: boolean;
}

export interface ConfigurationInfo {
  id: string;
  name: string;
  url: string;
  md5: string;
}

export interface DownloadInfo {
  url: string;
  path: string;
  fileName: string;
}

export interface UploadLogInfo {
  sessionId: string;
  filePath: string;
}

export interface NetCaptureInfo {
  path: string;
  deviceId: string;
  sessionId: string;
}

export interface NetCaptureStatus {
  status: string;
  sessionId: string;
}

export interface EventInfo {
  code: string;
  name: string;
  network: string;
  isp: string;
}

export interface YTMS extends EventEmitter {
  new(clientId: string);

  server: string;

  emit(event: string | symbol, ...args: any[]): boolean;
  on(event: string, listener: (...args: any[]) => void): this;

  on(event: 'reboot', listener: () => void): this;
  on(event: 'pushPacket', listener: () => void): this;
  on(event: 'pushConfig', listener: () => void): this;
  on(event: 'message', listener: () => void): this;
  on(event: 'uploadLog', listener: () => void): this;
  on(event: 'uploadConfig', listener: () => void): this;
  on(event: 'startCapture', listener: () => void): this;
  on(event: 'stopCapture', listener: () => void): this;
  on(event: 'reregiste', listener: () => void): this;

  start(): Promise<number>,
  update(params: TerminalInfo): Promise<number>,

  uploadAlarm(params: AlarmInfo): Promise<number>,
  uploadFeedBack(params: FeedbackInfo): Promise<number>,
  uploadEvent(params: EventInfo): Promise<number>,
  uploadConfig(params: string): Promise<number>,
  uploadLog(params: UploadLogInfo): Promise<number>,

  getPackagesInfo(): Promise<PackageInfo>,
  getConfigFileInfo(): Promise<ConfigurationInfo>,

  downloadFile(params: DownloadInfo): Promise<number>,

  getCaptureDevice(): Array<string>;
  startCapture(params: NetCaptureInfo): Promise<number>,
  stopCapture(params: string): Promise<number>,

  uploadPacket(params: NetCaptureInfo): Promise<number>,
  reportSessionStatus(params: NetCaptureStatus): Promise<number>,
}
