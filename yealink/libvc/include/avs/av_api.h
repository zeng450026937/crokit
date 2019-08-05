/*!
* @file av_api.h
* @date 2019/03/17
*
* @brief 
*
*/
#ifndef __AV_API_H__
#define __AV_API_H__

#include "avs/av_define.h"
#include "avs/av_call.h"
#include "sip_agent/sip_agent_api.h"
#include "media/media_api.h"

namespace yealink
{
/**
     * @brief Create a call object.
     *
     * @param[in] client
     * @param[in] media
     * @param[in] bOffer
     * @return AVCall*
     */
AV_API AVCall* CreateCall(SIPClient& client, Media& media, bool bOffer);
/**
     * @brief Create a call object of replace. 
     *
     * @param[in] client
     * @param[in] media
     * @param[in] pAgent 
     * @return AVCall*
     */
AV_API AVCall* CreateReplaceCall(SIPClient& client, Media& media, SIPInviteAgent* pAgent);
/**
     * @brief Create a call object of share content.
     *
     * @param[in] client
     * @param[in] media
     * @param[in] bOffer
     * @return AVCall*
     */
AV_API AVCall* CreateShare(SIPClient& client, Media& media, bool bOffer);
/**
     * @brief Release call object.
     *
     * @param pObject
     */
AV_API void ReleaseCall(AVCall* pObject);
} // namespace yealink

#endif //__AV_API_H__
