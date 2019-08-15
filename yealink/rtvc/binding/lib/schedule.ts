import { EventEmitter } from 'events';

export enum ScheduleItemProfile {
  kDefault,
  kSeminar,
  kEducation,
}
export enum ScheduleRecurrence {
  kNone,
  kDaily,
  kWeekly,
  kMonthly,
  kMonthlyNTH,
  kYearly,
  kYearlyNTH,
}
export enum ScheduleRecurrenceDaily {
  kNone,
  kEveryFewDays,
  kWorkingDay,
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

export interface ScheduleItemDetail {}

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

  readonly rooms: Array<string>,

  readonly recurrenceType: ScheduleRecurrence,
  readonly recurrenceDailyType: ScheduleRecurrenceDaily,
  readonly recurrenceInterval: number,
  readonly recurrenceStartDate: number,
  readonly recurrenceEndDate: number,
  readonly recurrenceCount: number,

  readonly dayOfWeek: string,
  readonly dayOfWeekIndex: number,
  readonly dayOfMonth: number,
  readonly dayOfMonthIndex: number,
}

export interface ScheduleConfig {
  connector: unknown,
  server: string,
}

export interface Schedule extends EventEmitter {
  new(config: ScheduleConfig);

  emit(event: string | symbol, ...args: any[]): boolean;
  on(event: string, listener: (...args: any[]) => void): this;

  on(event: 'updated', listener: () => void): this;

  fetch(startTime: Date, endTime: Date): Array<ScheduleItem>;
}
