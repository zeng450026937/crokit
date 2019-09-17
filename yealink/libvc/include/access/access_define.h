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
    SStringA encryptedCredential;
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

struct TurnServerInfo
{
    SStringA username;
    SStringA password;
};

struct LoginUserInfo
{
    AccountInfo account;
    PartyInfo party;
    PermissionInfo permission;
    SubjectInfo subject;
    TurnServerInfo turnServer;
    SStringA token;
};

struct LoginUserInfos
{
    Array<LoginUserInfo> accountInfos;
    SStringA principle;
    SStringA realm;
    SStringA type;
    SStringA algorithm;
    SStringA credential;
};

struct LoginInfo
{
    const char* server;
    const char* username;
    const char* password; //正常密码、短信验证码、LoginUserInfos中的ha1摘要credential
    bool isSmsVerify; //是否短信验证
    const char* algorithm; //摘要算法，通常为空，验证码自动登录时填LoginUserInfos中的algorithm
    const char* realm; //暂时没用到，先填空
    LoginInfo()
        : server("")
        , username("")
        , password("")
        , isSmsVerify(false)
        , algorithm("")
        , realm("")
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

struct PartyInviteInfo
{
    SStringA url;
    int applicants;
    PartyInviteInfo()
        : applicants(0)
    {
    }
};

} // namespace yealink

#endif
