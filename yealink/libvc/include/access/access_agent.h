#ifndef _ACCESS_AGENT_H
#define _ACCESS_AGENT_H

#include "access/access_define.h"

namespace yealink
{
class AccessProcess
{
public:
    virtual ~AccessProcess()
    {
    }
    /**
     * @brief stop api func's http request
     * @param  
     */
    virtual bool IsStop()
    {
        return false;
    };

    /**
     * @brief
     * @param  
     */
    virtual void SetErrorInfo(int code, const char* msg){};

    /**
     * @brief
     * @param
     */
    virtual void SetBizCode(int code){};

    /**
     * @brief
     * @param  
     */
    virtual void SetHttpCode(int code){};

    /**
     * @brief
     * @param  
     */
    virtual void SetTransferStatus(int up, int uptotal, int dn, int dntotal){};

    /**
     * @brief
     * @param
     */
    virtual int GetTimeoutSeconds()
    {
        return 0;
    };
};

class AccessObserver
{
public:
    virtual ~AccessObserver()
    {
    }

    /**
     * @brief 
     * @param content 
     */
    virtual void OnScheduleMessage(const char* content)
    {
        (void)content;
    };

    /**
     * @brief 
     * @param content 
     */
    virtual void OnContactMessage(const char* content)
    {
        (void)content;
    };

    /**
     * @brief 
     * @param content 
     */
    virtual void OnPushMessage(const char* content)
    {
        (void)content;
    };
};

class ACCESS_AGENT_API AccessAgent
{
public:
    virtual ~AccessAgent()
    {
    }
    /**
         * @brief get Schedule Services meta Information
         *
         * @param url
         * @param process
         * @return ScheduleMetaInfo
         */
    static SchedulerMetaInfo GetMetaInfo(const char* url, AccessProcess* process);
    /**
         * @brief get Schedule Services Information
         *
         * @param url example:http://10.71.1.40:9994/link?device=vcd、mobile
         * @param process
         * @return SStringA
         */
    static SStringA GetServiceInfo(const char* url, AccessProcess* process);
    /**
         * @brief set device display language
         * 
         * @param lang 
         * @return true/false
         */
    virtual bool SetLanguage(const char* lang) = 0;

    /**
         * @brief set registe area
         * 
         * @param area 
         * @return true/false
         */
    virtual bool SetRegion(const char* region) = 0;

    /**
         * @brief set schedule host
         * 
         * @param server 
         * @return true/false
         */
    virtual bool SetScheduleHost(const char* server) = 0;

    /**
         * @brief set access host,only for test
         * 
         * @param server 
         * @return true/false
         */
    virtual bool SetAccessHost(const char* server) = 0;

    /**
         * @brief Add the Observer Handler object
         * 
         * @param handler 
         * @return true/false
         */
    virtual bool AddObserverHandler(AccessObserver* observer) = 0;

    /**
         * @brief Del the Observer Handler object
         * 
         * @param handler 
         * @return true/false
         */
    virtual bool RemoveObserverHandler(AccessObserver* observer) = 0;

    /**
         * @brief tell the server to send a sms verify code
         * 
		 * @param phoneNumber 
         * @return true if server return success,otherwise false
         */
    virtual bool SendMobileLoginVerifyCode(const char* phoneNumber, AccessProcess* process) = 0;

    /**
         * @brief tell the server to bind push token
         * 
         * @param server : access server address
		 * @param BindPushInfo 
         * @return true if server return success,otherwise false
         */
    virtual bool BindPushToken(const BindPushInfo& pushInfo, AccessProcess* process) = 0;

    /**
         * @brief get wechat state
         * 
         * @return true if server return success,otherwise false
         */
    virtual SStringA GetWechatState(AccessProcess* process) = 0;

    /**
         * @brief  post wechat auth callback
         * 
		 * @param WechatAuthInfo 
         * @return 
         */
    virtual WechatAuthCallbackInfo PostWechatAuthCallback(const WechatAuthInfo& info, AccessProcess* process) = 0;

    /**
         * @brief login access service by schedule service
         * 
         * @param server : schedule server address
		 * @param username 
		 * @param password 
         * @return SStringA
         */
    virtual LoginUserInfos LoginAccessService(const LoginInfo& info, AccessProcess* process) = 0;

    /**
         * @brief start access push service, after invoke LoginAccessService()
         * 
         * @param username 
		 * @param password
		 * @param token
         * @return true/false
         */
    virtual bool StartAccessService(const char* accountInfoId) = 0;

    /**
         * @brief common http request api
         * 
         * @param params 
         * @param process 
         * @return SStringA
         */
    virtual SStringA SendHttpRequest(const HttpRequestParam& params, AccessProcess* process) = 0;
    /**
         * @brief common http request api
         *
         * @param params
         * @param process
         * @return SStringA
         */
    virtual SStringA SendHttpRequest(const HttpRequestParam& params, const char* token, AccessProcess* process) = 0;
    /**
         * @brief get Schedule Services jwt
         * 
         * @param partyId 
         * @param number
         * @param process 
         * @return SStringA
         */
    virtual SStringA GetTempJWT(const char* partyId, const char* number, AccessProcess* process) = 0;
    /**
         * @brief get LoginUserInfo by account id
         * 
         * @param account id 
         * @return ScheduleMetaInfo
         */
    virtual LoginUserInfo GetLoginUserInfoById(const char* id) = 0;

    /**
         * @brief get invite info of current account party
         * 
         * @return PartyInviteInfo
         */
    virtual PartyInviteInfo GetPartyInviteInfo(AccessProcess* process) = 0;

    /**
         * @brief Logout from access service
         * 
         * @return 
         */
    virtual void StopAccessService() = 0;
};
} // namespace yealink

#endif // YTMS_SERVICE_H
