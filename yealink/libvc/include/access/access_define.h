/*
 * @Description: In User Settings Edit
 * @Author: your name
 * @Date: 2019-09-19 15:09:04
 * @LastEditTime: 2019-09-19 15:09:04
 * @LastEditors: your name
 */
#ifndef ACCESS_DEFINE_H
#define ACCESS_DEFINE_H
#include "components/base/simplelib/simple_lib.h"

#ifdef _WIN32
#    ifndef ENABLE_UNIT_TEST
#        ifdef EXPORT_SYMPOLS
#            define ACCESS_AGENT_API __declspec(dllexport)
#        else
#            define ACCESS_AGENT_API __declspec(dllimport)
#        endif
#    else
#        define ACCESS_AGENT_API
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

struct BindPushInfo
{
    const char* token;
    bool bind;
    int tenantId;
    const char* clientId;
    const char* language;
    const char* apnsToken;
    const char* env;
    const char* thirdPartyToken;
    const char* service;
    const char* voipEnable;
    BindPushInfo()
        : token("")
        , bind(true)
        , tenantId(0)
        , clientId("")
        , language("")
        , apnsToken("")
        , env("")
        , thirdPartyToken("")
        , service("")
        , voipEnable("")
    {
    }
};

struct WechatAuthInfo
{
    const char* code;
    const char* state;
    const char* source;
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
    PartyInfo()
        : frozen(false)
        , slot(0)
        , status(0)
        , subType(0)
    {
    }

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
    PermissionInfo()
        : enableMeetingNow(false)
    {
    }

    bool enableMeetingNow;
};

struct GroupInfo
{
    SStringA uid;
    SStringA name;
    SStringA namePinyinForSearch;
};

struct SubjectInfo
{
    SubjectInfo()
        : type(0)
        , gender(0)
    {
    }

    Array<GroupInfo> groupInfos;
    SStringA uid;
    SStringA name;
    SStringA namePinyinForSearch;
    int type;
    SStringA title;
    int gender;
    Array<int> roles;
    SStringA mobile;
    SStringA email;
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

struct UserAccountInfo
{
    PartyInfo partyInfo;
    SubjectInfo subjectInfo;
    AccountInfo accountInfo;
    PermissionInfo permissionInfo;
};

//登录返回的账号鉴权信息
struct LoginAuthInfo
{
    SStringA principle;
    SStringA realm;
    SStringA type;
    SStringA algorithm;
    SStringA credential;
};

struct WechatUserInfo
{
    SStringA thirdPartyId; // 微信用户的 unionid,用于后续绑定流程
    SStringA nickName; // 微信用户的昵称
    SStringA countryCode; // 微信用户所属国家的区域编码
};

struct LoginUserInfos
{
    Array<LoginUserInfo> accountInfos;
    LoginAuthInfo authInfo;
    bool hasRegister; // 是否注册个人账号，因为软终端现在还未限制云账号登录，对于未注册的云账号登录时可能需要根据此字段限制一些功能
    bool upgraded; // 账号是否已创建企业，false：没有创建企业；true：已经创建企业
    LoginUserInfos()
        : hasRegister(false)
        , upgraded(false)
    {
    }
};

struct WechatAuthCallbackInfo
{
    Array<LoginUserInfo> accountInfos;
    LoginAuthInfo authInfo;
    WechatUserInfo wechatUserInfo;
};

struct LoginInfo
{
    const char* username;
    const char* password; //正常密码、短信验证码、LoginUserInfos中的ha1摘要credential
    bool isSmsVerify; //是否短信验证
    const char* algorithm; //摘要算法，通常为空，验证码自动登录时填LoginUserInfos中的algorithm
    const char* realm; //暂时没用到，先填空
    LoginInfo()
        : username("")
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
    const char* compressMethod; //压缩方式，如“gzip”,一般放空，有要求才设置
    const char* httpConnectionName; //有需要长连接时需要设置一个别名来区分
    HttpRequestParam()
        : method()
        , serverAddr("")
        , apiUrl("")
        , body("")
        , compressMethod("")
        , httpConnectionName("")
    {
    }
};

struct SchedulerMetaInfo
{
    SStringA phonebookVersion;
    Array<SStringA> phonebookSupport;
    SStringA scheduleVersion;
    Array<SStringA> scheduleSupport;
    SStringA build;
    SStringA version;
    SStringA webHost;
    SStringA serviceAccount;
    SStringA experienceAccount;
    SchedulerMetaInfo()
        : phonebookVersion("")
        , scheduleVersion("")
        , build("")
        , version("")
        , webHost("")
        , serviceAccount("")
        , experienceAccount("")
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
