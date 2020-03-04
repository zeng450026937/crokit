import { EventEmitter } from 'events';
import { Connector } from './bootstrap';

export enum ContactNodeType {
  kDepartment = 'kDepartment',
  kStaff = 'kStaff',
  kDevice = 'kDevice',
  kVMR = 'kVMR',
  kThirdParty = 'kThirdParty',
  kRoom = 'kRoom',
  kEnterprise = 'kEnterprise',
}

export interface ContactNode {
  uid: string;
  type: ContactNodeType;
  parentId: Array<string>;
  childCounts: number;

  name: string;
  i18nName: string;
  pinyin: string;
  pinyinAbbr: string;
  email: string;
  phone: string;
  mobile: string;
  number: string;
  fullNumber: string;
}

export interface ContactConfig {
  workspaceFolder?: string,
  databaseName?: string,
}

export interface LocalContactConfig extends ContactConfig { }

export interface LocalContact {
  new(config: LocalContactConfig);

  create(params: {name: string, indexed: string}): number;
  add(params: {name: string, indexed: string}): number;
  remove(uid: number): boolean;
  update(uid: number, params: {name: string, indexed: string}): boolean;
  modify(uid: number, params: {name: string, indexed: string}): boolean;
  search(key: string, offset: number, limit: number): Array<{uid: number, name:string, indexed: string}>;
  searchWith(key: string, val: string, offset: number, limit: number): Array<{uid: number, name:string, indexed: string}>;
  find(key: string, val: string, offset: number, limit: number): Array<{uid: number, name:string, indexed: string}>;
  findByName(name: string, offset: number, limit: number): Array<{uid: number, name:string, indexed: string}>;
  getContact(nodeId: string): {uid: number, name:string, indexed: string};
  getList(offset: number, limit: number): Array<{uid: number, name:string, indexed: string}>;
}

export interface CloudContactConfig extends ContactConfig {
  connector: Connector,
  server: string,
}

declare class CloudContact extends EventEmitter {
  constructor(config: CloudContactConfig);

  emit(event: string | symbol, ...args: any[]): boolean;
  on(event: string, listener: (...args: any[]) => void): this;

  on(event: 'changed', listener: () => void): this;

  readonly synced: boolean;
  readonly loadMode: any;
  readonly rootId: string;

  sync(): Promise<void>;
  search(key: string, offset: number, limit: number): Promise<Array<ContactNode>>;

  getNode(nodeId: string): ContactNode;
  getNodeChild(nodeId: string, recursive: boolean): Array<ContactNode>;
  getNodeByNumber(number: string): ContactNode;
}

export default CloudContact;
