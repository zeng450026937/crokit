import { Call } from './call';
import { Connector } from './bootstrap';

export interface AccountConfig {
  username: string;
  password: string;
  ha1: string;
  domain: string;
  displayName: string | null;
  userAgent: string | null;
  clientInfo: string | null;
  sitename: string | null
  tlsPort: number | null;
  tcpPort: number | null;
  udpPort: number | null;
  ipv4Only: boolean | null;
  ipv6Only: boolean | null;
  proxyServer: string | null;
  proxyPort: number | null;
  language: string | null;
  connector: Connector | null;
  uuid: string | null;
}

export interface UserAgent {
  new(config: AccountConfig);

  workspaceFolder: string;
  username: string;
  password: string;
  ha1: string;
  domain: string;
  proxyServer: string;
  proxyPort: number;
  language: string;

  readonly running: boolean;
  readonly registered: boolean;

  set(key: string, value: any): void;
  get(key: string): any;

  start(): void;
  stop(): void;
  register(): Promise<void>;
  unregister(): void;

  setConnector(handler: Connector): void;
}
