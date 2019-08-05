#ifndef __SIP_INVITE_AGENT_H__
#define __SIP_INVITE_AGENT_H__

#include "sip_agent/sip_agent_define.h"
#include "sip_agent/sip_message_readonly.h"
#include "sip_agent/sip_observer.h"
#include "sip_agent/sip_agent.h"

namespace yealink
{
class SIPInviteAgent;

class SIPInviteObserver : public SIPObserver
{
public:
    /**
         * @brief 
         * 
         * @param message, StatusCode only SIP_TRYING
         */
    virtual void OnTryResponse(const SIPMessageReadonly& message) = 0;
    /**
         * @brief 
         * 
         * @param message, StatusCode only SIP_RINGING
         */
    virtual void OnRingResponse(const SIPMessageReadonly& message) = 0;
    /**
         * @brief 
         * 
         * @param code 
         * @param strContactUri 
         */
    virtual void OnForwardResponse(const char* strContactUri, const SIPMessageReadonly& message) = 0;
    /**
         * @brief
         *
         * @param message
         */
    virtual void OnInfoResponse(const SIPMessageReadonly& message) = 0;
    /**
         * @brief 
         * 
         */
    virtual void OnOffer(const SIPMessageReadonly& message) = 0;
    /**
         * @brief 
         * 
         */
    virtual void OnAnswer(const SIPMessageReadonly& message) = 0;
    /**
         * @brief 
         * 
         * @param message
         */
    virtual void OnUpdate(const SIPMessageReadonly& message) = 0;
    /**
         * @brief 
         * 
         * @param message
         */
    virtual void OnInfo(const SIPMessageReadonly& message) = 0;
    /**
         * @brief 
         * 
         * @param strReferToUri 
         * @param strReferedBy 
         * @param strReplaceId 
         */
    virtual void OnRefer(const SIPMessageReadonly& message, const char* strReferToUri, const char* strReferedBy, const char* strReplaceId) = 0;

    /**
         * @brief 
         * 
         * @param  
         * @param  
         */

    virtual void OnReInvite(const SIPMessageReadonly& message) = 0;

    /**
         * @brief 
         * 
         * @param  
         * @param  
         */

    virtual void OnReferSubscribeUpdate(SIPReferSubscribeState state) = 0;

    /**
         * @brief 
         * 
         * @param  
         * @param  
         */

    virtual bool OnReplaces(const SIPMessageReadonly& message, SIPInviteAgent* agent) = 0;

    /**
         * @brief 
         * 
         * @param message 
         */
    virtual void OnFinished(const SIPMessageReadonly& message) = 0;
    /**
         * @brief 
         * 
         * @param message 
         */
    virtual void OnNotify(const SIPMessageReadonly& message) = 0;
};

class SIP_AGENT_API SIPInviteAgent : public SIPAgent
{
public:
    /**
         * @brief 
         * 
         * @return const char* 
         */
    static const char* DTMFContentType();

public:
    virtual bool SendRing(const char* strContent, const char* strContentType) = 0;
    /**
         * @brief 
         * 
         * @param targetURL 
         * @param sdp 
         * @return true 
         * @return false 
         */
    virtual bool SendInvite(const char* strContent, const char* strContentType) = 0;
    /**
         * @brief 
         * 
         * @param strUri
         * @return true 
         * @return false 
         */
    virtual bool SendForward(const char* strUri) = 0;
    /**
         * @brief 
         * 
         * @param strContent 
         * @param strContentType 
         * @return true 
         * @return false 
         */
    virtual bool SendUpdate(const char* strContent, const char* strContentType) = 0;
    /**
         * @brief
         *
         * @param strContent
         * @param strContentType
         * @return true
         * @return false
         */
    virtual bool SendReinvite(const char* strContent, const char* strContentType) = 0;
    /**
         * @brief 
         * 
         * @param targetURL 
         * @param referURL 
         * @return true 
         * @return false 
         */
    virtual bool SendRefer(const char* strReferUri) = 0;
    /**
         * @brief 
         * 
         * @param pAgent 
         * @return true 
         * @return false 
         */
    virtual bool SendRefer(SIPInviteAgent* pAgent) = 0;
    /**
         * @brief 
         * 
         * @param strContent A string ending in '\0'
         * @param strContentType A string ending in '\0'
         * @return true 
         * @return false 
         */
    virtual bool SendInfo(const char* strContent, const char* strContentType) = 0;
    /**
         * @brief
         *
         * @param strContent A string ending in '\0'
         * @param strContentType A string ending in '\0'
         * @return true
         * @return false
         */
    virtual bool SendInfoResponse(const SIPMessageReadonly& msgInfo, SIPCode code, const char* strContent, const char* strContentType) = 0;
    /**
         * @brief 
         * 
         * @param strReason 
         * @return true 
         * @return false 
         */
    virtual bool SendBye(const char* strReason) = 0;
    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool Answer(const char* strContent, const char* strContentType) = 0;
    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool Cancel(const char* strReason) = 0;
    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool Refuse(SIPCode code, const char* strStatus, const char* strReason) = 0;

    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool AcceptRefer(const SIPInviteAgent* pAgent) = 0;

    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool RejectRefer() = 0;

    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool AcceptForward() = 0;

    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool RejectForward() = 0;

    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool AcceptReplaces() = 0;

public:
    /**
         * @brief Set the Observer object
         * 
         * @param pObserver 
         */
    virtual void SetObserver(SIPInviteObserver* pObserver) = 0;
};
} // namespace yealink
#endif
