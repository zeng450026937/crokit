import { EventEmitter } from 'events';

export enum ContactNodeType {
  kDepartment,
  kStaff,
  kDevice,
  kVMR,
  kThirdParty,
}

export interface ContactNode {
  readonly nodeId: string;
  readonly nodeType: ContactNodeType;
  // one node can have many parent node
  readonly parentId: Array<string>;
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

export interface Contact extends EventEmitter {
  on(event: 'nodeUpdated', listener: () => void): this;
}
