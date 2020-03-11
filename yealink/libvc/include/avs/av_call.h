#ifndef __AV_CALL_H__
#define __AV_CALL_H__

#include "av_define.h"
#include "sip_agent/sip_agent_api.h"
#include "media/media_call.h"

namespace yealink
{
typedef struct _ContactInfo
{
    SStringA strDisplayName;
    SStringA strDomain;
    SStringA strNumber;
    SStringA strUserAgent;
    SStringA strClientInfo;
    SStringA strServerInfo;
    SStringA strConferenceId;
    unsigned int uCCID;
    _ContactInfo()
        : strConferenceId("svc-p2p")
        , uCCID(0)
    {
    }
} ContactInfo;

class AVCall;
class VideoFrame;
class AV_API AVCallHandler
{
public:
    enum FinishEventId
    {
        FINISH_BY_ERROR,
        FINISH_BY_REPLACED,
        FINISH_BY_REMOTE_CANCEL, ///only with incoming call
        FINISH_BY_LOCAL_CANCEL, ///only with outgoing call
        FINISH_BY_REMOTE_REFUSE, ///only with outgoing call
        FINISH_BY_LOCAL_REFUSE, ///only with incoming call
        FINISH_BY_REFERED,
        FINISH_BY_REMOTE_HANGUP,
        FINISH_BY_LOCAL_HANGUP,
    };

    enum MediaStatus
    {
        MEDIA_SLIENCE,
        MEDIA_ESTABLISHED,
        MEDIA_BROKEN,
        MEDIA_RESUME,
        MEDIA_FINISHED,
        MEDIA_VIDEO_LACK_OF_BANDWIDTH
    };

public:
    AVCallHandler()
    {
    }
    virtual ~AVCallHandler()
    {
    }

public:
    /**
         * @brief 
         * 
         */
    virtual void OnCreate(const AVCall* pCall) = 0;
    /**
         * @brief 
         * 
         */
    virtual void OnConnected(const AVCall* pCall, const SIPMessageReadonly& message) = 0;
    /**
         * @brief 
         * 
         */
    virtual void OnRingBack(const AVCall* pCall) = 0;
    /**
         * @brief 
         * 
         */
    virtual void OnForwardTo(const AVCall* pCall, const char* strUri, const SIPMessageReadonly& message) = 0;
    /**
         * @brief 
         * 
         */
    virtual void OnEstablished(const AVCall* pCall, const SIPMessageReadonly* message) = 0;
    /**
         * @brief 
         * 
         */
    virtual void OnFinished(const AVCall* pCall, FinishEventId id, const Array<SIPReasonInfo>& arrReason) = 0;
    /**
         * @brief 
         * 
         */
    virtual void OnTerminal(const AVCall* pCall) = 0;
    /**
         * @brief 
         * 
         */
    virtual bool OnReplaces(const AVCall* pCall, SIPInviteAgent* pNewAgent) = 0;
    /**
         * @brief 
         * 
         */
    virtual void OnRefer(const AVCall* pCall, const char* strReferToUri, const char* strReferedBy) = 0;
    /**
         * @brief
         *
         */
    virtual void OnHold(const AVCall* pCall, bool bLocalHold, bool bRemoteHold) = 0;
    /**
         * @brief
         *
         */
    virtual void OnReferStateUpdate(SIPReferSubscribeState state) = 0;
    /**
         * @brief
         *
         */
    virtual void OnEvent(const char* strEvent) = 0;

public:
    /**
         * @brief
         *
         */
    virtual void OnVideoFrame(const AVCall* pCall, const VideoFrame& frame, unsigned int id) = 0;
    /**
         * @brief
         *
         */
    virtual void OnMediaTransportFailed(const AVCall* pCall) = 0;
    /**
         * @brief
         *
         */
    virtual void OnAudioStatus(const AVCall* pCall, MediaStatus status) = 0;
    /**
         * @brief
         *
         */
    virtual void OnVideoStatus(const AVCall* pCall, MediaStatus status) = 0;
};

class AV_API AVCall
{
public:
    virtual ~AVCall()
    {
    }

public:
    virtual SIPInviteAgent* Agent() = 0;
    /**
         * @brief Set the Handler object
         * 
         * @param pHandler 
         */
    virtual void SetHandler(AVCallHandler* pHandler) = 0;
    /**
         * @brief Get the Handler object
         * 
         * @return AVCallHandler* 
         */
    virtual AVCallHandler* GetHandler() = 0;
    /**
         * @brief Set the Media Content Type object
         * 
         * @param typ 
         */
    virtual void SetMediaContentType(AVContentType typ) = 0;
    /**
         * @brief Get the Media Content Type object
         * 
         */
    virtual AVContentType MediaContentType() const = 0;
    /**
         * @brief send early
         *
         * @param strFile,can be nullptr
         * @return int
         */
    virtual bool Early(const char* strFile) = 0;
    /**
         * @brief dail url
         * 
         * @param param 
         * @return int 
         */
    virtual bool InviteUri(const char* strUri) = 0;
    /**
         * @brief transfer to uri
         * 
         * @param param 
         * @return int 
         */
    virtual bool InviteUri(const char* strReferToUri, const char* strReferedBy, const char* strReplaceId) = 0;
    /**
         * @brief Answer calls
         * 
         * @param typUseMediaContent 
         * @return true 
         * @return false 
         */
    virtual bool Answer(AVContentType typUseMediaContent) = 0;
    /**
         * @brief 
         * 
         * @param strUrl 
         * @return true Success,will be send forward message,call finish and release channel.
         * @return false Failure,not answer calls or no available channels.
         */
    virtual bool Forward(const char* strUri) = 0;
    /**
         * @brief 
         * 
         * @param strUrl 
         * @return true Success,will be send tansfer message,call finish and release channel.
         * @return false Failure,not calls established or no available channels.
         */
    virtual bool TransferTo(const char* strUri) = 0;
    /**
         * @brief 
         * 
         * @param pCall 
         * @return true 
         * @return false 
         */
    virtual bool TransferTo(AVCall* pCall) = 0;
    /**
         * @brief 
         * 
         * @param pNewCall 
         * @return true 
         * @return false 
         */
    virtual bool AcceptRefer(AVCall* pNewCall) = 0;
    /**
         * @brief 
         * 
         * @param code
         * @param strStatus
         * @param strReason 
         * @return true 
         * @return false 
         */
    virtual bool Hangup(SIPCode code, const char* strStatus, const char* strReason) = 0;
    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool SetHoldState(bool bHold) = 0;
    /**
         * @brief Send DTMF.
         * 
         * @param key 
         * @return true 
         * @return false 
         */
    virtual bool SendDTMF(char key) = 0;
    /**
         * @brief set conference session id.
         * 
         * @param id 
         */
    virtual void SetConversationId(const char* id) = 0;
    /**
         * @brief Get remote contact information.
         * 
         * @return ContactInfo 
         */
    virtual ContactInfo GetContactInfo() const = 0;
    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool IsRemoteHold() const = 0;
    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool IsLocalHold() const = 0;
    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool IsEstablished() const = 0;
    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool IsFinished() const = 0;
    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool IsEncrypted() const = 0;
    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool IsOffer() const = 0;
    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool IsVideoEnabled() const = 0;
    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool IsAudioEnabled() const = 0;
    /**
         * @brief Accept Replaces Call.
         * 
         * @param  
         * @return true 
         * @ret
		 */
    virtual bool AcceptReplaces() = 0;
    /**
         * @brief Termination Call and no sip/http signal.
         *
         * @param
         * @ret
         */
    virtual void Termination() = 0;
    /**
         * @brief Get media stream stats
         * 
         * @param  
         * @return true 
         * @ret
		 */
    virtual MediaStreamStats MediaStats() = 0;
    /**
         * @brief Set video stream bitrate.
         * Video resolution and frame rate will be affected.
         *
         * @param nBitrateR
         * @param nBitrateS
         */
    virtual void SetVideoBitrate(int nBitrateR, int nBitrateS) = 0;
    /**
     * @brief Update video stream send bitrate.
     * Video resolution and frame rate will be affected.
     *
     * @param nBitrate
     */
    virtual void UpdateSendBitrate(int nBitrate) = 0;
    /**
     * @brief Rebuild ice channel and media.
     *
     */
    virtual bool RebuildRTC() = 0;
    /**
     * @brief Set custom video capture source.
     *
     */
    virtual bool SetCustomCapture(MediaCapture* pCapture) = 0;
    /**
         * @brief Enable custom capture portrait mode.
         *
         */
    virtual bool EnableCapturePortrait(bool bEnable) = 0;
    /**
         * @brief Set SVC video subscribes.
         *
         * @param subscribes
         * @param sizeSub
         * @param unsubscribes
         * @param sizeUnsub
         * @return bool
         */
    virtual bool SetVideoSubscribe(const VideoSubscribe subscribes[], int sizeSub, const unsigned int unsubscribes[], int sizeUnsub) = 0;
    /**
         * @brief Get support video subscribe.
         *
         * @return bool
         */
    virtual bool SupportVideoSubscribe() const = 0;
    /**
         * @brief Set SVC codec enable.
         * 
         * default is disable svc.
         */
    virtual void SetSvcCodecEnable(bool enable) = 0;
    /**
         * @brief Set SVC Conference info.
         *
         * default is disable svc.
         */
    virtual void SetSvcConferenceInfo(const char* strId, unsigned int uCCId) = 0;
};
} // namespace yealink

#endif
