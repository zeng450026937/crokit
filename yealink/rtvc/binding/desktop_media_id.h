#ifndef YEALINK_RTVC_BINDING_DESKTOP_MEDIA_ID_H_
#define YEALINK_RTVC_BINDING_DESKTOP_MEDIA_ID_H_

#include <string>
#include <tuple>

namespace rtvc {

// Type used to identify desktop media sources. It's converted to string and
// stored in MediaStreamRequest::requested_video_device_id.
struct DesktopMediaID {
 public:
  enum Type { TYPE_NONE, TYPE_SCREEN, TYPE_WINDOW };

  typedef intptr_t Id;

  // Represents an "unset" value for either |id| or |window_id|.
  static const Id kNullId;
  // Represents a fake id to create a dummy capturer for autotests.
  static const Id kFakeId;

  constexpr DesktopMediaID() = default;

  constexpr DesktopMediaID(Type type, Id id) : type(type), id(id) {}

  constexpr DesktopMediaID(Type type, Id id, bool audio_share)
      : type(type), id(id), audio_share(audio_share) {}

  // Operators so that DesktopMediaID can be used with STL containers.
  bool operator<(const DesktopMediaID& other) const;
  bool operator==(const DesktopMediaID& other) const;

  bool is_null() const { return type == TYPE_NONE; }
  std::string ToString() const;
  static DesktopMediaID Parse(const std::string& str);

  Type type = TYPE_NONE;

  // The IDs referring to the target native screen or window.  |id| will be
  // non-null if and only if it refers to a native screen/window.  |window_id|
  // will be non-null if and only if it refers to an Aura window.  Note that is
  // it possible for both of these to be non-null, which means both IDs are
  // referring to the same logical window.
  Id id = kNullId;
  // TODO(miu): Make this an int, after clean-up for http://crbug.com/513490.
  Id window_id = kNullId;

  // This records whether the desktop share has sound or not.
  bool audio_share = false;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_DESKTOP_MEDIA_ID_H_
