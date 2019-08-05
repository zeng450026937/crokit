/*!
* @file media_capture.h
* @date 2019/06/18
*
* @brief 
*
*/
#ifndef __MEDIA_CAPTURE_H__
#define __MEDIA_CAPTURE_H__

#include "media/media_video_frame.h"

namespace yealink
{
typedef struct _CaptureFrame
{
    VideoRawDataType typeFrame;
    int nWidth;
    int nHeight;
    VideoFrame::PlaneData arrData[3];
    int nDataCount;
    _CaptureFrame()
        : typeFrame(VideoRawDataType::VIDEO_RAW_DATA_UNKNOWN)
        , nWidth(0)
        , nHeight(0)
        , nDataCount(0)
    {
    }
} CaptureFrame;

class FrameDeliverySink
{
public:
    enum RotaionMode
    {
        RM_0,
        RM_90,
        RM_180,
        RM_270,
    };

public:
    static void AllocI420FrameData(CaptureFrame& frame, int nWidth, int nHeight);
    static void FreeFrameData(CaptureFrame& frame);
    /**
    * @brief Convert and rotation to I420.
    *
    * @param[in] frameRaw
    * @param[in] mode
    * @param[out] frameNew
    * @return bool
    */
    static bool NV12ToI420Rotate(const CaptureFrame& frameRaw, CaptureFrame& frameNew, RotaionMode mode);
    static bool NV21ToI420(const CaptureFrame& frameRaw, CaptureFrame& frameNew);
    static bool I420Scale(const CaptureFrame& frameRaw, CaptureFrame& frameNew);
    static bool I420Rotate(const CaptureFrame& frameRaw, CaptureFrame& frameNew, RotaionMode mode);

public:
    virtual void OnFrame(const CaptureFrame& frame) = 0;
};

class MediaCapture
{
public:
    virtual bool ConnectSink(FrameDeliverySink* sink) = 0;
    virtual void DisconnectSink(FrameDeliverySink* sink) = 0;
    virtual bool SetBestResolution(int nWidth, int nHeight) = 0;
};
} // namespace yealink

#endif //__MEDIA_CAPTURE_H__