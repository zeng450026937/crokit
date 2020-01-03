#ifndef _RECORD_DEFINE_H
#define _RECORD_DEFINE_H

#include "components/base/simplelib/simple_lib.h"

#ifdef _WIN32
#    ifdef EXPORT_SYMPOLS
#        define RECORD_API __declspec(dllexport)
#    else
#        define RECORD_API __declspec(dllimport)
#    endif
#else
#    define RECORD_API
#endif

namespace yealink
{
enum CallObject
{
    CALLRECORD_FOR_USER,
    CALLRECORD_FOR_CONFERENCE,
    CALLRECORD_FOR_SHARE
};

enum CallDirection
{
    CALLRECORD_INCOMING,
    CALLRECORD_OUTGOING
};

enum CallStatus
{
    CALLRECORD_MISSED,
    CALLRECORD_REDIRECTED,
    CALLRECORD_ANSWER,
    CALLRECORD_REPLACED,
    CALLRECORD_REFUSED,
};

enum CallMedia
{
    CALLRECORD_AUDIO,
    CALLRECORD_VIDEO
};

struct CallInfo
{
    int64_t id;
    const char* context;
    const char* displayName;
    const char* number;
    const char* uri;
    int64_t startTime;
    int64_t endTime;
    int64_t durationTime;
    CallObject callType;
    CallDirection direction;
    CallStatus status;
    CallMedia media;
    CallInfo()
        : id(-1)
        , context("")
        , displayName("")
        , number("")
        , uri("")
        , startTime(-1)
        , endTime(-1)
        , durationTime(-1)
        , callType(CALLRECORD_FOR_USER)
        , direction(CALLRECORD_INCOMING)
        , status(CALLRECORD_ANSWER)
        , media(CALLRECORD_AUDIO)
    {
    }
};

struct CallRecordInfos
{
    int64_t id;
    SStringA context;
    SStringA displayName;
    SStringA number;
    SStringA uri;
    int64_t startTime;
    int64_t endTime;
    int64_t durationTime;
    CallObject callType;
    CallDirection direction;
    CallStatus status;
    CallMedia media;
    CallRecordInfos()
        : id(-1)
        , startTime(-1)
        , endTime(-1)
        , durationTime(-1)
        , callType()
        , direction()
        , status()
        , media()
    {
    }
};
} // namespace yealink
#endif
