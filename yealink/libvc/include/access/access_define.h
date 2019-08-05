#ifndef ACCESS_DEFINE_H
#define ACCESS_DEFINE_H

#include "components/base/simplelib/simple_lib.h"

#ifdef _WIN32
#    ifdef EXPORT_SYMPOLS
#        define ACCESS_AGENT_API __declspec(dllexport)
#    else
#        define ACCESS_AGENT_API __declspec(dllimport)
#    endif
#else
#    define ACCESS_AGENT_API
#endif

namespace yealink
{
enum HttpMethod
{
    HTTP_POST = 0,
    HTTP_GET,
    HTTP_PUT
};

struct AccountInfo
{
    SStringA extension;
    SStringA uid;
    SStringA principle;
};

struct PartyInfo
{
    SStringA area;
    SStringA country;
    SStringA domain;
    bool frozen;
    SStringA uid;
    SStringA name;
    SStringA number;
    SStringA realm;
    int slot;
    int status;
    int subType;
    SStringA zoneId;
};

struct PermissionInfo
{
    bool enableMeetingNow;
};

struct SubjectInfo
{
    SStringA groupInfos;
    SStringA uid;
    SStringA name;
    SStringA namePinyinForSearch;
    int type;
};

struct LoginUserInfo
{
    AccountInfo account;
    PartyInfo party;
    PermissionInfo permission;
    SubjectInfo subject;
    SStringA token;
};

struct LoginInfo
{
    const char* server;
    const char* username;
    const char* password;
    LoginInfo()
        : server("")
        , username("")
        , password("")
    {
    }
};

struct HttpRequestParam
{
    HttpMethod method;
    const char* serverAddr;
    const char* apiUrl;
    const char* body;
    HttpRequestParam()
        : serverAddr("")
        , apiUrl("")
        , body("")
    {
    }
};

struct ScheduleMetaInfo
{
    SStringA phonebookVersion;
    Array<SStringA> phonebookSupport;
    SStringA scheduleVersion;
    Array<SStringA> scheduleSupport;
    SStringA build;
    SStringA version;
    ScheduleMetaInfo()
        : phonebookVersion("")
        , scheduleVersion("")
        , build("")
        , version("")
    {
    }
};

} // namespace yealink

#endif
