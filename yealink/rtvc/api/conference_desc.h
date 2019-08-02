#ifndef YEALINK_RTVC_API_CONFERENE_DESC_H_
#define YEALINK_RTVC_API_CONFERENE_DESC_H_

#include <string>

#include "yealink/rtvc/api/macros.h"

namespace yealink {

namespace rtvc {

enum class UriPurpose {
  kFocus,
  kAudioVideo,
  kApplicationSharing,
};

class ConferenceDesc {
  RTVC_READONLY_PROPERTY(std::string, subject);
  RTVC_READONLY_PROPERTY(std::string, note);
  RTVC_READONLY_PROPERTY(std::string, locations);
  RTVC_READONLY_PROPERTY(std::string, banner);
  RTVC_READONLY_PROPERTY(std::string, procedure);
  RTVC_READONLY_PROPERTY(std::string, schedule_id);
  RTVC_READONLY_PROPERTY(std::string, conf_uris);
  RTVC_READONLY_PROPERTY(std::string, applicant);
  RTVC_READONLY_PROPERTY(std::string, organizer);
  RTVC_READONLY_PROPERTY(std::string, invitees);
  RTVC_READONLY_PROPERTY(std::string, rtmp_invitees);
  RTVC_READONLY_PROPERTY(std::string, conference_id);
  RTVC_READONLY_PROPERTY(std::string, conference_number);
  RTVC_READONLY_PROPERTY(std::string, conference_type);
  RTVC_READONLY_PROPERTY(std::string, is_recurrence);
  RTVC_READONLY_PROPERTY(std::string, presenter_pin);
  RTVC_READONLY_PROPERTY(std::string, attendee_pin);
  RTVC_READONLY_PROPERTY(std::string, maximum_user_count);
  RTVC_READONLY_PROPERTY(std::string, start_time);
  RTVC_READONLY_PROPERTY(std::string, end_time);
  RTVC_READONLY_PROPERTY(std::string, book_start_time);
  RTVC_READONLY_PROPERTY(std::string, book_expire_time);
  RTVC_READONLY_PROPERTY(std::string, remind_early);
  RTVC_READONLY_PROPERTY(std::string, create_early);
  RTVC_READONLY_PROPERTY(std::string, recurrence_pattern);
  RTVC_READONLY_PROPERTY(std::string, admission_policy);
  RTVC_READONLY_PROPERTY(std::string, attendee_bypass);
  RTVC_READONLY_PROPERTY(std::string, lobby_capable);
  RTVC_READONLY_PROPERTY(std::string, join_url);
  RTVC_READONLY_PROPERTY(std::string, autopromote);
  RTVC_READONLY_PROPERTY(std::string, server_mode);
  RTVC_READONLY_PROPERTY(std::string, hide_osd);
  RTVC_READONLY_PROPERTY(std::string, interactive_broadcast_enabled);
  RTVC_READONLY_PROPERTY(std::string, default_rtmp);
  RTVC_READONLY_PROPERTY(std::string, record_id);
  RTVC_READONLY_PROPERTY(std::string, speech_mode);
  RTVC_READONLY_PROPERTY(std::string, record_server_type);
  RTVC_READONLY_PROPERTY(std::string, forward_enabled);
  RTVC_READONLY_PROPERTY(std::string, enterprise_id);

 public:
  ConferenceDesc() = default;
  ~ConferenceDesc() = default;

  std::string GetUri(UriPurpose purpose) {}

  std::string GetBanner() {}
  std::string GetPresetBanner() {}
  void SetBanner(std::string banner) {}
  void SaveBanner(std::string banner) {}

  std::string GetProcedure() {}
  void SetProcedure(std::string procedure) {}
  void SaveProcedure(std::string procedure) {}

  std::string GetTitle() {}
  void SetTitle(std::string title) {}
  void SaveTitle(std::string title) {}
  void CancelTitle() {}

  std::string GetDefaultRTMP() {}
  void SetDefaultRTMP() {}

  std::string GetRecordServerType() {}

  std::string GetSpeechMode() {}
  void SetSpeechMode(std::string speech_mode) {}
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_CONFERENE_DESC_H_
