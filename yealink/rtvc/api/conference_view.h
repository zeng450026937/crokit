#ifndef YEALINK_RTVC_API_CONFERENCE_VIEW_H_
#define YEALINK_RTVC_API_CONFERENCE_VIEW_H_

#include <string>

#include "yealink/rtvc/api/macros.h"

namespace rtvc {

enum class ViewSpeakMode {
  kInvalid,
  kFree,
  kHandUp,
};

enum class ViewLayoutType {
  kInvalid,
  kEquality,
  kPresentation,
  kSpeechExcitation,
  kExclusive,
};

enum class ViewPresenterLayoutType {
  kInvalid,
  kEquality,
  kSpeechExcitation,
  kExclusive,
};

enum class ViewPurpose {
  kInvalid,
  kFocus,
  kAudioVideo,
  kChat,
  kCoopShare,
  kApplicationSharing,
};

enum class ViewRole {
  kInvalid,
  kDefault,
  kAttendee,
};

enum class ViewFilter {
  kInvalid,
  kBlock,
  kUnblock,
};

struct ViewInitialFilter {
  ViewRole role;
  ViewFilter ingressFilter;
};

struct SetLayoutInfo {
  ViewLayoutType video_layout;
  int video_max_view;
  ViewFilter egressFilter;
};

struct GetLayoutInfo {
  ViewSpeakMode speak_mode;
  ViewLayoutType video_layout;
  uint32_t video_max_view;
  ViewPresenterLayoutType video_presenter_layout;
  uint32_t video_presenter_max_view;
  uint32_t video_round_number;
  uint32_t video_round_interval;
  uint32_t video_speech_ex_sensitivity;
  bool video_round_enable;
  bool video_big_round;
  bool video_speech_ex_enabled;
  bool video_data_mix_enabled;
  bool hide_osd_sitename;
  bool hide_osd_sitestatus;
};

enum class ViewFilterRoleType {
  kInvalid,
  kDefault,
  kAttendee,
};

enum class ViewFilterType {
  kInvalid,
  kBlock,
  kUnBlock,
};

struct ViewFilterRuleInfo {
  ViewFilterRoleType role;
  ViewFilterType ingress;
  ViewFilterType egress;
};

// std::string ViewFilterTypeToString(ViewFilterType type) {
//   switch (type) {
//     case ViewFilterType::kAudio:
//       return "audio";
//     case ViewFilterType::kVideo:
//       return "video";
//   }

//   return std::string();
// }

// ViewFilterType ViewFilterTypeFromString(std::string type) {
//   if (type == "audio")
//     return ViewFilterType::kAudio;
//   if (type == "video")
//     return ViewFilterType::kVideo;

//   return ViewFilterType::kUnknown;
// }

class ConferenceView {
  RTVC_READONLY_PROPERTY(std::string, entity_view);
  RTVC_READONLY_PROPERTY(std::string, subtitle);

 public:
  ConferenceView() = default;
  ~ConferenceView() = default;

  void GetEntityView();

  void GetMediaView();
  void SetMediaView();

  void GetInitialFilters(ViewFilterType type);
  void SetInitialFilters(ViewFilterType type, std::string property);

  void GetDefaultFilter(ViewFilterType type);
  void SetDefaultFilter(ViewFilterType type, std::string property);

  void GetAttendeeFilter(ViewFilterType type);
  void SetAttendeeFilter(ViewFilterType type, std::string property);

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

#endif  // YEALINK_RTVC_API_CONFERENCE_VIEW_H_
