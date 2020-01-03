#ifndef YEALINK_RTVC_API_SCHEDULE_ITEM_H_
#define YEALINK_RTVC_API_SCHEDULE_ITEM_H_

#include <string>
#include <vector>

namespace rtvc {

enum class ScheduleItemProfile {
  kInvalid,
  kDefault,
  kSeminar,
  kEducation,
};

enum class ScheduleRecurrenceType {
  kNone,
  kDaily,
  kWeekly,
  kMonthly,
  kMonthlyNTH,
  kYearly,
  kYearlyNTH,
};

enum class ScheduleRecurrenceDailyType {
  kNone,
  kEach,
  kWeekday,
};

enum class ScheduleRecurrenceRangeType {
  kForever,
  kTimes,
  kUntil,
};

struct ScheduleRecurrence {
  ScheduleRecurrenceType type;
  ScheduleRecurrenceDailyType dailyType;
  ScheduleRecurrenceRangeType rangeType;
  int64_t interval;
  int64_t startDate;
  int64_t endDate;
  int64_t count;
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
  int64_t utcOffset;
  std::string utcOffsetName;
  std::vector<ScheduleTimeZoneRule> rule;
};

enum class ScheduleMemberRole {
  kInvalid,
  kOrganizer,
  kPresenter,
  kPaticipant,
  kCastViewer,
};

enum class ScheduleMemberType {
  kInvalid,
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

enum class ScheduleRTMPLimitType {
  kAll,
  kPassword,
};

struct ScheduleRTMP {
  bool autoRecord;
  std::string url;
  std::string password;
  std::string logoUrl;
  ScheduleRTMPLimitType limitType;
};

struct ScheduleItemDetail {
  std::string remark;
  std::string share_link;
  ScheduleMember organizer;
  std::vector<ScheduleMember> participants;
  std::vector<ScheduleRoom> rooms;
  ScheduleRTMP rtmp;
};

struct ScheduleItem {
  std::string planId;
  int64_t sequence;

  ScheduleItemProfile profile;
  std::string subject;
  std::string organizer;

  std::string timezoneId;
  ScheduleTimeZone timezone;

  int64_t aheadTime;
  int64_t startTime;
  int64_t endTime;

  std::string confNum;
  std::string confPwd;
  bool isRTMP;

  std::vector<std::string> roomNames;

  ScheduleRecurrence recurrence;

  std::vector<int> dayOfWeek;
  int64_t dayOfWeekIndex;
  int64_t dayOfMonth;
  int64_t monthOfYear;
};

enum class ScheduleExtensionType { kInvalid, kRTMP };

enum class ScheduleConfigCreateType {
  kInvalid,
  kAdmin,
  kPersonal,
  kEnterprise,
};

enum class ScheduleVideoResolutionLimit {
  kInvalid,
  k1080P,
  k720P,
};

enum class ScheduleTextNotificationMode {
  kInvalid,
  kClose,
  kAttendee,
  kAuthenticated,
  kAll,
};

enum class ScheduleVoicePromptMode {
  kInvalid,
  kAttendee,
  kAuthenticated,
  kAll,
};

struct SchedulePlanConfig {
  int32_t bizCode;

  ScheduleConfigCreateType createType;
  ScheduleVideoResolutionLimit maxVideoResolutionLimit;
  bool enableMaxSecondaryFlowResolutionLimit;
  bool enableDeviceManage;
  bool enableCooperation;

  bool enableInspect;
  bool enableSfb;
  bool enableTeachingProfile;
  bool enableOpenApi;
  int32_t maxScheduledConfDuration;

  int32_t maxScheduledConfStartTime;
  int32_t maxRecurrenceConfAmount;
  int32_t maxRecurrenceConfEndTime;
  int32_t maxRecurrenceConfRemarkLength;
  int32_t maxRecurrenceConfParticipantAmount;

  bool enableJoinAutoMute;
  ScheduleTextNotificationMode textNotificationMode;
  ScheduleVoicePromptMode voicePromptMode;
  int32_t forwardMeetingTime;
  std::string meetNowPassword;

  std::string scheduledPassword;
  bool enableMeetNowPassword;
  bool enableScheduledPassword;
  bool enableLoginOpt;
  bool enableDnd;

  bool enableChatByWebrtc;
  bool enableAutoRecord;
  int32_t maxConferenceTime;
};

enum class ScheduleServiceAbility {
  kInvalid,
  kTraversal,
  kHardwarePort,
  kSoftwarePort,
  kVmr,
  kSeminar,
  kThirdParty,
  kPSTN,
  kCloudStorage,
  kRTMP,
};

struct ScheduleServiceStatus {
  ScheduleServiceAbility type;
  bool status;
  ScheduleServiceStatus()
      : type(ScheduleServiceAbility::kInvalid), status(false) {}
};

struct ScheduleServiceResponse {
  int32_t bizCode;
  std::vector<ScheduleServiceStatus> statusList;
  ScheduleServiceResponse() : bizCode(0) {}
};

struct SchedulePlanInfo {
  ScheduleItemProfile profile;
  std::string subject;
  std::string zoneId;
  std::string startDate;
  std::string startTime;
  int32_t durationHour;
  int32_t durationMinute;
  ScheduleRecurrenceType recurrenceType;
  int32_t interval;
  int32_t dayOfWeek;
  std::string rangeEndDate;
  std::string remark;
  std::string identifier;
  ScheduleMemberType memberType;
  ScheduleMemberRole roleType;
  ScheduleExtensionType extensionType;
  std::string rtmpLogoFileName;
  ScheduleRTMPLimitType rtmpWatchLimitType;
  std::string rtmpWatchPwd;
  bool enableAutoRecord;
};

/*
class ScheduleItem {
 public:
  virtual std::string planId() = 0;
  virtual int64_t sequence() = 0;

  virtual ScheduleItemProfile profile() = 0;
  virtual std::string subject() = 0;
  virtual std::string organizer() = 0;

  virtual std::string timezoneId() = 0;
  virtual ScheduleTimeZone timezone() = 0;

  virtual int64_t aheadTime() = 0;
  virtual int64_t startTime() = 0;
  virtual int64_t endTime() = 0;

  virtual std::string confNum() = 0;
  virtual std::string confPwd() = 0;
  virtual bool isRTMP() = 0;

  virtual std::vector<std::string> rooms() = 0;

  virtual ScheduleRecurrence recurrence() = 0;

  virtual std::vector<int> dayOfWeek() = 0;
  virtual int64_t dayOfWeekIndex() = 0;
  virtual int64_t dayOfMonth() = 0;
  virtual int64_t monthOfYear() = 0;

  virtual ScheduleItemDetail GetDetail() = 0;

 protected:
  virtual ~ScheduleItem() = default;
};
*/

}  // namespace rtvc

#endif  // YEALINK_RTVC_API_SCHEDULE_ITEM_H_
