#include "yealink/rtvc/binding/desktop_media_id.h"

#include <stdint.h>

#include <vector>

#include "base/containers/id_map.h"
#include "base/macros.h"
#include "base/memory/singleton.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/string_split.h"
#include "base/strings/string_util.h"

namespace yealink {

namespace rtvc {

const char kScreenPrefix[] = "screen";
const char kWindowPrefix[] = "window";

// static
const DesktopMediaID::Id DesktopMediaID::kNullId = 0;
// static
const DesktopMediaID::Id DesktopMediaID::kFakeId = -3;

bool DesktopMediaID::operator<(const DesktopMediaID& other) const {
  return std::tie(type, id, window_id, audio_share) <
         std::tie(other.type, other.id, other.window_id, other.audio_share);
}

bool DesktopMediaID::operator==(const DesktopMediaID& other) const {
  return type == other.type && id == other.id && window_id == other.window_id &&
         audio_share == other.audio_share;
}

// static
// Input string should in format:
// for WebContents:
// web-contents-media-stream://"render_process_id":"render_process_id" for
// screen: screen:window_id:native_window_id for window:
// window:window_id:native_window_id
DesktopMediaID DesktopMediaID::Parse(const std::string& str) {
  // For screen and window types.
  std::vector<std::string> parts =
      base::SplitString(str, ":", base::TRIM_WHITESPACE, base::SPLIT_WANT_ALL);

  if (parts.size() != 3)
    return DesktopMediaID();

  Type type = TYPE_NONE;
  if (parts[0] == kScreenPrefix) {
    type = TYPE_SCREEN;
  } else if (parts[0] == kWindowPrefix) {
    type = TYPE_WINDOW;
  } else {
    return DesktopMediaID();
  }

  int64_t id;
  if (!base::StringToInt64(parts[1], &id))
    return DesktopMediaID();

  DesktopMediaID media_id(type, id);

  int64_t window_id;
  if (!base::StringToInt64(parts[2], &window_id))
    return DesktopMediaID();
  media_id.window_id = window_id;

  return media_id;
}

std::string DesktopMediaID::ToString() const {
  std::string prefix;
  switch (type) {
    case TYPE_NONE:
      NOTREACHED();
      return std::string();
    case TYPE_SCREEN:
      prefix = kScreenPrefix;
      break;
    case TYPE_WINDOW:
      prefix = kWindowPrefix;
      break;
  }
  DCHECK(!prefix.empty());

  // Screen and Window types.
  prefix.append(":");
  prefix.append(base::NumberToString(id));

  prefix.append(":");
  prefix.append(base::NumberToString(window_id));

  return prefix;
}

}  // namespace rtvc

}  // namespace yealink
