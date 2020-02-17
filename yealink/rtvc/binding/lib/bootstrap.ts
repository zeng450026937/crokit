
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

export interface AccountInfo {
  id: string;
  uid: string;
  number: string;
  fullNumber: string;
  name: string;
  namePinyin: string;
  groupInfo: string;
  token: string;
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
  phonebook_version: string;
  phonebook_support: Array<string>;
  schedule_version: string;
  schedule_support: Array<string>;
  build: string;
  version: string;
  web_host: string;
  service_account: string;
  experience_account: string;
}

export interface Connector {
}

export interface Bootstrap {
  new(clientId: string);

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
