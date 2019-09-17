#ifndef _ACCESS_AGENT_H
#define _ACCESS_AGENT_H

#include "access_define.h"

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
};

class ACCESS_AGENT_API AccessAgent
{
public:
    ~AccessAgent()
    {
    }
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
         * @param server : schedule server address
		 * @param phoneNumber 
         * @return true if server return success,otherwise false
         */
    virtual bool SendMobileLoginVerifyCode(const char* server, const char* phoneNumber, AccessProcess* process) = 0;

    /**
         * @brief tell the server to send a sms verify code
         * 
         * @param server : access server address
		 * @param phoneNumber 
         * @return true if server return success,otherwise false
         */
    virtual bool UnscheduledSendMobileLoginVerifyCode(const char* server, const char* phoneNumber, AccessProcess* process) = 0;

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
         * @brief login access service direct
         * 
         * @param server : access server address
		 * @param username 
		 * @param password 
         * @return SStringA
         */
    virtual LoginUserInfos UnscheduledLoginAccessService(const LoginInfo& info, AccessProcess* process) = 0;

    /**
         * @brief start access push service, after invoke LoginAccessService()
         * 
         * @param username 
		 * @param password
		 * @param token
         * @return true/false
         */
    virtual bool StartAccessPushService(const char* accountInfoId) = 0;

    /**
         * @brief common http request api
         * 
         * @param method 
         * @param serverAddr 
         * @param apiUrl 
         * @param body 
         * @return true/false
         */
    virtual SStringA SendHttpRequest(const HttpRequestParam& params, AccessProcess* process) = 0;

    /**
         * @brief get Schedule Services Information
         * 
         * @param url 
         * @param process 
         * @return ScheduleMetaInfo
         */
    virtual ScheduleMetaInfo GetMetaInfo(const char* url, AccessProcess* process) = 0;

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
};
} // namespace yealink

#endif // YTMS_SERVICE_H
