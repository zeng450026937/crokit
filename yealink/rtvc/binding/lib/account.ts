import { Call } from './call';

export interface AccountConfig {
  username: string;
  password: string;
  domain: string;
  language: string;
  // for internal use
  // all these options below are optional
  // discussion needed -> should we list them for debugging purpose ?
  ha1: string | null;
  authorizationUser: string | null;
  displayName: string | null;
  sessionTimers: number | null;
  sessionTimersRefreshMethod: 'update' | 'invite' | null
  noAnswerTimeout: number | null;
  registerExpires: number | null;
  registrarServer: string | null;
  clientInfo: string | null;
  contentEncoding: boolean | null;
  acceptEncoding: Array<string> | null;
  // TODO
  // proxy address ?
}

export interface Account {
  // TODO
  // add disconnect/connect error event
  //
  workspaceFolder(): string;
  setWorkspaceFolder(path: string | null): void;

  username(): string;
  setUsername(username: string): void;

  password(): string;
  setPassword(password: string): void;

  domain(): string;
  setDomain(domain: string): void;

  // store some custom data/setting
  // also it can be used for internal debug,
  // as it should change the account's config as well.
  set(key: string): void;
  get(key: string): any;

  // register account so it can be founded by server
  register(): void;
  unregister(): void;

  isRegistered(): boolean;

  // call someone or join a conference
  call(target: string, options: any): Call;
  // send sms message to someone
  sendMessage(): void;
}
