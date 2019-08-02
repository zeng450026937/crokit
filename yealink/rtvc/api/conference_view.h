#ifndef YEALINK_RTVC_API_CONFERENCE_VIEW_H_
#define YEALINK_RTVC_API_CONFERENCE_VIEW_H_

#include <string>

#include "yealink/rtvc/api/macros.h"

namespace yealink {
namespace rtvc {

enum class FilterType {
  kAudio,
  kVideo,
  kUnknown,
};

std::string FilterTypeToString(FilterType type) {
  switch (type) {
    case FilterType::kAudio:
      return "audio";
    case FilterType::kVideo:
      return "video";
  }

  return std::string();
}

FilterType FilterTypeFromString(std::string type) {
  if (type == "audio")
    return FilterType::kAudio;
  if (type == "video")
    return FilterType::kVideo;

  return FilterType::kUnknown;
}

class ConferenceView {
  RTVC_READONLY_PROPERTY(std::string, entity_view);
  RTVC_READONLY_PROPERTY(std::string, subtitle);

 public:
  ConferenceView() = default;
  ~ConferenceView() = default;

  void GetEntityView();

  void GetMediaView();
  void SetMediaView();

  void GetInitialFilters(FilterType type);
  void SetInitialFilters(FilterType type, std::string property);

  void GetDefaultFilter(FilterType type);
  void SetDefaultFilter(FilterType type, std::string property);

  void GetAttendeeFilter(FilterType type);
  void SetAttendeeFilter(FilterType type, std::string property);

  void GetLayout();
  void SetLayout();

  void GetBroadcastLayout();
  void SetBroadcastLayout();

  void GetSupervisionLayout();
  void SetSupervisionLayout();

  // wtf these are ??
  void GetStudentAudioFilter();
  void SetStudentAudioFilter();

  void SetPerspective();
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_CONFERENCE_VIEW_H_
