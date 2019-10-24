#include "yealink/rtvc/api/video/i420_buffer.h"

#include <string.h>
#include <algorithm>
#include <utility>

#include "base/logging.h"
#include "third_party/libyuv/include/libyuv/convert.h"
#include "third_party/libyuv/include/libyuv/planar_functions.h"
#include "third_party/libyuv/include/libyuv/scale.h"

// Aligning pointer to 64 bytes for improved performance, e.g. use SIMD.
static const int kBufferAlignment = 64;

namespace rtvc {

namespace {

int I420DataSize(int height, int stride_y, int stride_u, int stride_v) {
  return stride_y * height + (stride_u + stride_v) * ((height + 1) / 2);
}

}  // namespace

I420BufferImpl::I420BufferImpl(int width, int height)
    : I420BufferImpl(width, height, width, (width + 1) / 2, (width + 1) / 2) {}

I420BufferImpl::I420BufferImpl(int width,
                               int height,
                               int stride_y,
                               int stride_u,
                               int stride_v)
    : width_(width),
      height_(height),
      stride_y_(stride_y),
      stride_u_(stride_u),
      stride_v_(stride_v),
      data_(static_cast<uint8_t*>(
          // base::AlignedAlloc(I420DataSize(height, stride_y, stride_u, stride_v),
          webrtc::AlignedMalloc(I420DataSize(height, stride_y, stride_u, stride_v),
                             kBufferAlignment))) {
  DCHECK_GT(width, 0);
  DCHECK_GT(height, 0);
  DCHECK_GE(stride_y, width);
  DCHECK_GE(stride_u, (width + 1) / 2);
  DCHECK_GE(stride_v, (width + 1) / 2);
}

I420BufferImpl::~I420BufferImpl() {}

// static
scoped_refptr<I420BufferImpl> I420BufferImpl::Create(int width, int height) {
  return base::WrapRefCounted<I420BufferImpl>(
      new I420BufferImpl(width, height));
}

// static
scoped_refptr<I420BufferImpl> I420BufferImpl::Create(int width,
                                                     int height,
                                                     int stride_y,
                                                     int stride_u,
                                                     int stride_v) {
  return base::WrapRefCounted<I420BufferImpl>(
      new I420BufferImpl(width, height, stride_y, stride_u, stride_v));
}

// static
scoped_refptr<I420BufferImpl> I420BufferImpl::Copy(const I420Buffer& source) {
  return Copy(source.width(), source.height(), source.DataY(), source.StrideY(),
              source.DataU(), source.StrideU(), source.DataV(),
              source.StrideV());
}

// static
scoped_refptr<I420BufferImpl> I420BufferImpl::Copy(int width,
                                                   int height,
                                                   const uint8_t* data_y,
                                                   int stride_y,
                                                   const uint8_t* data_u,
                                                   int stride_u,
                                                   const uint8_t* data_v,
                                                   int stride_v) {
  // Note: May use different strides than the input data.
  scoped_refptr<I420BufferImpl> buffer = Create(width, height);
  CHECK_EQ(0, libyuv::I420Copy(data_y, stride_y, data_u, stride_u, data_v,
                               stride_v, buffer->MutableDataY(),
                               buffer->StrideY(), buffer->MutableDataU(),
                               buffer->StrideU(), buffer->MutableDataV(),
                               buffer->StrideV(), width, height));
  return buffer;
}

// static
scoped_refptr<I420BufferImpl> I420BufferImpl::Rotate(const I420Buffer& src,
                                                     VideoRotation rotation) {
  CHECK(src.DataY());
  CHECK(src.DataU());
  CHECK(src.DataV());

  int rotated_width = src.width();
  int rotated_height = src.height();
  if (rotation == kVideoRotation_90 || rotation == kVideoRotation_270) {
    std::swap(rotated_width, rotated_height);
  }

  scoped_refptr<I420BufferImpl> buffer =
      I420BufferImpl::Create(rotated_width, rotated_height);

  CHECK_EQ(0, libyuv::I420Rotate(
                  src.DataY(), src.StrideY(), src.DataU(), src.StrideU(),
                  src.DataV(), src.StrideV(), buffer->MutableDataY(),
                  buffer->StrideY(), buffer->MutableDataU(), buffer->StrideU(),
                  buffer->MutableDataV(), buffer->StrideV(), src.width(),
                  src.height(), static_cast<libyuv::RotationMode>(rotation)));

  return buffer;
}

void I420BufferImpl::InitializeData() {
  memset(data_.get(), 0,
         I420DataSize(height_, stride_y_, stride_u_, stride_v_));
}

int I420BufferImpl::width() const {
  return width_;
}

int I420BufferImpl::height() const {
  return height_;
}

const uint8_t* I420BufferImpl::DataY() const {
  return data_.get();
}
const uint8_t* I420BufferImpl::DataU() const {
  return data_.get() + stride_y_ * height_;
}
const uint8_t* I420BufferImpl::DataV() const {
  return data_.get() + stride_y_ * height_ + stride_u_ * ((height_ + 1) / 2);
}

int I420BufferImpl::StrideY() const {
  return stride_y_;
}
int I420BufferImpl::StrideU() const {
  return stride_u_;
}
int I420BufferImpl::StrideV() const {
  return stride_v_;
}

uint8_t* I420BufferImpl::MutableDataY() {
  return const_cast<uint8_t*>(DataY());
}
uint8_t* I420BufferImpl::MutableDataU() {
  return const_cast<uint8_t*>(DataU());
}
uint8_t* I420BufferImpl::MutableDataV() {
  return const_cast<uint8_t*>(DataV());
}

// static
void I420BufferImpl::SetBlack(I420BufferImpl* buffer) {
  CHECK(libyuv::I420Rect(buffer->MutableDataY(), buffer->StrideY(),
                         buffer->MutableDataU(), buffer->StrideU(),
                         buffer->MutableDataV(), buffer->StrideV(), 0, 0,
                         buffer->width(), buffer->height(), 0, 128, 128) == 0);
}

void I420BufferImpl::CropAndScaleFrom(const I420Buffer& src,
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

  const uint8_t* y_plane = src.DataY() + src.StrideY() * offset_y + offset_x;
  const uint8_t* u_plane =
      src.DataU() + src.StrideU() * uv_offset_y + uv_offset_x;
  const uint8_t* v_plane =
      src.DataV() + src.StrideV() * uv_offset_y + uv_offset_x;
  int res =
      libyuv::I420Scale(y_plane, src.StrideY(), u_plane, src.StrideU(), v_plane,
                        src.StrideV(), crop_width, crop_height, MutableDataY(),
                        StrideY(), MutableDataU(), StrideU(), MutableDataV(),
                        StrideV(), width(), height(), libyuv::kFilterBox);

  DCHECK_EQ(res, 0);
}

void I420BufferImpl::CropAndScaleFrom(const I420Buffer& src) {
  const int crop_width =
      std::min(src.width(), width() * src.height() / height());
  const int crop_height =
      std::min(src.height(), height() * src.width() / width());

  CropAndScaleFrom(src, (src.width() - crop_width) / 2,
                   (src.height() - crop_height) / 2, crop_width, crop_height);
}

void I420BufferImpl::ScaleFrom(const I420Buffer& src) {
  CropAndScaleFrom(src, 0, 0, src.width(), src.height());
}

void I420BufferImpl::PasteFrom(const I420Buffer& picture,
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

  libyuv::CopyPlane(picture.DataY(), picture.StrideY(),
                    MutableDataY() + StrideY() * offset_row + offset_col,
                    StrideY(), picture.width(), picture.height());

  libyuv::CopyPlane(
      picture.DataU(), picture.StrideU(),
      MutableDataU() + StrideU() * offset_row / 2 + offset_col / 2, StrideU(),
      picture.width() / 2, picture.height() / 2);

  libyuv::CopyPlane(
      picture.DataV(), picture.StrideV(),
      MutableDataV() + StrideV() * offset_row / 2 + offset_col / 2, StrideV(),
      picture.width() / 2, picture.height() / 2);
}

}  // namespace rtvc
