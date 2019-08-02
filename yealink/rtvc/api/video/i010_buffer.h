#ifndef YEALINK_RTVC_API_VIDEO_I010_BUFFER_H_
#define YEALINK_RTVC_API_VIDEO_I010_BUFFER_H_

#include <stdint.h>
#include <memory>

#include "base/memory/aligned_memory.h"
#include "base/memory/scoped_refptr.h"
#include "yealink/rtvc/api/video/video_frame_buffer.h"
#include "yealink/rtvc/api/video/video_rotation.h"

namespace yealink {

namespace rtvc {

class I010BufferImpl : public I010Buffer {
 public:
  // Create a new buffer.
  static scoped_refptr<I010BufferImpl> Create(int width, int height);

  // Create a new buffer and copy the pixel data.
  static scoped_refptr<I010BufferImpl> Copy(const I010Buffer& buffer);

  // Convert and put I420 buffer into a new buffer.
  static scoped_refptr<I010BufferImpl> Copy(const I420Buffer& buffer);

  // Return a rotated copy of |src|.
  static scoped_refptr<I010BufferImpl> Rotate(const I010Buffer& src,
                                              VideoRotation rotation);

  // VideoFrameBuffer implementation.
  scoped_refptr<I420Buffer> ToI420() override;

  // PlanarYuv16BBuffer implementation.
  int width() const override;
  int height() const override;
  const uint16_t* DataY() const override;
  const uint16_t* DataU() const override;
  const uint16_t* DataV() const override;
  int StrideY() const override;
  int StrideU() const override;
  int StrideV() const override;

  uint16_t* MutableDataY();
  uint16_t* MutableDataU();
  uint16_t* MutableDataV();

  // Scale the cropped area of |src| to the size of |this| buffer, and
  // write the result into |this|.
  void CropAndScaleFrom(const I010Buffer& src,
                        int offset_x,
                        int offset_y,
                        int crop_width,
                        int crop_height);

  // Scale all of |src| to the size of |this| buffer, with no cropping.
  void ScaleFrom(const I010Buffer& src);

  // Pastes whole picture to canvas at (offset_row, offset_col).
  // Offsets and picture dimensions must be even.
  void PasteFrom(const I010Buffer& picture, int offset_col, int offset_row);

 protected:
  I010BufferImpl(int width,
                 int height,
                 int stride_y,
                 int stride_u,
                 int stride_v);
  ~I010BufferImpl() override;

 private:
  const int width_;
  const int height_;
  const int stride_y_;
  const int stride_u_;
  const int stride_v_;
  const std::unique_ptr<uint16_t, base::AlignedFreeDeleter> data_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_VIDEO_I010_BUFFER_H_
