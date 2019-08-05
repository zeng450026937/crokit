#ifndef __MEETING_API_H__
#define __MEETING_API_H__

#include "meeting_define.h"
#include "meeting.h"
#include "sip_agent/sip_agent_api.h"
#include "media/media_api.h"

namespace yealink
{
/**
     * @brief Create a Incoming Meeting Call object
     * 
     * @param[in] client 
     * @return Meeting* 
     */
MEETING_API Meeting* CreateMeeting(SIPClient& client, Media& media, bool bOffer);
/**
     * @brief 
     * 
     * @param pObject 
     */
MEETING_API void ReleaseMeeting(Meeting* pObject);
} // namespace yealink

#endif