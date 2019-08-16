#ifndef YEALINK_RTVC_API_SCHEDULE_ITEM_H_
#define YEALINK_RTVC_API_SCHEDULE_ITEM_H_

#include <string>
#include <vector>

namespace yealink {

namespace rtvc {

enum class ScheduleItemProfile {
  kDefault,
  kSeminar,
  kEducation,
};

enum class ScheduleRecurrence {
  kNone,
  kDaily,
  kWeekly,
  kMonthly,
  kMonthlyNTH,
  kYearly,
  kYearlyNTH,
};

enum class ScheduleRecurrenceDaily {
  kNone,
  kEveryFewDays,
  kWorkingDay,
};

struct ScheduleDaylightStrategy {
  bool isFixedDateRule;
  std::string day;
  std::string month;
  std::string week;
  std::string dayOfWeek;
  std::string timeOfDay;
};

struct ScheduleTimeZoneRule {
  std::string startDate;
  std::string endDate;
  std::string daylightDelta;
  ScheduleDaylightStrategy daylightStrategyStart;
  ScheduleDaylightStrategy daylightStrategyEnd;
};

struct ScheduleTimeZone {
  std::string id;
  std::string cnName;
  std::string usName;
  int utcOffset;
  std::string utcOffsetName;
  std::vector<ScheduleTimeZoneRule> rule;
};

enum class ScheduleMemberRole {
  kOrganizer,
  kPresenter,
  kPaticipant,
  kCastViewer,
};

enum class ScheduleMemberType {
  kInternal,
  kExternal,
};

struct ScheduleMember {
  std::string id;
  std::string name;
  std::string number;
  ScheduleMemberRole role;
  ScheduleMemberType type;
};

struct ScheduleRoom {
  std::string id;
  std::string name;
};

struct ScheduleItemDetail {
  std::string remark;
  ScheduleMember organizer;
  std::vector<ScheduleMember> participants;
  std::vector<ScheduleRoom> rooms;
};

struct ScheduleItem {
  std::string planId;
  int sequence;

  ScheduleItemProfile profile;
  std::string subject;
  std::string organizer;

  std::string timezoneId;
  ScheduleTimeZone timezone;

  int aheadTime;
  int startTime;
  int endTime;

  std::string confNum;
  std::string confPwd;
  bool isRTMP;

  std::vector<std::string> rooms;

  ScheduleRecurrence recurrenceType;
  ScheduleRecurrenceDaily recurrenceDailyType;
  int recurrenceInterval;
  int recurrenceStartDate;
  int recurrenceEndDate;
  int recurrenceCount;

  std::string dayOfWeek;
  int dayOfWeekIndex;
  int dayOfMonth;
  int dayOfMonthIndex;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_SCHEDULE_ITEM_H_
