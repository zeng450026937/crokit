
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

export interface EventInfo {
  code: string;
  name: string;
  network: string;
  isp: string;
}

export interface YTMS {
  server: string,

  start(): void,
  update(params: TerminalInfo): void,

  uploadAlarm(params: AlarmInfo): void,
  uploadFeedBack(params: FeedbackInfo): void,
  uploadEvent(params: EventInfo): void,
  uploadConfig(params: string): void,
  uploadLog(params: UploadLogInfo): void,

  getPackagesInfo(): PackageInfo,
  getConfigFileInfo(): ConfigurationInfo,

  downloadFile(params: DownloadInfo): void,

  startCapture(params: NetCaptureInfo): void,
  stopCapture(params: string): void,
}
