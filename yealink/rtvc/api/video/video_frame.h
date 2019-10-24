#ifndef YEALINK_RTVC_API_VIDEO_VIDEO_FRAME_H_
#define YEALINK_RTVC_API_VIDEO_VIDEO_FRAME_H_

#include <stdint.h>

#include "base/optional.h"
#include "yealink/rtvc/api/video/video_frame_buffer.h"
#include "yealink/rtvc/api/video/video_rotation.h"

namespace rtvc {

class VideoFrame {
 public:
  struct UpdateRect {
    int offset_x;
    int offset_y;
    int width;
    int height;

    // Makes this UpdateRect a bounding box of this and other rect.
    void Union(const UpdateRect& other);

    // Makes this UpdateRect an intersection of this and other rect.
    void Intersect(const UpdateRect& other);

    // Sets everything to 0, making this UpdateRect a zero-size (empty) update.
    void MakeEmptyUpdate();

    bool IsEmpty() const;
  };

  // Preferred way of building VideoFrame objects.
  class Builder {
   public:
    Builder();
    ~Builder();

    VideoFrame build();
    Builder& set_video_frame_buffer(
        const scoped_refptr<VideoFrameBuffer>& buffer);
    Builder& set_timestamp_ms(int64_t timestamp_ms);
    Builder& set_timestamp_us(int64_t timestamp_us);
    Builder& set_timestamp_rtp(uint32_t timestamp_rtp);
    Builder& set_ntp_time_ms(int64_t ntp_time_ms);
    Builder& set_rotation(VideoRotation rotation);
    Builder& set_id(uint16_t id);
    Builder& set_update_rect(const UpdateRect& update_rect);

   private:
    uint16_t id_ = 0;
    scoped_refptr<VideoFrameBuffer> video_frame_buffer_;
    int64_t timestamp_us_ = 0;
    uint32_t timestamp_rtp_ = 0;
    int64_t ntp_time_ms_ = 0;
    VideoRotation rotation_ = kVideoRotation_0;
    base::Optional<UpdateRect> update_rect_;
  };

  // To be deprecated. Migrate all use to Builder.
  VideoFrame(const scoped_refptr<VideoFrameBuffer>& buffer,
             VideoRotation rotation,
             int64_t timestamp_us);
  VideoFrame(const scoped_refptr<VideoFrameBuffer>& buffer,
             uint32_t timestamp_rtp,
             int64_t render_time_ms,
             VideoRotation rotation);

  ~VideoFrame();

  // Support move and copy.
  VideoFrame(const VideoFrame&);
  VideoFrame(VideoFrame&&);
  VideoFrame& operator=(const VideoFrame&);
  VideoFrame& operator=(VideoFrame&&);

  // Get frame width.
  int width() const;
  // Get frame height.
  int height() const;
  // Get frame size in pixels.
  uint32_t size() const;

  // Get frame ID. Returns 0 if ID is not set. Not guarantee to be transferred
  // from the sender to the receiver, but preserved on single side. The id
  // should be propagated between all frame modifications during its lifetime
  // from capturing to sending as encoded image. It is intended to be unique
  // over a time window of a few minutes for peer connection, to which
  // corresponding video stream belongs to.
  uint16_t id() const { return id_; }
  void set_id(uint16_t id) { id_ = id; }

  // System monotonic clock, same timebase as TimeMicros().
  int64_t timestamp_us() const { return timestamp_us_; }
  void set_timestamp_us(int64_t timestamp_us) { timestamp_us_ = timestamp_us; }

  // TODO(nisse): After the cricket::VideoFrame and webrtc::VideoFrame
  // merge, timestamps other than timestamp_us will likely be
  // deprecated.

  // Set frame timestamp (90kHz).
  void set_timestamp(uint32_t timestamp) { timestamp_rtp_ = timestamp; }

  // Get frame timestamp (90kHz).
  uint32_t timestamp() const { return timestamp_rtp_; }

  // For now, transport_frame_id and rtp timestamp are the same.
  // TODO(nisse): Must be handled differently for QUIC.
  uint32_t transport_frame_id() const { return timestamp(); }

  // Set capture ntp time in milliseconds.
  // TODO(nisse): Deprecated. Migrate all users to timestamp_us().
  void set_ntp_time_ms(int64_t ntp_time_ms) { ntp_time_ms_ = ntp_time_ms; }

  // Get capture ntp time in milliseconds.
  // TODO(nisse): Deprecated. Migrate all users to timestamp_us().
  int64_t ntp_time_ms() const { return ntp_time_ms_; }

  // Naming convention for Coordination of Video Orientation. Please see
  // http://www.etsi.org/deliver/etsi_ts/126100_126199/126114/12.07.00_60/ts_126114v120700p.pdf
  //
  // "pending rotation" or "pending" = a frame that has a VideoRotation > 0.
  //
  // "not pending" = a frame that has a VideoRotation == 0.
  //
  // "apply rotation" = modify a frame from being "pending" to being "not
  //                    pending" rotation (a no-op for "unrotated").
  //
  VideoRotation rotation() const { return rotation_; }
  void set_rotation(VideoRotation rotation) { rotation_ = rotation; }

  // Get render time in milliseconds.
  // TODO(nisse): Deprecated. Migrate all users to timestamp_us().
  int64_t render_time_ms() const;

  // Return the underlying buffer. Never nullptr for a properly
  // initialized VideoFrame.
  scoped_refptr<VideoFrameBuffer> video_frame_buffer() const;

  // TODO(nisse): Deprecated.
  // Return true if the frame is stored in a texture.
  bool is_texture() const {
    return video_frame_buffer()->type() == VideoFrameBuffer::Type::kNative;
  }

  // Always initialized to whole frame update, can be set by Builder or manually
  // by |set_update_rect|.
  UpdateRect update_rect() const { return update_rect_; }
  // Rectangle must be within the frame dimensions.
  void set_update_rect(const VideoFrame::UpdateRect& update_rect) {
    DCHECK_GE(update_rect.offset_x, 0);
    DCHECK_GE(update_rect.offset_y, 0);
    DCHECK_LE(update_rect.offset_x + update_rect.width, width());
    DCHECK_LE(update_rect.offset_y + update_rect.height, height());
    update_rect_ = update_rect;
  }

 private:
  VideoFrame(uint16_t id,
             const scoped_refptr<VideoFrameBuffer>& buffer,
             int64_t timestamp_us,
             uint32_t timestamp_rtp,
             int64_t ntp_time_ms,
             VideoRotation rotation,
             const base::Optional<UpdateRect>& update_rect);

  uint16_t id_;
  // An opaque reference counted handle that stores the pixel data.
  scoped_refptr<VideoFrameBuffer> video_frame_buffer_;
  uint32_t timestamp_rtp_;
  int64_t ntp_time_ms_;
  int64_t timestamp_us_;
  VideoRotation rotation_;
  // Updated since the last frame area. Unless set explicitly, will always be
  // a full frame rectangle.
  UpdateRect update_rect_;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_API_VIDEO_VIDEO_FRAME_H_
