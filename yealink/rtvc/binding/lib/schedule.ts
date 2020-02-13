import { EventEmitter } from 'events';
import { Connector } from './bootstrap';

export enum ScheduleItemProfile {
  kDefault,
  kSeminar,
  kEducation,
}

export enum ScheduleRecurrence {
  kNone = 'kNone',
  kDaily = 'kDaily',
  kWeekly = 'kWeekly',
  kMonthly = 'kMonthly',
  kMonthlyNTH = 'kMonthlyNTH',
  kYearly = 'kYearly',
  kYearlyNTH = 'kYearlyNTH',
}

export enum ScheduleRecurrenceDaily {
  kNone = 'kNone',
  kEach = 'kEach',
  kWeekday = 'kWeekday',
}

export enum ScheduleRecurrenceRange {
  kForever = 'kForever',
  kTimes = 'kTimes',
  kUntil = 'kUntil',
};

export enum ScheduleMemberRole {
  kInvalid = 'kInvalid',
  kOrganizer = 'kOrganizer',
  kPresenter = 'kPresenter',
  kPaticipant = 'kPaticipant',
  kCastViewer = 'kCastViewer',
};

export enum ScheduleMemberType {
  kInvalid = 'kInvalid',
  kInternal = 'kInternal',
  kExternal = 'kExternal',
};

export enum ScheduleRTMPLimitType {
  kAll = 'kAll',
  kPassword = 'kPassword',
};

export enum ScheduleMemberCreateType {
  kInvalid = 'invalid',
  kAdmin = 'admin',
  kPersonal = 'personal',
  kEnterprise = 'enterprise',
};

export enum ScheduleResolutionType {
  k720P = '720P',
  k1080P = '1080P',
};

export enum SchedulePromptType {
  kInvalid = 'invalid',
  kClose = 'close',
  kAttendee = 'attendee',
  kAuthenticated = 'authenticated',
  kAll = 'all',
};

export interface ScheduleRecurrenceInfo {
  readonly recurrenceType: ScheduleRecurrence,
  readonly recurrenceDailyType: ScheduleRecurrenceDaily,
  readonly recurrenceRangeType: ScheduleRecurrenceRange,
  readonly recurrenceInterval: number,
  readonly recurrenceStartDate: number,
  readonly recurrenceEndDate: number,
  readonly recurrenceCount: number,
}

export interface ScheduleDaylightStrategy {
  readonly isFixedDateRule: boolean,
  readonly day: string,
  readonly month: string,
  readonly week: string,
  readonly dayOfWeek: string,
  readonly timeOfDay: string,
}
export interface ScheduleTimeZoneRule {
  readonly startDate: string,
  readonly endDate: string,
  readonly daylightDelta: string,
  readonly daylightStrategyStart: ScheduleDaylightStrategy,
  readonly daylightStrategyEnd: ScheduleDaylightStrategy,
}
export interface ScheduleTimeZone {
  readonly id: string,
  readonly cnName: string,
  readonly usName: string,
  readonly utcOffset: number,
  readonly utcOffsetName: string,
  readonly rule: Array<ScheduleTimeZoneRule>,
}

export interface ScheduleMember {
  readonly id: string;
  readonly name: string;
  readonly number: string;
  readonly role: ScheduleMemberRole;
  readonly type: ScheduleMemberType;
}

export interface ScheduleRoom {
  readonly id: string;
  readonly name: string;
};

export interface ScheduleRTMP {
  readonly autoRecord: boolean;
  readonly url: string;
  readonly password: string;
  readonly logoUrl: string;
  readonly limitType: ScheduleMemberType;
};

export interface ScheduleItemDetail {
  readonly remark: string;
  readonly shareLink: string;
  readonly organizer: ScheduleMember;
  readonly participants: Array<ScheduleMember>;
  readonly rooms: Array<ScheduleRoom>;
  readonly rtmp: ScheduleRTMP;
};

export interface ScheduleItem {
  readonly planId: string,
  readonly sequence: number,
  readonly profile: ScheduleItemProfile,
  readonly subject: string,
  readonly organizer: string,
  readonly timezoneId: string,
  readonly timezone: ScheduleTimeZone,
  readonly aheadTime: number,
  readonly startTime: number,
  readonly endTime: number,
  readonly confNum: string,
  readonly confPwd: string,
  readonly isRTMP: boolean,
  readonly roomNames: Array<string>,
  readonly recurrence: ScheduleRecurrenceInfo;
  readonly dayOfWeek: string,
  readonly dayOfWeekIndex: number,
  readonly dayOfMonth: number,
  readonly monthOfYear: number,

  getDetail(): Promise<ScheduleItemDetail>;
  getMailTemplate(): Promise<string>;
  editSerial(infos: SchedulePlan): Promise<number>;
  editSingle(infos: SchedulePlan): Promise<number>;
  deleteSingle(): Promise<number>;
  deleteSerial(): Promise<number>;
}

export interface ScheduleConfig {
  connector: Connector,
  server: string,
}

export interface SchedulePlanMember {
  identifier: string,
  memberType: ScheduleMemberType,
  roleType: ScheduleMemberRole,
}

export interface SchedulePlan {
  profile: ScheduleItemProfile,
  subject: string,
  zoneId: string,
  startDate: string,
  startTime: string,
  durationHour: number,
  durationMinute: number,
  recurrenceType: ScheduleRecurrence,
  interval: number,
  dayOfWeek: number,
  rangeEndDate: string,
  remark: string,
  users: Array<SchedulePlanMember>
  extensionType: ScheduleRTMPLimitType,
  rtmpLogoFileName: string,
  rtmpWatchLimitType: ScheduleRTMPLimitType,
  rtmpWatchPwd: string,
  enableAutoRecord: boolean,
}

export interface SchedulePlanConfig {
  readonly bizCode: number;
  readonly createType: ScheduleMemberCreateType;
  readonly maxVideoResolutionLimit: ScheduleResolutionType;
  readonly enableMaxSecondaryFlowResolutionLimit: boolean;
  readonly enableDeviceManage: boolean;
  readonly enableCooperation: boolean;

  readonly enableInspect: boolean;
  readonly enableSfb: boolean;
  readonly enableTeachingProfile: boolean;
  readonly enableOpenApi: boolean;
  readonly maxScheduledConfDuration: number;

  readonly maxScheduledConfStartTime: number;
  readonly maxRecurrenceConfAmount: number;
  readonly maxRecurrenceConfEndTime: number;
  readonly maxRecurrenceConfRemarkLength: number;
  readonly maxRecurrenceConfParticipantAmount: number;

  readonly enableJoinAutoMute: boolean;
  readonly textNotificationMode: SchedulePromptType;
  readonly forwardMeetingTime: number;
  readonly meetNowPassword: string;

  readonly scheduledPassword: string;
  readonly enableMeetNowPassword: boolean;
  readonly enableScheduledPassword: boolean;
  readonly enableLoginOpt: boolean;
  readonly enableDnd: boolean;

  readonly enableChatByWebrtc: boolean;
  readonly enableAutoRecord: boolean;
  readonly maxConferenceTime: number;
}

export enum ScheduleServiceAbility {
  kInvalid = 'invalid',
  kTraversal = 'traversal',
  kHardwarePort = 'hardwarePort',
  kSoftwarePort = 'softwarePort',
  kVmr = 'vmr',
  kSeminar = 'seminar',
  kThirdParty = 'thirdParty',
  kPSTN = 'PSTN',
  kCloudStorage = 'cloudStorage',
  kRTMP = 'RTMP',
};

export interface ScheduleServiceStatus {
  readonly type: ScheduleServiceAbility;
  readonly status: boolean;
}

export interface ScheduleServiceResponse {
  readonly bizCode: number;
  readonly statusList: Array<ScheduleServiceStatus>
}

export interface Schedule extends EventEmitter {
  new(config: ScheduleConfig);

  emit(event: string | symbol, ...args: any[]): boolean;
  on(event: string, listener: (...args: any[]) => void): this;

  on(event: 'updated', listener: () => void): this;

  sync(startTime: Date, endTime: Date): Promise<void>;
  fetch(startTime: Date, endTime: Date): Promise<Array<ScheduleItem>>;

  addSchedulePlan(plan: SchedulePlan): Promise<void>;
  editSerialSchedulePlan(id: string, plan: SchedulePlan): Promise<void>;
  editSingleSchedulePlan(id: string, sequence: number, plan: SchedulePlan): Promise<void>;
  deleteSerialSchedulePlan(id: string): Promise<void>;
  deleteSingleSchedulePlan(id: string, sequence: number): Promise<void>;
  getScheduleConfig(): Promise<SchedulePlanConfig>;
  getServiceAbility(abilities: Array<ScheduleServiceAbility>): Promise<ScheduleServiceResponse>;
  getScheduleByPlanId(id: string): Promise<Array<ScheduleItem>>;
}
