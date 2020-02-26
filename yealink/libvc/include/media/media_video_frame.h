/*!
* @file media_video_frame.h
* @date 2019/05/28
*
* @brief 
*
*/
#ifndef __MEDIA_VIDEO_FRAME_H__
#define __MEDIA_VIDEO_FRAME_H__

#include "media/media_export.h"

namespace yealink
{
enum VideoRawDataType
{
    VIDEO_RAW_DATA_I420 = 0,
    VIDEO_RAW_DATA_YV12 = 1,
    VIDEO_RAW_DATA_YUY2 = 2,
    VIDEO_RAW_DATA_UYVY = 3,
    VIDEO_RAW_DATA_IYUV = 4,
    VIDEO_RAW_DATA_ARGB = 5,
    VIDEO_RAW_DATA_RGB24 = 6,
    VIDEO_RAW_DATA_RGB565 = 7,
    VIDEO_RAW_DATA_ARGB4444 = 8,
    VIDEO_RAW_DATA_ARGB1555 = 9,
    VIDEO_RAW_DATA_MJPEG = 10,
    VIDEO_RAW_DATA_NV12 = 11,
    VIDEO_RAW_DATA_NV21 = 12,
    VIDEO_RAW_DATA_BGRA = 13,
    VIDEO_RAW_DATA_UNKNOWN = 99
};

class MEDIA_EXPORT VideoFrame
{
public:
    typedef int PlaneType;
    struct PlaneValueType
    {
        static const PlaneType kYPlane = 0;
        static const PlaneType kUPlane = 1;
        static const PlaneType kVPlane = 2;
    };
    struct PlaneData
    {
        void* data;
        int len;
        int stride;
        PlaneData()
            : data(nullptr)
            , len(0)
            , stride(0)
        {
        }
    };

public:
    /*
     @ biref buf size = width * height * 4 (bytes);
    */
    static bool ConvertToARGB32(const VideoFrame& frame, const void* buf, int width, int height);
    static void CopyPlane(const unsigned char* src, int src_stride, unsigned char* dst, int dst_stride, int width, int height);

public:
    VideoFrame();
    VideoFrame(const VideoFrame& right);
    virtual ~VideoFrame();

public:
    VideoFrame& operator=(const VideoFrame& right);

public:
    virtual VideoRawDataType RawDataType() const;
    virtual int Width() const;
    virtual int Height() const;
    virtual int PlaneCount() const;
    virtual PlaneData GetData(PlaneType type) const;

protected:
    void* m_pData;
};

class MEDIA_EXPORT VideoRender
{
public:
    virtual void OnVideoFrame(const VideoFrame& frame, unsigned int id) = 0;

protected:
    virtual ~VideoRender()
    {
    }
};
} // namespace yealink
#endif //__MEDIA_VIDEO_FRAME_H__