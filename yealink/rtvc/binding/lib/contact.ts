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

  getChild(recursive: boolean): Array<ContactNode>;
}

export interface ContactConfig {
  workspaceFolder?: string,
  databaseName?: string,
}

// CRUD
export interface Contact {
  new(config: ContactConfig);

  create(): void;
  remove(): void;
  update(): void;
  search(): Promise<Array<ContactNode>>;
  // alias for create
  add(): void;
  // alias for update
  modify(): void;
  // alias for search
  find(): void;
}

export interface LocalContactConfig extends ContactConfig {}

export interface LocalContact extends Contact {
  new(config: LocalContactConfig);

  // support paging acquisition
  // limit 0 to acquire all
  // acquire all by default
  getList(limit: number, offset: number): Array<ContactNode>;
}

export interface CloudContactConfig extends ContactConfig {
  connector: unknown,
  server: string,
}

export interface CloudContact extends EventEmitter, Contact {
  new(config: CloudContactConfig);

  on(event: 'updating', listener: () => void): this;
  on(event: 'updated', listener: () => void): this;
  on(event: 'changed', listener: () => void): this;

  readonly synced: boolean;
  readonly loadMode: any;

  readonly rootId: string;
  readonly selfId: string;

  sync(): Promise<void>;
  search(): Promise<Array<ContactNode>>;

  getNode(nodeId: string): ContactNode;
  getNodeChild(nodeId: string, recursive: boolean): Array<ContactNode>;
}
