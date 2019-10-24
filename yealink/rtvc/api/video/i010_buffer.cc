#include "yealink/rtvc/api/video/i010_buffer.h"

#include <utility>

#include "base/logging.h"
#include "third_party/libyuv/include/libyuv/convert.h"
#include "third_party/libyuv/include/libyuv/scale.h"
#include "yealink/rtvc/api/video/i420_buffer.h"

// Aligning pointer to 64 bytes for improved performance, e.g. use SIMD.
static const int kBufferAlignment = 64;
static const int kBytesPerPixel = 2;

namespace rtvc {

namespace {

int I010DataSize(int height, int stride_y, int stride_u, int stride_v) {
  return kBytesPerPixel *
         (stride_y * height + (stride_u + stride_v) * ((height + 1) / 2));
}

}  // namespace

I010BufferImpl::I010BufferImpl(int width,
                               int height,
                               int stride_y,
                               int stride_u,
                               int stride_v)
    : width_(width),
      height_(height),
      stride_y_(stride_y),
      stride_u_(stride_u),
      stride_v_(stride_v),
      data_(static_cast<uint16_t*>(
          // base::AlignedAlloc(I010DataSize(height, stride_y, stride_u, stride_v),
          webrtc::AlignedMalloc(I010DataSize(height, stride_y, stride_u, stride_v),
                             kBufferAlignment))) {
  DCHECK_GT(width, 0);
  DCHECK_GT(height, 0);
  DCHECK_GE(stride_y, width);
  DCHECK_GE(stride_u, (width + 1) / 2);
  DCHECK_GE(stride_v, (width + 1) / 2);
}

I010BufferImpl::~I010BufferImpl() {}

// static
scoped_refptr<I010BufferImpl> I010BufferImpl::Create(int width, int height) {
  return base::WrapRefCounted<I010BufferImpl>(new I010BufferImpl(
      width, height, width, (width + 1) / 2, (width + 1) / 2));
}

// static
scoped_refptr<I010BufferImpl> I010BufferImpl::Copy(const I010Buffer& source) {
  const int width = source.width();
  const int height = source.height();
  scoped_refptr<I010BufferImpl> buffer = Create(width, height);
  CHECK_EQ(0, libyuv::I010Copy(source.DataY(), source.StrideY(), source.DataU(),
                               source.StrideU(), source.DataV(),
                               source.StrideV(), buffer->MutableDataY(),
                               buffer->StrideY(), buffer->MutableDataU(),
                               buffer->StrideU(), buffer->MutableDataV(),
                               buffer->StrideV(), width, height));
  return buffer;
}

// static
scoped_refptr<I010BufferImpl> I010BufferImpl::Copy(const I420Buffer& source) {
  const int width = source.width();
  const int height = source.height();
  scoped_refptr<I010BufferImpl> buffer = Create(width, height);
  CHECK_EQ(
      0, libyuv::I420ToI010(
             source.DataY(), source.StrideY(), source.DataU(), source.StrideU(),
             source.DataV(), source.StrideV(), buffer->MutableDataY(),
             buffer->StrideY(), buffer->MutableDataU(), buffer->StrideU(),
             buffer->MutableDataV(), buffer->StrideV(), width, height));
  return buffer;
}

// static
scoped_refptr<I010BufferImpl> I010BufferImpl::Rotate(const I010Buffer& src,
                                                     VideoRotation rotation) {
  if (rotation == kVideoRotation_0)
    return Copy(src);

  CHECK(src.DataY());
  CHECK(src.DataU());
  CHECK(src.DataV());
  int rotated_width = src.width();
  int rotated_height = src.height();
  if (rotation == kVideoRotation_90 || rotation == kVideoRotation_270) {
    std::swap(rotated_width, rotated_height);
  }

  scoped_refptr<I010BufferImpl> buffer = Create(rotated_width, rotated_height);
  // TODO(emircan): Remove this when there is libyuv::I010Rotate().
  for (int x = 0; x < src.width(); x++) {
    for (int y = 0; y < src.height(); y++) {
      int dest_x = x;
      int dest_y = y;
      switch (rotation) {
        // This case is covered by the early return.
        case kVideoRotation_0:
          NOTREACHED();
          break;
        case kVideoRotation_90:
          dest_x = src.height() - y - 1;
          dest_y = x;
          break;
        case kVideoRotation_180:
          dest_x = src.width() - x - 1;
          dest_y = src.height() - y - 1;
          break;
        case kVideoRotation_270:
          dest_x = y;
          dest_y = src.width() - x - 1;
          break;
      }
      buffer->MutableDataY()[dest_x + buffer->StrideY() * dest_y] =
          src.DataY()[x + src.StrideY() * y];
      dest_x /= 2;
      dest_y /= 2;
      int src_x = x / 2;
      int src_y = y / 2;
      buffer->MutableDataU()[dest_x + buffer->StrideU() * dest_y] =
          src.DataU()[src_x + src.StrideU() * src_y];
      buffer->MutableDataV()[dest_x + buffer->StrideV() * dest_y] =
          src.DataV()[src_x + src.StrideV() * src_y];
    }
  }
  return buffer;
}

scoped_refptr<I420Buffer> I010BufferImpl::ToI420() {
  scoped_refptr<I420BufferImpl> i420_buffer =
      I420BufferImpl::Create(width(), height());
  libyuv::I010ToI420(DataY(), StrideY(), DataU(), StrideU(), DataV(), StrideV(),
                     i420_buffer->MutableDataY(), i420_buffer->StrideY(),
                     i420_buffer->MutableDataU(), i420_buffer->StrideU(),
                     i420_buffer->MutableDataV(), i420_buffer->StrideV(),
                     width(), height());
  return i420_buffer;
}

int I010BufferImpl::width() const {
  return width_;
}

int I010BufferImpl::height() const {
  return height_;
}

const uint16_t* I010BufferImpl::DataY() const {
  return data_.get();
}
const uint16_t* I010BufferImpl::DataU() const {
  return data_.get() + stride_y_ * height_;
}
const uint16_t* I010BufferImpl::DataV() const {
  return data_.get() + stride_y_ * height_ + stride_u_ * ((height_ + 1) / 2);
}

int I010BufferImpl::StrideY() const {
  return stride_y_;
}
int I010BufferImpl::StrideU() const {
  return stride_u_;
}
int I010BufferImpl::StrideV() const {
  return stride_v_;
}

uint16_t* I010BufferImpl::MutableDataY() {
  return const_cast<uint16_t*>(DataY());
}
uint16_t* I010BufferImpl::MutableDataU() {
  return const_cast<uint16_t*>(DataU());
}
uint16_t* I010BufferImpl::MutableDataV() {
  return const_cast<uint16_t*>(DataV());
}

void I010BufferImpl::CropAndScaleFrom(const I010Buffer& src,
                                      int offset_x,
                                      int offset_y,
                                      int crop_width,
                                      int crop_height) {
  CHECK_LE(crop_width, src.width());
  CHECK_LE(crop_height, src.height());
  CHECK_LE(crop_width + offset_x, src.width());
  CHECK_LE(crop_height + offset_y, src.height());
  CHECK_GE(offset_x, 0);
  CHECK_GE(offset_y, 0);

  // Make sure offset is even so that u/v plane becomes aligned.
  const int uv_offset_x = offset_x / 2;
  const int uv_offset_y = offset_y / 2;
  offset_x = uv_offset_x * 2;
  offset_y = uv_offset_y * 2;

  const uint16_t* y_plane = src.DataY() + src.StrideY() * offset_y + offset_x;
  const uint16_t* u_plane =
      src.DataU() + src.StrideU() * uv_offset_y + uv_offset_x;
  const uint16_t* v_plane =
      src.DataV() + src.StrideV() * uv_offset_y + uv_offset_x;
  int res = libyuv::I420Scale_16(
      y_plane, src.StrideY(), u_plane, src.StrideU(), v_plane, src.StrideV(),
      crop_width, crop_height, MutableDataY(), StrideY(), MutableDataU(),
      StrideU(), MutableDataV(), StrideV(), width(), height(),
      libyuv::kFilterBox);

  DCHECK_EQ(res, 0);
}

void I010BufferImpl::ScaleFrom(const I010Buffer& src) {
  CropAndScaleFrom(src, 0, 0, src.width(), src.height());
}

void I010BufferImpl::PasteFrom(const I010Buffer& picture,
                               int offset_col,
                               int offset_row) {
  CHECK_LE(picture.width() + offset_col, width());
  CHECK_LE(picture.height() + offset_row, height());
  CHECK_GE(offset_col, 0);
  CHECK_GE(offset_row, 0);

  // Pasted picture has to be aligned so subsumpled UV plane isn't corrupted.
  CHECK(offset_col % 2 == 0);
  CHECK(offset_row % 2 == 0);
  CHECK(picture.width() % 2 == 0 || picture.width() + offset_col == width());
  CHECK(picture.height() % 2 == 0 || picture.height() + offset_row == height());

  libyuv::CopyPlane_16(picture.DataY(), picture.StrideY(),
                       MutableDataY() + StrideY() * offset_row + offset_col,
                       StrideY(), picture.width(), picture.height());

  libyuv::CopyPlane_16(
      picture.DataU(), picture.StrideU(),
      MutableDataU() + StrideU() * offset_row / 2 + offset_col / 2, StrideU(),
      picture.width() / 2, picture.height() / 2);

  libyuv::CopyPlane_16(
      picture.DataV(), picture.StrideV(),
      MutableDataV() + StrideV() * offset_row / 2 + offset_col / 2, StrideV(),
      picture.width() / 2, picture.height() / 2);
}

}  // namespace rtvc
