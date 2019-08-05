/*
 * @file room_data.h
 * @date 2019-03-21
 * 
 * @brief 
 */

#ifndef __ROOM_DATA_H__
#define __ROOM_DATA_H__
#include "components/base/simplelib/simple_lib.h"
#include "sip_agent/sip_define.h"

namespace yealink
{
/**
 * @brief 
 */
enum ConferenceResult
{
    CONFERENCE_SUCCESS,
    CONFERENCE_INVALID_PARAMS,
    CONFERENCE_SIP_FAILURE,
    CONFERENCE_INVALID,

};

/**
 * @brief 
 */
enum ResponseState
{
    RESPONSE_SUCCESS,
    RESPONSE_FAILURE,
    RESPONSE_PENDING
};

/**
 * @brief 
 */
struct RequestResult
{
    RequestResult()
        : requestId(0)
        , requestResult(CONFERENCE_INVALID)
    {
    }
    RequestResult(int64_t id, ConferenceResult result)
        : requestId(id)
        , requestResult(result)
    {
    }
    int64_t requestId;
    ConferenceResult requestResult;
};

/**
 * @brief 
 */
struct ResponseResult
{
    enum Status
    {
        INVALID,
        SUCCESS,
        FAILURE,
        PENDING
    };
    ResponseResult()
        : sipCode(SIP_CODE_UNKNOWN)
        , requestId(0)
        , status(INVALID)
        , errorCode(0)
    {
    }

    ResponseResult(SIPCode responseSipCode, int64_t id, Status responseStatus,
                   uint32_t responseErrorCode, const char* reasonText)
        : sipCode(responseSipCode)
        , requestId(id)
        , status(responseStatus)
        , errorCode(responseErrorCode)
        , reason(reasonText)
    {
    }

    SIPCode sipCode;
    int64_t requestId;
    Status status;
    uint32_t errorCode;
    SStringA reason;
};

/**
 * @brief 
 */
struct ConferenceDescription
{
    struct Banner
    {
        enum Position
        {
            POSITION_INVALID,
            TOP,
            MEDIUM,
            BOTTOM
        };
        Banner()
            : enabled(false)
            , position(POSITION_INVALID)
        {
        }

        bool enabled;
        SStringA displayText;
        Position position;
    };
    struct DefaultRtmp
    {
        enum McuSessionType
        {
            MCU_INVALID,
            MCU_AV,
            MCU_AD,
            MCU_AVD
        };
        enum MaxVideoFs
        {
            FS_INVALID,
            FS_360P,
            FS_720P,
            FS_1080P
        };
        DefaultRtmp()
            : enabled(false)
            , mcuSessionType(MCU_INVALID)
            , maxVideoFs(FS_INVALID)
        {
        }

        bool enabled;
        SStringA displayText;
        McuSessionType mcuSessionType;
        MaxVideoFs maxVideoFs;
        SStringA webShareUrl;
    };

    struct Entry
    {
        Entry()
            : purpose(PURPOSE_INVALID)
        {
        }

        enum Purpose
        {
            PURPOSE_INVALID,
            FOCUS,
            AUDIO_VIDEO,
            APPLICATION_SHARING,
            CHAT,
            COOPSHARE
        };
        SStringA uri;
        SStringA displayText;
        Purpose purpose;
    };

    enum Profile
    {
        PROFILE_INVALID,
        CONFERENCE,
        TEACHING,
        SEMINAR
    };

    struct OrganizerInfo
    {
        SStringA displayText;
        SStringA uid;
        SStringA username;
        SStringA realm;
        SStringA phone;
        SStringA domain;
    };

    enum ConferenceType
    {
        CONFERENCE_TYPE_INVALID,
        VMN,
        VGCP,
        VGCM,
        VSC,
        VSCA
    };

    enum ConferenceNumberType
    {
        CONFERENCE_NUMBER_TYPE_INVALID,
        MEET_NOW,
        RECURRENCE,
        VMR
    };
    enum AdmissionPolicy
    {
        ADMISSION_POLICY_INVALID,
        CLOSED_AUTHENTICATED,
        OPEN_AUTHENTICATED,
        ANONYMOUS
    };
    enum AttendeeByPass
    {
        ATTENDEE_BY_PASS_INVALID,
        ATTENDEE_BY_PASS_TRUE,
        ATTENDEE_BY_PASS_FALSE
    };
    enum AutoPromote
    {
        AUTO_PROMOTE_INVALID,
        NONE,
        EVERYONE,
        COMPANY
    };

    enum RecordServerType
    {
        RECORD_SERVER_TYPE_INVALID,
        YL_RECORD,
        THIRD_PARTY,
    };

    enum RecordPrivilege
    {
        RECORD_PRIVILEGE_INVALID,
        ORGANIZER,
        PRESENTER,
        ATTENDEE
    };

    ConferenceDescription()
        : startTime(0)
        , profile(PROFILE_INVALID)
        , conferenceType(CONFERENCE_TYPE_INVALID)
        , conferenceNumberType(CONFERENCE_NUMBER_TYPE_INVALID)
        , bookStartTime(0)
        , bookExpiryTime(0)
        , maximumUserCount(0)
        , admissionPolicy(ADMISSION_POLICY_INVALID)
        , lobbyCapable(false)
        , attendeeByPass(false)
        , autoPromote(AUTO_PROMOTE_INVALID)
        , interactiveBroadcastEnabled(false)
        , videoEnable(false)
        , ipcallEnable(false)
        , webrtcEnable(false)
        , recordServerType(RECORD_SERVER_TYPE_INVALID)
        , recordPrivilege(RECORD_PRIVILEGE_INVALID)
    {
    }

    SStringA subject;
    int64_t startTime;
    Banner banner;
    DefaultRtmp defaultRtmp;
    Profile profile;

    SStringA recordId;
    Array<Entry> confUris;
    OrganizerInfo organizer;
    SStringA conferenceId;
    SStringA conferenceNumber;

    ConferenceType conferenceType;
    ConferenceNumberType conferenceNumberType;
    int64_t bookStartTime;
    int64_t bookExpiryTime;
    SStringA presenterPin;

    SStringA attendeePin;
    uint32_t maximumUserCount;
    AdmissionPolicy admissionPolicy;
    bool lobbyCapable;
    bool attendeeByPass;

    AutoPromote autoPromote;
    SStringA serverMode;
    bool interactiveBroadcastEnabled;
    SStringA enterpriseId;
    bool videoEnable;

    bool ipcallEnable;
    bool webrtcEnable;
    RecordServerType recordServerType;
    RecordPrivilege recordPrivilege;
    SStringA confInfoUrl;
};

/**
 * @brief 
 */
struct ConferenceState
{
    ConferenceState()
        : active(false)
        , locked(false)
    {
    }

    bool active;
    bool locked;
    SStringA rollCallStatus;
};
/**
 * @brief 
 */
struct MemberInfo
{
    MemberInfo()
        : protocol(PROTOCOL_INVALID)
    {
    }

    enum Protocol
    {
        PROTOCOL_INVALID,
        SIP,
        H323,
        RTMP
    };

    struct Roles
    {
        Roles()
            : permissionRole(PERMISSION_INVALID)
            , demoStateRole(DEMOSTATE_INVALID)
            , presenterDemoStateRole(PRESENTER_INVALID)
        {
        }

        enum PermissionRole
        {
            PERMISSION_INVALID,
            PERMISSION_ORGANIZER,
            PERMISSION_PRESENTER,
            PERMISSION_ATTENDEE,
            PERMISSION_CAST_VIEWER
        };

        enum DemoStateRole
        {
            DEMOSTATE_INVALID,
            DEMOSTATE_DEMONSTRATOR,
            DEMOSTATE_AUDIENCE
        };

        enum PresenterDemoStateRole
        {
            PRESENTER_INVALID,
            PRESENTER_DEMONSTRATOR,
            PRESENTER_AUDIENCE
        };

        PermissionRole permissionRole;
        DemoStateRole demoStateRole;
        PresenterDemoStateRole presenterDemoStateRole;
    };

    struct Endpoint
    {
        Endpoint()
            : sessionType(SESSION_TYPE_INVALID)
            , status(STATUS_INVALID)
            , joiningMethod(JOINING_METHOD_INVALID)
        {
        }

        enum SessionType
        {
            SESSION_TYPE_INVALID,
            FOCUS,
            AUDIO_VIDEO,
            APPLICATION_SHARING,
            CHAT,
            COOPSHARE
        };

        enum Status
        {
            STATUS_INVALID,
            DIALING_OUT,
            ON_HOLD,
            CONNECTED,
            DISCONNECTED
        };

        enum JoiningMethod
        {
            JOINING_METHOD_INVALID,
            DIALED_IN,
            DIALED_OUT
        };

        struct Media
        {
            Media()
                : type(TYPE_INVALID)
                , label(LABEL_INVALID)
                , status(STATUS_INVALID)
                , mediaIngressFilter(MEDIA_FILTER_INVALID)
                , mediaIngressBlockBy(BLOCK_BY_INVALID)
                , mediaEgressFilter(MEDIA_FILTER_INVALID)
                , mediaEgressBlockBy(BLOCK_BY_INVALID)
            {
            }

            enum Type
            {
                TYPE_INVALID,
                AUDIO,
                VIDEO,
                APPLICATION
            };

            enum Label
            {
                LABEL_INVALID,
                MAIN_AUDIO,
                MAIN_VIDEO,
                APPLICATIONSHARING,
                FECC
            };

            enum Status
            {
                STATUS_INVALID,
                SEND_RECV,
                SEND_ONLY,
                RECV_ONLY,
                INACTIVE
            };

            enum MediaFilter
            {
                MEDIA_FILTER_INVALID,
                BLOCK,
                UNBLOCK,
                UNBLOCKING
            };

            enum BlockBy
            {
                BLOCK_BY_INVALID,
                NONE,
                SERVER,
                CLIENT
            };

            SStringA id;
            Type type;
            Label label;
            Status status;
            MediaFilter mediaIngressFilter;
            BlockBy mediaIngressBlockBy;
            MediaFilter mediaEgressFilter;
            BlockBy mediaEgressBlockBy;
        };

        SStringA entity;
        SessionType sessionType;
        Status status;
        JoiningMethod joiningMethod;
        SStringA joiningInfo;
        SStringA mcuCallId;
        Array<Media> mediaList;
    };

    SStringA entity;
    SStringA displayText;
    SStringA displayNumber;
    SStringA displayTextPinyin;
    SStringA uid;
    Protocol protocol;
    SStringA mediumServerType;
    SStringA ip;
    SStringA phone;
    SStringA requestUri;
    SStringA userAgent;
    Roles roles;
    Array<Endpoint> endpointList;
};

enum ConferenceViewSpeakMode
{
    CONFERENCE_VIEW_SPEAK_MODE_INVALID,
    CONFERENCE_VIEW_SPEAK_MODE_FREE,
    CONFERENCE_VIEW_SPEAK_MODE_HAND_UP
};

/**
 * @brief 
 */
struct ConferenceView
{
    enum Purpose
    {
        PURPOSE_INVALID,
        FOCUS,
        AUDIO_VIDEO,
        CHAT,
        COOPSHARE,
        APPLICATION_SHARING
    };

    struct EntityState
    {
        EntityState()
            : speakMode(CONFERENCE_VIEW_SPEAK_MODE_INVALID)
            , videoLayout(VIDEO_LAYOUT_INVALID)
            , videoMaxView(0)
            , videoPresenterLayout(VIDEO_PRESENTER_LAYOUT_INVALID)
            , videoPresenterMaxView(0)
            , videoRoundNumber(0)
            , videoRoundInterval(0)
            , videoSpeechExSensitivity(0)
            , videoRoundEnabled(false)
            , videoBigRound(false)
            , videoSpeechExEnabled(false)
            , videoDataMixEnabled(false)
            , hideOsdSitename(false)
            , hideOsdSitestatus(false)
        {
        }

        enum VideoLayout
        {
            VIDEO_LAYOUT_INVALID,
            VIDEO_LAYOUT_EQUALITY,
            VIDEO_LAYOUT_PRESENTATION,
            VIDEO_LAYOUT_SPEECH_EXCITATION,
            VIDEO_LAYOUT_EXCLUSIVE
        };
        enum VideoPresenterLayout
        {
            VIDEO_PRESENTER_LAYOUT_INVALID,
            VIDEO_PRESENTER_LAYOUT_EQUALITY,
            VIDEO_PRESENTER_LAYOUT_SPEECH_EXCITATION,
            VIDEO_PRESENTER_LAYOUT_EXCLUSIVE
        };
        struct MediaFiltersRules
        {
            struct InitialFilter
            {
                InitialFilter()
                    : role(ROLE_INVALID)
                    , ingressFilter(FILTER_INVALID)
                    , egressFilter(FILTER_INVALID)
                {
                }

                enum Role
                {
                    ROLE_INVALID,
                    DEFAULT,
                    ATTENDEE
                };
                enum Filter
                {
                    FILTER_INVALID,
                    BLOCK,
                    UNBLOCK
                };
                Role role;
                Filter ingressFilter;
                Filter egressFilter;
            };
            Array<InitialFilter> initialFilters;
        };
        ConferenceViewSpeakMode speakMode;
        VideoLayout videoLayout;
        uint32_t videoMaxView;
        VideoPresenterLayout videoPresenterLayout;
        uint32_t videoPresenterMaxView;
        uint32_t videoRoundNumber;
        uint32_t videoRoundInterval;
        uint32_t videoSpeechExSensitivity;
        bool videoRoundEnabled;
        bool videoBigRound;
        bool videoSpeechExEnabled;
        bool videoDataMixEnabled;
        bool hideOsdSitename;
        bool hideOsdSitestatus;
        MediaFiltersRules mediaFiltersRules;
    };

    struct EntityView
    {
        EntityView()
            : purpose(PURPOSE_INVALID)
        {
        }

        SStringA entity;
        Purpose purpose;
    };

    SStringA subTitle;
    Array<EntityView> entityViews;
    EntityState entityState;
};

struct UserMediaDetail
{
    UserMediaDetail()
        : enable(false)
        , width(0)
        , height(0)
        , fr(0)
        , sampleRate(0)
        , bandwidth(0)
        , bitRate(0)
        , lossRate(0)
        , packetLost(0)
        , jitter(0)
        , rtt(0)
    {
    }

    bool enable;
    SStringA ip;
    SStringA codec;
    int32_t width;
    int32_t height;
    int32_t fr;
    int32_t sampleRate;
    int32_t bandwidth;
    int32_t bitRate;
    int32_t lossRate;
    int32_t packetLost;
    int32_t jitter;
    int32_t rtt;
};

struct UserMediaInfo
{
    UserMediaInfo()
        : label(MemberInfo::Endpoint::Media::LABEL_INVALID)
        , type(MemberInfo::Endpoint::Media::TYPE_INVALID)
    {
    }

    SStringA mediaId;
    MemberInfo::Endpoint::Media::Label label;
    MemberInfo::Endpoint::Media::Type type;
    UserMediaDetail send;
    UserMediaDetail recv;
};

} // namespace yealink
#endif // __ROOM_DATA_H__
