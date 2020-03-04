/**
 * @file meeting.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-02-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __MEETING_H__
#define __MEETING_H__

#include "meeting_define.h"
#include "avs/av_api.h"
#include "sip_agent/sip_agent_api.h"
#include "room/room.h"
#include "components/base/simplelib/simple_lib.h"

namespace yealink
{
/**
     * @brief 
     * 
     */
typedef struct _DailParam
{
    const char* strUri;
    AVContentType typAVContent;
    _DailParam()
        : strUri("")
        , typAVContent(AV_CONTENT_NONE)
    {
    }
} DailParam;

typedef struct _MeetingInfo
{
    SStringA strNumber;
    SStringA strDomain;
    SStringA strDisplayName;
    SStringA strUserAgent;
    SStringA strLocalDomain;
    bool isVideoEnabled;
    bool isAudioEnabled;
    bool isMediaEncrypted;
    bool isEstablished;
    bool isFinished;
    AVCallHandler::FinishEventId idFinishEvent;
    bool isHoldByRemote;
    bool isHoldByLocal;
    bool isOffer;
    bool isSupportReplaces;
    _MeetingInfo()
        : isVideoEnabled(false)
        , isAudioEnabled(false)
        , isMediaEncrypted(false)
        , isEstablished(false)
        , isFinished(false)
        , idFinishEvent(AVCallHandler::FINISH_BY_ERROR)
        , isHoldByRemote(false)
        , isHoldByLocal(false)
        , isOffer(false)
        , isSupportReplaces(false)
    {
    }
} MeetingInfo;

typedef struct _AplloConferenceInvite
{
    SStringA strUri;
    SStringA strEntity;
    SStringA strInviter;
    SStringA strOrganizer;
    SStringA strNumber;
    SStringA strSubject;
    SStringA strUUID;
} AplloConferenceInvite;

class MEETING_API MeetingObserver
{
public:
    MeetingObserver()
    {
    }
    virtual ~MeetingObserver()
    {
    }

public:
    virtual void OnEvent(MeetingEventId id)
    {
        (void)id;
    }
    virtual void OnMediaEvent(MeetingMediaEventId id)
    {
        (void)id;
    }
    virtual void OnCallInfoChanged(const MeetingInfo& infoNew)
    {
        (void)infoNew;
    }
    virtual void OnCreateConferenceAfter(RoomController* pObject)
    {
        (void)pObject;
    }
    virtual void OnRealseConferenceBefore(RoomController* pObject)
    {
        (void)pObject;
    }

public:
    virtual void OnVideoFrame(const VideoFrame& frame, unsigned int id)
    {
        (void)frame;
    }
    virtual void OnShareFrame(const VideoFrame& frame, unsigned int id)
    {
        (void)frame;
    }
};

class Meeting
{
public:
    virtual ~Meeting(){};
    virtual void SetObserver(MeetingObserver* pObserver) = 0;
    virtual MeetingObserver* GetObserver() = 0;
    virtual void FetchInfo(MeetingInfo& info) = 0;
    virtual bool FetchInviteInfo(AplloConferenceInvite& info) = 0;
    virtual const Array<SIPReasonInfo>& FinishReason() const = 0;
    virtual SIPInviteAgent* MediaCallAgent() = 0;
    virtual RoomController* Room() = 0;
    virtual bool SupportShare() = 0;

public:
    /**
         * @brief dail url
         * 
         * @param param 
         * @return bool
         */
    virtual bool Dail(const DailParam& param) = 0;
    /**
         * @brief create apllo conference
         *
         * @return bool
         */
    virtual bool CreateAplloConference(AVContentType typ) = 0;
    /**
         * @brief Send early.
         *
         * @param[in] strFile
         * @return true
         * @return false
         */
    virtual bool Early(const char* strFile) = 0;
    /**
         * @brief Answer calls
         * 
         * @param typUseMediaContent 
         * @return true 
         * @return false 
         */
    virtual bool Answer(AVContentType typUseAVContent) = 0;
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
    virtual bool TransferToUri(const char* strUri) = 0;
    /**
         * @brief 
         * 
         * @param pExistCall 
         * @return true 
         * @return false 
         */
    virtual bool TransferToCall(Meeting* pExistCall) = 0;
    /**
         * @brief 
         * 
         * @param code 
         * @param strReason 
         * @return true 
         * @return false 
         */
    virtual bool Hangup(SIPCode code, const char* strReason) = 0;
    /**
     * @brief reconnect meeting.
     *
     * @return true
     * @return false
     */
    virtual bool Reconnect() = 0;
    /**
     * @brief Set the call hold state
     * 
     * @param bHold 
     * @return true 
     * @return false 
     */
    virtual bool SetHold(bool bHold) = 0;
    /**
         * @brief Send DTMF key.
         * Use rfc2833.
         * 
         * @param key 
         * @return true 
         * @return false 
         */
    virtual bool SendDTMF(char key) = 0;
    /**
         * @brief Request share desktop/window to remote.
         * 
         * @param window
         * @return true 
         * @return false 
         */
    virtual bool StartSendShare(const ShareWindow& window) = 0;
    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool StopSendShare() = 0;
    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual bool OpenVideoStream() = 0;
    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual MediaStreamStats AVMediaStats() = 0;
    /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
    virtual VideoStreamStats ShareMediaStats() = 0;

public:
    /**
         * @brief Set the max bandwidth limit.
         * if param value == 0 means ignore this param.
         * 
         * @param uMaxSendBitRate max send bandwidth bit rate(kb).
         * @param uMaxRecvBitRate max receive bandwidth bit rate(kb).
         * @return true Success,will be renegotiation bit rate.
         * @return false Failure,not calls established or no available channels.
         */
    virtual void SetCallBitRate(int nMaxSendBitRate, int nMaxRecvBitRate) = 0;
    /**
         * @brief Set the Share Bit Rate object
         * if param value == 0 means ignore this param.
         * 
         * @param uMaxSendBitRate max send bandwidth bit rate(kb).
         * @param uMaxRecvBitRate max receive bandwidth bit rate(kb).
         * @return true Success,will be renegotiation bit rate.
         * @return false Failure,not calls established or no available channels.
         */
    virtual void SetShareBitRate(int nMaxSendBitRate, int nMaxRecvBitRate) = 0;
    /**
     * @brief Rebuild audio and video channel.
     *
     * @return true Success, will be renegotiation audio and video channel.
     * @return false Failure, can not be renegotiation.
     */
    virtual bool RebuildCallRTC() = 0;
    /**
     * @brief Rebuild share channel.
     *
     * @return true Success, will be renegotiation share channel.
     * @return false Failure, can not be renegotiation.
     */
    virtual bool RebuildShareRTC() = 0;
    /**
     * @brief Set custom video capture source.
     *
     */
    virtual bool SetVideoCapute(MediaCapture* pCapture) = 0;
    /**
     * @brief Set custom share capture source.
     *
     */
    virtual bool SetShareCapute(MediaCapture* pCapture) = 0;
    /**
     * @brief Set video capture portrait mode.
     *
     */
    virtual bool EnableVideoPortraitMode(bool bEnable) = 0;
    /**
     * @brief Set SVC share subscribe.
     *
     */
    virtual bool SetShareSubscribe(const VideoSubscribe subscribes[], int sizeSub, const unsigned int unsubscribes[], int sizeUnsub) = 0;
    /**
     * @brief Get support share subscribe.
     *
     */
    virtual bool SupportShareSubscribe() const = 0;
    /**
     * @brief Set SVC video subscribe.
     *
     */
    virtual bool SetVideoSubscribe(const VideoSubscribe subscribes[], int sizeSub, const unsigned int unsubscribes[], int sizeUnsub) = 0;
    /**
     * @brief Get support video subscribe.
     *
     */
    virtual bool SupportVideoSubscribe() const = 0;
    /**
     * @brief Set svc codec enable.
     *
     */
    virtual void SetSvcCodecEnable(bool enable) = 0;
};
} // namespace yealink
#endif //__MEETING_H__
