import { EventEmitter } from 'events';

export enum ContactNodeType {
  kDepartment,
  kStaff,
  kDevice,
  kVMR,
  kThirdParty,
  kRoom,
  kEnterprise,
}

export interface ContactNode {
  readonly nodeId: string;
  readonly nodeType: ContactNodeType;
  // one node can have many parent node
  readonly parentId: Array<string> | null;
  // child node counts(recursive)
  readonly childCounts: number;

  readonly name: string;
  readonly i18nName: string;
  readonly pinyin: string;
  readonly pinyinAbbr: string;
  readonly email: string;
  readonly number: string;
  readonly extensionNum: string;
}

export interface ContactConfig {
  connector: unknown,
  server: string,
  workspaceFolder?: string,
  databaseName?: string,
}

export interface Contact extends EventEmitter {
  new(config: ContactConfig);

  on(event: 'updated', listener: () => void): this;

  sync(): void;

  getNode(nodeId: string): ContactNode;
  getNodeChild(nodeId: string): Array<ContactNode>;
}

export interface LocalContactConfig {
  workspaceFolder?: string,
  databaseName?: string,
}

// CRUD
export interface LocalContact {
  new(config: LocalContactConfig);

  create(): void;
  remove(): void;
  update(): void;
  search(): void;
  // alias for create
  add(): void;
  // alias for update
  modify(): void;
  // alias for search
  find(): void;
}
