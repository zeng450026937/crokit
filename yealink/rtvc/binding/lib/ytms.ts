
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
  enterprise_domain: string;
  enterprise_id: string;
  enterprise_name: string;
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

export interface YTMS {
  server: string,

  start(): void,
  update(params: TerminalInfo): void,

  uploadAlarm(params: AlarmInfo): void,
  uploadFeedBack(params: FeedbackInfo): void,

  getPackagesInfo(): PackageInfo,
  getConfigFileInfo(): ConfigurationInfo,
}
