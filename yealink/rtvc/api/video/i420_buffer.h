#ifndef YEALINK_RTVC_API_VIDEO_I420_BUFFER_H_
#define YEALINK_RTVC_API_VIDEO_I420_BUFFER_H_

#include <stdint.h>
#include <memory>

#include "base/memory/aligned_memory.h"
#include "base/memory/scoped_refptr.h"
#include "yealink/rtvc/api/video/video_frame_buffer.h"
#include "yealink/rtvc/api/video/video_rotation.h"

namespace yealink {

namespace rtvc {

class I420BufferImpl : public I420Buffer {
 public:
  static scoped_refptr<I420BufferImpl> Create(int width, int height);
  static scoped_refptr<I420BufferImpl> Create(int width,
                                              int height,
                                              int stride_y,
                                              int stride_u,
                                              int stride_v);

  // Create a new buffer and copy the pixel data.
  static scoped_refptr<I420BufferImpl> Copy(const I420Buffer& buffer);
  // Deprecated.
  static scoped_refptr<I420BufferImpl> Copy(const VideoFrameBuffer& buffer) {
    return Copy(*buffer.GetI420());
  }

  static scoped_refptr<I420BufferImpl> Copy(int width,
                                            int height,
                                            const uint8_t* data_y,
                                            int stride_y,
                                            const uint8_t* data_u,
                                            int stride_u,
                                            const uint8_t* data_v,
                                            int stride_v);

  // Returns a rotated copy of |src|.
  static scoped_refptr<I420BufferImpl> Rotate(const I420Buffer& src,
                                              VideoRotation rotation);
  // Deprecated.
  static scoped_refptr<I420BufferImpl> Rotate(const VideoFrameBuffer& src,
                                              VideoRotation rotation) {
    return Rotate(*src.GetI420(), rotation);
  }

  // Sets the buffer to all black.
  static void SetBlack(I420BufferImpl* buffer);

  // Sets all three planes to all zeros. Used to work around for
  // quirks in memory checkers
  // (https://bugs.chromium.org/p/libyuv/issues/detail?id=377) and
  // ffmpeg (http://crbug.com/390941).
  // TODO(nisse): Deprecated. Should be deleted if/when those issues
  // are resolved in a better way. Or in the mean time, use SetBlack.
  void InitializeData();

  int width() const override;
  int height() const override;
  const uint8_t* DataY() const override;
  const uint8_t* DataU() const override;
  const uint8_t* DataV() const override;

  int StrideY() const override;
  int StrideU() const override;
  int StrideV() const override;

  uint8_t* MutableDataY();
  uint8_t* MutableDataU();
  uint8_t* MutableDataV();

  // Scale the cropped area of |src| to the size of |this| buffer, and
  // write the result into |this|.
  void CropAndScaleFrom(const I420Buffer& src,
                        int offset_x,
                        int offset_y,
                        int crop_width,
                        int crop_height);

  // The common case of a center crop, when needed to adjust the
  // aspect ratio without distorting the image.
  void CropAndScaleFrom(const I420Buffer& src);

  // Scale all of |src| to the size of |this| buffer, with no cropping.
  void ScaleFrom(const I420Buffer& src);

  // Pastes whole picture to canvas at (offset_row, offset_col).
  // Offsets and picture dimensions must be even.
  void PasteFrom(const I420Buffer& picture, int offset_col, int offset_row);

 protected:
  I420BufferImpl(int width, int height);
  I420BufferImpl(int width,
                 int height,
                 int stride_y,
                 int stride_u,
                 int stride_v);

  ~I420BufferImpl() override;

 private:
  const int width_;
  const int height_;
  const int stride_y_;
  const int stride_u_;
  const int stride_v_;
  const std::unique_ptr<uint8_t, base::AlignedFreeDeleter> data_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_VIDEO_I420_BUFFER_H_
