#ifndef __MEDIA_CALL_H__
#define __MEDIA_CALL_H__

#include "media/media_api.h"

namespace yealink
{
enum OutMediaType
{
    MT_AUDIO_ONLY = 0, //音频通话
    MT_AUDIO_VIDEO, //视频通话
    MT_VIDEO_ONLY //辅流
};

enum DeviceType
{
    DT_CAMERA = 0,
    DT_MICROPHONE,
    DT_SPEAKER,
    DT_SHARE_WINDOW
};

enum MediaDirection
{
    MD_SEND_ONLY = 0,
    MD_SEND_RECV,
    MD_RECV_ONLY,
    MD_INACTIVE
};

enum SdpOfferAnswer
{
    SOA_UNKNOWN = 0,
    SOA_OFFER,
    SOA_ANSWER
};

struct SdpParams
{
    OutMediaType mediaType;
    MediaDirection mediaDireation;
    bool bRtcpMux;
    bool bEnableCrypted;
    bool bDtls;
    bool bEnableICE;
    SStringA strLocalIP; //IP直拨时这里应该填写正确的本地IP

    //外部不需要传
    bool bICERestart; //重协商时ice是否重启
};

struct VideoResolution
{
    int maxBitrate; //bps
    int maxFps;
    int maxHeight;
    int maxWidth;
};

enum MediaEvent
{
    ME_NONE = 0,
    ME_AUDIO_CODEC_MACTH_FAILED,
    ME_VIDEO_CODEC_MACTH_FAILED,
    ME_AUDIO_DEAD,
    ME_AUDIO_ALIVE,
    ME_AUDIO_TALK_FAILED,
    ME_VIDEO_DEAD,
    ME_VIDEO_ALIVE,
    ME_VIDEO_KEYFRAME_REQUEST_TO_SENDER,
    ME_VIDEO_FLOW_CONTROL_BY_RECEIVER,
    ME_VIDEO_CAMERA_DEVICE_LOST,
    ME_VIDEO_CAMERA_DEVICE_RESUME
};

class MediaCallObserver
{
public:
    virtual void OnSdpGathered(const char* strSdp) = 0;
    virtual void OnMediaEvent(MediaEvent eventId, int extSize = 0, void* extData = nullptr) = 0;
    virtual void OnICEFailed() = 0;
    virtual void OnAudioSessionStart() = 0;
    virtual void OnAudioSessionStoped() = 0;
    virtual void OnVideoSessionStart() = 0;
    virtual void OnVideoSessionStoped() = 0;
};

class MEDIA_EXPORT MediaCall
{
public:
    static MediaCall* CreateInstance(Media* pMedia, bool bMain);
    static void ReleaseInstance(MediaCall* pMediaCall);
    static void GetResultionByBitRate(int nBitrate, int& nFps, int& nWidth, int& nHeight);
    static int GetBitrateByResultion(int nFps, int nResultion);

public:
    virtual bool Start(SdpParams& params) = 0;
    virtual void Stop() = 0;
    virtual bool SetRemoteDescription(const char* strSdp) = 0;
    virtual SStringA LocalDescription() = 0;
    virtual SStringA RemoteDescription() = 0;
    virtual bool EnableDTLS() const = 0;
    virtual bool IsAudioCrypted() const = 0;
    virtual bool IsVideoCrypted() const = 0;
    virtual bool RemoteHasAudio() = 0;
    virtual bool RemoteHasVideo() = 0;
    virtual bool HasAudioChannel() = 0;
    virtual bool HasVideoChannel() = 0;
    virtual bool Hold() = 0;
    virtual bool Unhold() = 0;
    virtual bool SupportRFC2833() = 0;
    virtual bool SendDTMF(char key) = 0;
    virtual void SetRemoteVideoRender(VideoRender* render) = 0;
    virtual void SetObserver(MediaCallObserver* ob) = 0;
    virtual MediaStreamStats GetStats() = 0;
    virtual void SetCustomCapture(MediaCapture* capture) = 0;
    virtual bool StartSecondaryFlow(MediaDirection direction) = 0;
    virtual void SetSendVideoResolution(const VideoResolution& resolution) = 0;
    virtual bool UpdateSendVideoResolution(const VideoResolution& resolution) = 0;
    virtual void SetRecvVideoResolution(const VideoResolution& resolution) = 0;
    virtual bool RestartIce() = 0;
    virtual bool EnableVideoPortrait(bool enable) = 0;
    virtual bool IsKeyFrameRequestMethodExternal() = 0;

protected:
    virtual ~MediaCall() = default;
};
} // namespace yealink

#endif
