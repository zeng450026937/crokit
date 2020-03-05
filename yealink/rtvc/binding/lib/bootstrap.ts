
export interface EnterpriseInfo {
  uid: string;
  name: string;
  number: string;
  domain: string;
  realm: string;
  area: string;
  country: string;
  zone: string;
  frozen: boolean;
  slot: number;
  status: number;
  subtype: number;
}

export interface TurnServerInfo {
  username: string;
  password: string;
}

export interface GroupInfo {
  uid: string;
  name: string;
  namePinyin: string;
}

export interface AccountInfo {
  id: string;
  uid: string;
  number: string;
  fullNumber: string;
  name: string;
  namePinyin: string;
  groupInfo: Array<GroupInfo>;
  token: string;
  mobile: string;
  email: string;
  type: number;
  meetnow: boolean;
  ha1: string;
  enterprise: EnterpriseInfo;
  turnServer: EnterpriseInfo;
}

export interface PrimaryAccountInfo {
  upgraded: boolean;
  principle: string;
  realm: string;
  type: string;
  algorithm: string;
  ha1: string;
}

export interface AuthenticateInfos {
  accountList: Array<AccountInfo>;
  primaryAccount: PrimaryAccountInfo;
}

export interface InviteInfo {
  url: string;
  applicants: number;
}

export interface SchedulerMetaInfo {
  phonebookVersion: string;
  phonebookSupport: Array<string>;
  scheduleVersion: string;
  scheduleSupport: Array<string>;
  build: string;
  version: string;
  webHost: string;
  service_account: string;
  experience_account: string;
}

export interface Connector {
}

declare class Bootstrap {
  constructor(clientId: string);

  server: string;
  username: string;
  password: string;
  debug: boolean;
  smsVerify: boolean;
  ha1: string;
  language: string;
  region: string;

  authenticate(): Promise<AuthenticateInfos>;
  getConnector(uid: string): Connector;
  pushVerifyCode(): Promise<boolean>;
  getToken(uid: string): string;
  getPartyInviteInfo(): Promise<InviteInfo>;
  getMetaInfo(url: string): Promise<SchedulerMetaInfo>;
  getServiceInfo(url: string): Promise<string>;
}

export default Bootstrap;
