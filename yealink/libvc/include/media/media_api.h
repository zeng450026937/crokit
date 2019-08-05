#ifndef __MEDIA_API_H__
#define __MEDIA_API_H__

#include "media/media_export.h"
#include "media/media_video_frame.h"
#include "media/media_capture.h"
#include "components/base/simplelib/simple_string.hpp"

namespace yealink
{
typedef struct _MediaDeviceInfo
{
    SStringA strId;
    SStringA strName;
} MediaDeviceInfo;

enum VideoCodecs
{
    VIDEO_CODEC_NONE = -1,
    VIDEO_CODEC_H263,
    VIDEO_CODEC_H264
};

enum VideoCodecProfile
{
    VIDEO_CODEC_PROFILE_NONE = -1,
    VIDEO_CODEC_PROFILE_BASE,
    VIDEO_CODEC_PROFILE_MAIN,
    VIDEO_CODEC_PROFILE_HIGH,
    VIDEO_CODEC_PROFILE_MAX
};

typedef struct _VideoChannelStats
{
    VideoCodecs codec;
    VideoCodecProfile profile;
    int width;
    int height;
    int frameRate;
    int bitRate;
    int lossRate; //0-100
    int totalLossPackets;
    int jitter; //ms
    int rtt;
    _VideoChannelStats()
        : codec(VIDEO_CODEC_NONE)
        , profile(VIDEO_CODEC_PROFILE_NONE)
        , width(-1)
        , height(-1)
        , frameRate(-1)
        , bitRate(-1)
        , lossRate(-1)
        , totalLossPackets(-1)
        , jitter(-1)
        , rtt(-1)
    {
    }
} VideoChannelStats;

enum AudioCodecs
{
    AUDIO_CODEC_NONE = -1,
    AUDIO_CODEC_ARES,
    AUDIO_CODEC_OPUS,
    AUDIO_CODEC_G722,
    AUDIO_CODEC_G7221,
    AUDIO_CODEC_G7221C,
    AUDIO_CODEC_G729,
    AUDIO_CODEC_AACLC,
    AUDIO_CODEC_PCMU,
    AUDIO_CODEC_PCMA,
};

typedef struct _AudioStreamStats
{
    AudioCodecs codecR;
    AudioCodecs codecS;
    int bitrateR;
    int bitrateS;
    int samplerateR;
    int samplerateS;
    int lossRateR;
    int lossRateS;
    int totalLostPacketsR;
    int totalLostPacketsS;
    int jitterR; //ms
    int jitterS; //ms
    int delayR; //ms
    int delayS; //ms
    _AudioStreamStats()
        : codecR(AUDIO_CODEC_NONE)
        , codecS(AUDIO_CODEC_NONE)
        , bitrateR(-1)
        , bitrateS(-1)
        , samplerateR(-1)
        , samplerateS(-1)
        , lossRateR(-1)
        , lossRateS(-1)
        , totalLostPacketsR(-1)
        , totalLostPacketsS(-1)
        , jitterR(-1)
        , jitterS(-1)
        , delayR(-1)
        , delayS(-1)
    {
    }
} AudioStreamStats;

typedef struct _VideoStreamStats
{
    VideoChannelStats stSend;
    VideoChannelStats stRecv;
} VideoStreamStats;

typedef struct _MediaStreamStats
{
    VideoStreamStats stVideo;
    AudioStreamStats stAudio;
} MediaStreamStats;

typedef struct _ICEProfile
{
    const char* strServer;
    const char* strUserName;
    const char* strPassword;
    int nUDPPort;
    int nTCPPort;
} ICEProfile;

typedef struct _ShareWindow
{
    const void* pHandle;
    int nScreenWidth;
    int nScreenHeight;
    int nMaxSampleRate;
    const char* strCoverImgFile;
    _ShareWindow()
        : pHandle(nullptr)
        , nScreenWidth(0)
        , nScreenHeight(0)
        , nMaxSampleRate(5)
        , strCoverImgFile(nullptr)
    {
    }
} ShareWindow;

class MediaObserver
{
public:
    virtual void OnVideoEvent() = 0;
    virtual void OnAudioEvent() = 0;
};

class MEDIA_EXPORT Media
{
public:
    static Media* CreateInstance(const char* strWorkingPath);
    static void ReleaseInstance(Media* obj);

public:
    virtual ~Media()
    {
    }

public:
    virtual int EnumAudioPlayoutDevices(MediaDeviceInfo descs[], int maxSize) = 0;
    virtual int EnumAudioRecordDevices(MediaDeviceInfo descs[], int maxSize) = 0;
    virtual bool SetAudioPlayoutDevice(const char* id) = 0;
    virtual bool SetAudioRecordDevice(const char* id) = 0;
    virtual bool StartAudioPlayout() = 0;
    virtual void StopAudioPlayout() = 0;
    virtual bool StartAudioRecord() = 0;
    virtual void StopAudioRecord() = 0;
    virtual bool EnableSoundShare(bool enable) = 0;
    virtual bool RestartSoundShare() = 0;
    virtual bool IsAudioPlaying() = 0;
    virtual bool IsAudioRecording() = 0;
    virtual bool Mute(bool mute) = 0;
    virtual bool IsMute() = 0;
    virtual bool SetVolume(int volume) = 0;
    virtual int GetVolume() = 0;
    virtual bool SetEnableANS(bool enable) = 0;
    virtual bool GetEnableANS() = 0;
    virtual bool SetEnableAGC(bool enable) = 0;
    virtual bool GetEnableAGC() = 0;
    virtual int EnumVideoCameraDevice(MediaDeviceInfo descs[], int maxSize) = 0;
    virtual bool SetCamera(const char* strId, bool isPicture) = 0;
    virtual bool SetCameraOrientation(int nOrientation) = 0;
    virtual bool SetShareWindow(const ShareWindow& window) = 0;
    virtual void SetVideoCameraDeviceRender(VideoRender* render) = 0;
    virtual void SetICEProfile(const ICEProfile& profile) = 0;
    virtual void PlayTone(char key) = 0;
    virtual bool PlayRingFile(const char* strFile, bool bLoop) = 0;
    virtual void StopPlayRing() = 0;
    virtual int GetRecentVolume() = 0;
};

} // namespace yealink

#endif
