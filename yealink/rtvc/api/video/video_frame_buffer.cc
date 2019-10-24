#include "yealink/rtvc/api/video/video_frame_buffer.h"

#include "base/logging.h"

namespace rtvc {

scoped_refptr<I420Buffer> VideoFrameBuffer::GetI420() {
  CHECK(type() == Type::kI420);
  return static_cast<I420Buffer*>(this);
}

scoped_refptr<const I420Buffer> VideoFrameBuffer::GetI420() const {
  CHECK(type() == Type::kI420);
  return static_cast<const I420Buffer*>(this);
}

I420ABuffer* VideoFrameBuffer::GetI420A() {
  CHECK(type() == Type::kI420A);
  return static_cast<I420ABuffer*>(this);
}

const I420ABuffer* VideoFrameBuffer::GetI420A() const {
  CHECK(type() == Type::kI420A);
  return static_cast<const I420ABuffer*>(this);
}

I444Buffer* VideoFrameBuffer::GetI444() {
  CHECK(type() == Type::kI444);
  return static_cast<I444Buffer*>(this);
}

const I444Buffer* VideoFrameBuffer::GetI444() const {
  CHECK(type() == Type::kI444);
  return static_cast<const I444Buffer*>(this);
}

I010Buffer* VideoFrameBuffer::GetI010() {
  CHECK(type() == Type::kI010);
  return static_cast<I010Buffer*>(this);
}

const I010Buffer* VideoFrameBuffer::GetI010() const {
  CHECK(type() == Type::kI010);
  return static_cast<const I010Buffer*>(this);
}

VideoFrameBuffer::Type I420Buffer::type() const {
  return Type::kI420;
}

int I420Buffer::ChromaWidth() const {
  return (width() + 1) / 2;
}

int I420Buffer::ChromaHeight() const {
  return (height() + 1) / 2;
}

scoped_refptr<I420Buffer> I420Buffer::ToI420() {
  return this;
}

VideoFrameBuffer::Type I420ABuffer::type() const {
  return Type::kI420A;
}

VideoFrameBuffer::Type I444Buffer::type() const {
  return Type::kI444;
}

int I444Buffer::ChromaWidth() const {
  return width();
}

int I444Buffer::ChromaHeight() const {
  return height();
}

VideoFrameBuffer::Type I010Buffer::type() const {
  return Type::kI010;
}

int I010Buffer::ChromaWidth() const {
  return (width() + 1) / 2;
}

int I010Buffer::ChromaHeight() const {
  return (height() + 1) / 2;
}

}  // namespace rtvc
