
export interface EnterpriseInfo {
  uid: string,
  name: string,
  number: string,
  domain: string,
  realm: string,
  area: string,
  country: string,
  zone: string,

  frozen: boolean,
  slot: number,
  status: number,
  subtype: number,
}

export interface AccountInfo {
  uid: string,
  number: string,
  fullNumber: string,
  name: string,
  namePinyin: string,
  groupInfo: string,
  type: number,
  token: string,

  meetnow: boolean,
}

export interface Bootstrap {
  server: string,
  username: string,
  password: string,

  authenticate(): Array<AccountInfo>,
}
