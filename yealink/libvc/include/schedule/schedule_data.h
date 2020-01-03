/*
 * @file schedule_data.h
 * @date 2019-04-10
 *
 * @brief 
 */
#ifndef __SCHEDULE_DATA_H__
#define __SCHEDULE_DATA_H__
#include <cstdint>
#include "components/base/simplelib/simple_lib.h"

namespace yealink
{
enum ScheduleResult
{
    SCHEDULE_SUCCESS,
    SCHEDULE_INVALID_PARAMS,
    SCHEDULE_HTTP_FAILURE,
    SCHEDULE_INVALID,
};

enum ScheduleItemProfile
{
    SCHEDULE_ITEM_PROFILE_INVALID,
    SCHEDULE_ITEM_PROFILE_DEFAULT,
    SCHEDULE_ITEM_PROFILE_EDUCATION,
    SCHEDULE_ITEM_PROFILE_SEMINAR
};

enum ScheduleRecurrenceType
{
    SCHEDULE_RECURRENCE_TYPE_INVALID,
    SCHEDULE_RECURRENCE_TYPE_NORMAL,
    SCHEDULE_RECURRENCE_TYPE_DAILY,
    SCHEDULE_RECURRENCE_TYPE_WEEKLY,
    SCHEDULE_RECURRENCE_TYPE_MONTHLY,
    SCHEDULE_RECURRENCE_TYPE_MONTH_NTH,
    SCHEDULE_RECURRENCE_TYPE_YEARLY,
    SCHEDULE_RECURRENCE_TYPE_YEAR_NTH
};

enum ScheduleDailyType
{
    SCHEDULE_DAILY_TYPE_INVALID,
    SCHEDULE_DAILY_TYPE_EACH,
    SCHEDULE_DAILY_TYPE_WEEKDAY
};

enum ScheduleRangeType
{
    SCHEDULE_RANGE_TYPE_INVALID,
    SCHEDULE_RANGE_TYPE_FOREVER,
    SCHEDULE_RANGE_TYPE_TIMES,
    SCHEDULE_RANGE_TYPE_UNTIL
};

enum ScheduleMemberRole
{
    SCHEDULE_MEMBER_ROLE_INVALID,
    SCHEDULE_MEMBER_ROLE_ORGANIZER,
    SCHEDULE_MEMBER_ROLE_PRESENTER,
    SCHEDULE_MEMBER_ROLE_PARTICIPANT,
    SCHEDULE_MEMBER_ROLE_CAST_VIEWER
};

enum ScheduleMemberType
{
    SCHEDULE_MEMBER_TYPE_INVALID,
    SCHEDULE_MEMBER_TYPE_INSIDER,
    SCHEDULE_MEMBER_TYPE_OUTSIDER
};

struct ScheduleDaylightStrategyInfo
{
    ScheduleDaylightStrategyInfo()
        : isFixedDateRule(false)
    {
    }

    bool isFixedDateRule;
    SStringA day;
    SStringA month;
    SStringA week;
    SStringA dayOfWeek;
    SStringA timeOfDay;
};

struct ScheduleTimeZoneRule
{
    SStringA dateStart;
    SStringA dateEnd;
    SStringA daylightDelta;
    ScheduleDaylightStrategyInfo daylightStrategyStart;
    ScheduleDaylightStrategyInfo daylightStrategyEnd;
};

struct ScheduleTimeZoneConfig
{
    ScheduleTimeZoneConfig()
        : utcOffset(-1)
    {
    }

    SStringA zoneId;
    int64_t utcOffset;
    SStringA offsetDisplayName;
    SStringA cnZoneName;
    SStringA usZoneName;
    Array<ScheduleTimeZoneRule> rule;
};
struct ScheduleSimpleInfo
{
    ScheduleSimpleInfo()
        : sequence(-1)
        , profile(SCHEDULE_ITEM_PROFILE_INVALID)
        , aheadTime(-1)
        , startDateTime(-1)
        , endDateTime(-1)
        , recurrenceType(SCHEDULE_RECURRENCE_TYPE_INVALID)
        , dailyType(SCHEDULE_DAILY_TYPE_INVALID)
        , recurrenceInterval(-1)
        , dayOfMonth(-1)
        , monthOfYear(-1)
        , rangeStartDate(-1)
        , rangeEndDate(-1)
        , rangeType(SCHEDULE_RANGE_TYPE_INVALID)
        , rangeOccurrences(-1)
        , isRtmp(false)
    {
    }

    SStringA planId;
    int64_t sequence;
    ScheduleItemProfile profile;
    SStringA subject;
    SStringA organizerName;

    SStringA zoneId;
    ScheduleTimeZoneConfig timeZoneConfig;
    int64_t aheadTime;
    int64_t startDateTime;
    int64_t endDateTime;

    SStringA conferenceNo;
    SStringA conferencePwd;
    Array<SStringA> roomNames;
    ScheduleRecurrenceType recurrenceType;
    ScheduleDailyType dailyType;

    int32_t recurrenceInterval;
    Array<int32_t> dayOfWeek;
    int32_t dayOfMonth;
    int32_t monthOfYear;
    int64_t rangeStartDate;

    int64_t rangeEndDate;
    ScheduleRangeType rangeType;
    int32_t rangeOccurrences;
    bool isRtmp;
};

struct ScheduleMemberInfo
{
    ScheduleMemberInfo()
        : role(SCHEDULE_MEMBER_ROLE_INVALID)
        , type(SCHEDULE_MEMBER_TYPE_INVALID)
    {
    }

    SStringA identifier;
    ScheduleMemberRole role;
    ScheduleMemberType type;
    SStringA showName;
    SStringA extension;
};

struct ScheduleRoomInfo
{
    SStringA roomId;
    SStringA name;
};

enum ScheduleRtmpWatchLimitType
{
    SCHEDULE_WATCH_TYPE_INVALID,
    SCHEDULE_WATCH_TYPE_BY_ALL,
    SCHEDULE_WATCH_TYPE_BY_PASSWORD
};

struct ScheduleDetailInfo
{
    ScheduleDetailInfo()
        : bizCode(900200)
        , rtmpWatchLimitType(SCHEDULE_WATCH_TYPE_INVALID)
        , rtmpAutoRecord(false)
    {
    }

    int32_t bizCode;

    ScheduleMemberInfo organizer;
    SStringA remark;
    Array<ScheduleMemberInfo> participants;
    Array<ScheduleRoomInfo> rooms;
    SStringA rtmpLogoUrl;
    ScheduleRtmpWatchLimitType rtmpWatchLimitType;
    SStringA rtmpWatchPwd;
    bool rtmpAutoRecord;
    SStringA rtmpWatchUrl;
};

enum ScheduleExtensionType
{
    SCHEDULE_EXTENSION_TYPE_INVALID,
    SCHEDULE_EXTENSION_TYPE_RTMP
};

enum ScheduleConfigCreateType
{
    SCHEDULE_CONFIG_CREATE_TYPE_INVALID,
    /**
     * @brief 企业注册生成
     */
    SCHEDULE_CONFIG_CREATE_TYPE_ADMIN,
    /**
     * @brief 个人注册生成
     */
    SCHEDULE_CONFIG_CREATE_TYPE_PERSONAL,
    /**
     * @brief 管理员添加
     */
    SCHEDULE_CONFIG_CREATE_TYPE_ENTERPRISE
};

enum ScheduleVideoResolutionLimit
{
    SCHEDULE_VIDEO_RESOLUTION_LIMIT_INVALID,
    /**
     * @brief 最大为1080P
     */
    SCHEDULE_VIDEO_RESOLUTION_LIMIT_1080P,
    /**
     * @brief 最大为720P
     */
    SCHEDULE_VIDEO_RESOLUTION_LIMIT_720P
};

enum ScheduleTextNotificationMode
{
    SCHEDULE_TEXT_NOTIFICATION_MODE_INVALID,
    /**
     * @brief 关闭
     */
    SCHEDULE_TEXT_NOTIFICATION_MODE_CLOSE,
    /**
     * @brief 仅入会方接收提示语
     */
    SCHEDULE_TEXT_NOTIFICATION_MODE_ATTENDEE,
    /**
     * @brief 仅入会方和主持人接收提示语
     */
    SCHEDULE_TEXT_NOTIFICATION_MODE_AUTHENTICATED,
    /**
     * @brief 所有参会方接收提示语
     */
    SCHEDULE_TEXT_NOTIFICATION_MODE_ALL
};

enum ScheduleVoicePromptMode
{
    SCHEDULE_VOICE_PROMPT_MODE_INVALID,
    /**
     * @brief 仅入会方接收提示音
     */
    SCHEDULE_VOICE_PROMPT_MODE_ATTENDEE,
    /**
     * @brief 仅入会方和主持人接收提示音
     */
    SCHEDULE_VOICE_PROMPT_MODE_AUTHENTICATED,
    /**
     * @brief 所有参会方接收提示音
     */
    SCHEDULE_VOICE_PROMPT_MODE_ALL
};

struct SchedulePlanConfig
{
    SchedulePlanConfig()
        : bizCode(900599)
        , createType(SCHEDULE_CONFIG_CREATE_TYPE_INVALID)
        , maxVideoResolutionLimit(SCHEDULE_VIDEO_RESOLUTION_LIMIT_INVALID)
        , enableMaxSecondaryFlowResolutionLimit(false)
        , enableDeviceManage(false)
        , enableCooperation(false)
        , enableInspect(false)
        , enableSfb(false)
        , enableTeachingProfile(false)
        , enableOpenApi(false)
        , maxScheduledConfDuration(-1)
        , maxScheduledConfStartTime(-1)
        , maxRecurrenceConfAmount(-1)
        , maxRecurrenceConfEndTime(-1)
        , maxRecurrenceConfRemarkLength(-1)
        , maxRecurrenceConfParticipantAmount(-1)
        , enableJoinAutoMute(false)
        , textNotificationMode(SCHEDULE_TEXT_NOTIFICATION_MODE_INVALID)
        , voicePromptMode(SCHEDULE_VOICE_PROMPT_MODE_INVALID)
        , forwardMeetingTime(0)
        , enableMeetNowPassword(false)
        , enableScheduledPassword(false)
        , enableLoginOpt(false)
        , enableDnd(false)
        , enableChatByWebrtc(false)
        , enableAutoRecord(false)
        , maxConferenceTime(-1)
    {
    }

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
    SStringA meetNowPassword;

    SStringA scheduledPassword;
    bool enableMeetNowPassword;
    bool enableScheduledPassword;
    bool enableLoginOpt;
    bool enableDnd;

    bool enableChatByWebrtc;
    bool enableAutoRecord;
    int32_t maxConferenceTime;
};

enum ScheduleServiceAbility
{
    SCHEDULE_SERVICE_ABILITY_INVALID,
    SCHEDULE_SERVICE_ABILITY_TRAVERSAL,
    SCHEDULE_SERVICE_ABILITY_HARDWARE_PORT,
    SCHEDULE_SERVICE_ABILITY_SOFTWARE_PORT,
    SCHEDULE_SERVICE_ABILITY_VMR,

    SCHEDULE_SERVICE_ABILITY_SEMINAR,
    SCHEDULE_SERVICE_ABILITY_THIRD_PARTY,
    SCHEDULE_SERVICE_ABILITY_PSTN,
    SCHEDULE_SERVICE_ABILITY_CLOUD_STORAGE,
    SCHEDULE_SERVICE_ABILITY_RTMP
};

struct ScheduleServiceStatus
{
    ScheduleServiceStatus()
        : type(SCHEDULE_SERVICE_ABILITY_INVALID)
        , status(false)
    {
    }

    ScheduleServiceStatus(ScheduleServiceAbility type, bool status)
        : type(type)
        , status(status)
    {
    }

    ScheduleServiceAbility type;
    bool status;
};

struct ScheduleServiceResponse
{
    ScheduleServiceResponse()
        : bizCode(900599)
    {
    }

    int32_t bizCode;
    Array<ScheduleServiceStatus> statusList;
};

} // namespace yealink

#endif // __SCHEDULE_DATA_H__
