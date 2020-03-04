#ifndef __SIP_CLIENT_H__
#define __SIP_CLIENT_H__

#include "sip_agent/connection.h"
#include "sip_agent/sip_message_readonly.h"
#include "sip_agent/sip_define.h"
#include "sip_agent/sip_invite_agent.h"
#include "sip_agent/sip_message_agent.h"
#include "sip_agent/sip_subscription_agent.h"
#include "sip_agent/sip_service_agent.h"

namespace yealink
{
class SIPClientHandler
{
public:
    virtual ~SIPClientHandler(){};
    /**
         * @brief 
         * 
         * @param message 
         * @param [out] pAgent the value is null will 
         * response 488(not accept here), if not will continue processing and response 180(Ring).
         */
    virtual void OnOffer(const SIPMessageReadonly& message, SIPInviteAgent** pAgent) = 0;
};

class SIPClientFilter
{
};

class SIPClient : public Connnection
{
public:
    /**
         * @brief Set sip head of Client-Info.
         *
         * @param[in] strInfo
         */
    virtual void SetClientInfo(const char* strInfo) = 0;
    /**
         * @brief Set sip head of Apl-Device-Language.
         *
         * @param[in] strInfo
         */
    virtual void SetLanguageInfo(const char* strInfo) = 0;
    /**
         * @brief Set the transport type.
         * Use 0.0.0.0(IPv4)/::(IPv6) by default.
         * 
         * @param[in] addrLocal
         * @param[in] typTransport 
         * @return true
         * @return false
         */
    virtual bool AddTransport(const Address& addrLocal, TransportType typTransport) = 0;
    /**
         * @brief remove the transport
         * 
         */
    virtual void RemoveTransport(const Address& addrLocal, TransportType typTransport) = 0;
    /**
         * @brief add the transport
         *
         */
    virtual bool AddTransport2(const Address2& addrLocal, TransportType typTransport) = 0;
    /**
         * @brief remove the transport
         *
         */
    virtual void RemoveTransport2(const Address2& addrLocal, TransportType typTransport) = 0;
    /**
         * @brief clean the all transport
         *
         */
    virtual void TransportShutdown() = 0;
    /**
         * @brief Set the Client Handler object
         * 
         * @param pHandler 
         */
    virtual void SetClientHandler(SIPClientHandler* pHandler) = 0;
    /**
         * @brief 
         * 
         * @return SIPClientHandler* 
         */
    virtual SIPClientHandler* GetClientHandler() = 0;
    /**
         * @brief Set the conversation handler object
         *
         * @param pHandler
         */
    virtual void RegisterConversationHandler(const char* strId, SIPClientHandler* pHandler) = 0;
    /**
         * @brief Remove the conversation handler object
         *
         * @param pHandler
         */
    virtual void RemoveConversationHandler(const char* strId) = 0;
    /**
         * @brief Create a Invite Agent object
         * 
         * @return SIPInviteAgent 
         */
    virtual SIPInviteAgent* CreateInviteAgent(const char* strTargetUri) = 0;
    /**
     * @brief Create a Invite Agent object
     *
     * @param strTargetUri 
     * @param strReplacesUri
     * @param strRefferByUri
     * @return SIPInviteAgent
     */
    virtual SIPInviteAgent* CreateInviteAgent(const char* strTargetUri, const char* strReplacesUri, const char* strRefferByUri) = 0;
    /**
         * @brief 
         * 
         * @param pAgent 
         */
    virtual void RealseInviteAgent(SIPInviteAgent* pAgent) = 0;
    /**
         * @brief Create a Message Agent object
         * 
         * @return SIPMessageAgent* 
         */
    virtual SIPMessageAgent* CreateMessageAgent(const char* strTargetUri) = 0;
    /**
         * @brief 
         * 
         * @param pAgent 
         */
    virtual void RealseMessageAgent(SIPMessageAgent* pAgent) = 0;
    /**
         * @brief Create a Subscription Agent object
         * 
         * @return SIPSubscriptionAgent* 
         */
    virtual SIPSubscribeAgent* CreateSubscriptionAgent(const char* strTargetUri, const char* strEvent) = 0;
    /**
         * @brief 
         * 
         * @param pAgent 
         */
    virtual void RealseSubscriptionAgent(SIPSubscribeAgent* pAgent) = 0;
    /**
         * @brief
         *
         * @param strTargetUri
         * @param strEvent
         */
    virtual SIPServiceAgent* CreateServiceAgent(const char* strTargetUri, const char* strEvent) = 0;
    /**
         * @brief 
         * 
         * @param pAgent 
         */
    virtual void RealseServiceAgent(SIPServiceAgent* pAgent) = 0;
    /**
         * @brief
         *
         * @param nWaitTimems
         */
    virtual bool ProcessOnce(int nWaitTimems) = 0;
    /**
     * @brief
     *
     * @param nWaitTimems
     */
    virtual SStringA SiteUri() = 0;
};
}; // namespace yealink
#endif
