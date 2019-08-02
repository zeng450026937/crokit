#ifndef YEALINK_RTVC_API_VIDEO_VIDEO_FRAME_BUFFER_H_
#define YEALINK_RTVC_API_VIDEO_VIDEO_FRAME_BUFFER_H_

#include <stdint.h>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_refptr.h"

namespace yealink {

namespace rtvc {

class I420Buffer;
class I420ABuffer;
class I444Buffer;
class I010Buffer;

class VideoFrameBuffer : public base::RefCounted<VideoFrameBuffer> {
 public:
  // New frame buffer types will be added conservatively when there is an
  // opportunity to optimize the path between some pair of video source and
  // video sink.
  enum class Type {
    kNative,
    kI420,
    kI420A,
    kI444,
    kI010,
  };

  // This function specifies in what pixel format the data is stored in.
  virtual Type type() const = 0;

  // The resolution of the frame in pixels. For formats where some planes are
  // subsampled, this is the highest-resolution plane.
  virtual int width() const = 0;
  virtual int height() const = 0;

  // Returns a memory-backed frame buffer in I420 format. If the pixel data is
  // in another format, a conversion will take place. All implementations must
  // provide a fallback to I420 for compatibility with e.g. the internal WebRTC
  // software encoders.
  virtual scoped_refptr<I420Buffer> ToI420() = 0;

  // These functions should only be called if type() is of the correct type.
  // Calling with a different type will result in a crash.
  // TODO(magjed): Return raw pointers for GetI420 once deprecated interface is
  // removed.
  scoped_refptr<I420Buffer> GetI420();
  scoped_refptr<const I420Buffer> GetI420() const;
  I420ABuffer* GetI420A();
  const I420ABuffer* GetI420A() const;
  I444Buffer* GetI444();
  const I444Buffer* GetI444() const;
  I010Buffer* GetI010();
  const I010Buffer* GetI010() const;

 protected:
  friend class base::RefCounted<VideoFrameBuffer>;

  virtual ~VideoFrameBuffer() = default;
};

// This interface represents planar formats.
class PlanarYuvBuffer : public VideoFrameBuffer {
 public:
  virtual int ChromaWidth() const = 0;
  virtual int ChromaHeight() const = 0;

  // Returns the number of steps(in terms of Data*() return type) between
  // successive rows for a given plane.
  virtual int StrideY() const = 0;
  virtual int StrideU() const = 0;
  virtual int StrideV() const = 0;

 protected:
  ~PlanarYuvBuffer() override = default;
};

// This interface represents 8-bit color depth formats: Type::kI420,
// Type::kI420A and Type::kI444.
class PlanarYuv8Buffer : public PlanarYuvBuffer {
 public:
  // Returns pointer to the pixel data for a given plane. The memory is owned by
  // the VideoFrameBuffer object and must not be freed by the caller.
  virtual const uint8_t* DataY() const = 0;
  virtual const uint8_t* DataU() const = 0;
  virtual const uint8_t* DataV() const = 0;

 protected:
  ~PlanarYuv8Buffer() override = default;
};

class I420Buffer : public PlanarYuv8Buffer {
 public:
  Type type() const override;

  int ChromaWidth() const final;
  int ChromaHeight() const final;

  scoped_refptr<I420Buffer> ToI420() final;

 protected:
  friend class VideoFrameBuffer;

  ~I420Buffer() override = default;
};

class I420ABuffer : public I420Buffer {
 public:
  Type type() const final;
  virtual const uint8_t* DataA() const = 0;
  virtual int StrideA() const = 0;

 protected:
  ~I420ABuffer() override = default;
};

class I444Buffer : public PlanarYuv8Buffer {
 public:
  Type type() const final;

  int ChromaWidth() const final;
  int ChromaHeight() const final;

 protected:
  ~I444Buffer() override = default;
};

// This interface represents 8-bit to 16-bit color depth formats: Type::kI010.
class PlanarYuv16BBuffer : public PlanarYuvBuffer {
 public:
  // Returns pointer to the pixel data for a given plane. The memory is owned by
  // the VideoFrameBuffer object and must not be freed by the caller.
  virtual const uint16_t* DataY() const = 0;
  virtual const uint16_t* DataU() const = 0;
  virtual const uint16_t* DataV() const = 0;

 protected:
  ~PlanarYuv16BBuffer() override = default;
};

// Represents Type::kI010, allocates 16 bits per pixel and fills 10 least
// significant bits with color information.
class I010Buffer : public PlanarYuv16BBuffer {
 public:
  Type type() const override;

  int ChromaWidth() const final;
  int ChromaHeight() const final;

 protected:
  ~I010Buffer() override = default;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_VIDEO_VIDEO_FRAME_BUFFER_H_
