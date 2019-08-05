/*!
* @file sip_agent.h
* @date 2019/02/27
*
* @brief 
*
*/
#ifndef __SIP_AGENT_H__
#define __SIP_AGENT_H__

#include "sip_agent/sip_agent_define.h"

namespace yealink
{
class SIPAgent
{
public:
    /**
         * @brief 
         * 
         * @param strSupport 
         */
    virtual void AddSupport(const char* strSupport) = 0;
    /**
         * @brief 
         * 
         * @param strMIME 
         */
    virtual bool AddAccept(const char* strMIME) = 0;
    /**
         * @brief 
         * 
         * @param strMIME 
         */
    virtual void RemoveAccept(const char* strMIME) = 0;
    /**
         * @brief 
         * 
         * @param strMIME 
         */
    virtual void ClearAccept(const char* strMIME) = 0;
    /**
         * @brief 
         * 
         * @param strSupport 
         */
    virtual void AddAplConversationId(const char* strId) = 0;
};
} // namespace yealink

#endif //__SIP_AGENT_H__