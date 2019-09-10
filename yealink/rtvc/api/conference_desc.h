#ifndef YEALINK_RTVC_API_CONFERENE_DESC_H_
#define YEALINK_RTVC_API_CONFERENE_DESC_H_

#include <string>

#include "yealink/rtvc/api/macros.h"

namespace yealink {

namespace rtvc {
enum class DescProfile { kInvalid, kConference, kTeaching, kSeminar };

enum class DescPosition { kInvalid, kTop, kMedium, kBottom };

struct DescBanner {
  bool enabled;
  std::string display_text;
  DescPosition position;
};

enum class DescRtmpSessionType {
  kInvalid,
  kAV,
  kAD,
  kAVD,
};

enum class DescRtmpFsType {
  kInvalid,
  k360P,
  k720P,
  k1080P,
};

struct DescDefaultRtmp {
  bool enabled;
  std::string display_text;
  DescRtmpSessionType mcu_session_type;
  DescRtmpFsType max_video_fs;
  std::string web_share_url;
};

enum class DescUriPurpose {
  kInvalid,
  kFocus,
  kAudioVideo,
  kApplicationSharing,
  kChat,
  kCoopShare
};

struct DescConfUriInfo {
  std::string uri;
  std::string display_text;
  DescUriPurpose purpose;
};

struct DescOrganizerInfo {
  std::string display_text;
  std::string uid;
  std::string username;
  std::string realm;
  std::string phone;
  std::string domain;
};

enum class DescConferenceType { kInvalid, kVMN, kVGCP, kVGCM, kVSC, kVSCA };

enum class DescNumberType { kInvalid, kMeetNow, kRecurrence, kVMR };

enum class DescAdmissionPolicy {
  kInvalid,
  kClosedAuthenticated,
  KOpenAuthenticated,
  kAnonumous,
};

enum class DescAttendeeByPass {
  kInvalid,
  kByPassTrue,
  KByPassFalse,
};

enum class DescAutoPromote {
  kInvalid,
  kNone,
  kEveryOne,
  kCompany,
};

enum class DescRecordType {
  kInvalid,
  kYealinkRecord,
  kThirdParty,
};

enum class DescRecordPrivilege {
  kInvalid,
  kOrganizer,
  kPresenter,
  kAttendee,
};

struct DescSetLockInfo {
  DescAdmissionPolicy admission_policy;
  DescAttendeeByPass attendee_by_pass;
  DescAutoPromote auto_promote;
};

struct DescGetLockInfo {
  DescAdmissionPolicy admission_policy;
  bool attendee_by_pass;
  DescAutoPromote auto_promote;
};

struct DescInfo {
  std::string subject;
  int64_t start_time;
  DescBanner banner;
  DescDefaultRtmp default_rtmp;
  DescProfile profile;
  std::string record_id;
  std::vector<DescConfUriInfo> conf_uris;
  std::string conference_id;
  std::string conference_number;
  DescConferenceType conference_type;
  DescNumberType conference_number_type;
  int64_t book_start_time;
  int64_t book_expiry_time;
  std::string presenter_pin;
  std::string attendee_pin;
  DescAdmissionPolicy admission_policy;
  bool lobby_capable;
  bool attendee_by_pass;
  DescAutoPromote auto_promote;
  std::string server_mode;
  bool interactive_broadcast_enabled;
  std::string enterprise_id;
  bool video_enable;
  bool ipcall_enable;
  bool webrtc_enable;
  DescRecordType record_server_type;
  DescRecordPrivilege record_privilege;
  std::string conf_info_url;
};

// class ConferenceDesc {
//   RTVC_READONLY_PROPERTY(std::string, subject);
//   RTVC_READONLY_PROPERTY(std::string, note);
//   RTVC_READONLY_PROPERTY(std::string, locations);
//   RTVC_READONLY_PROPERTY(std::string, banner);
//   RTVC_READONLY_PROPERTY(std::string, procedure);
//   RTVC_READONLY_PROPERTY(std::string, schedule_id);
//   RTVC_READONLY_PROPERTY(std::string, conf_uris);
//   RTVC_READONLY_PROPERTY(std::string, applicant);
//   RTVC_READONLY_PROPERTY(std::string, organizer);
//   RTVC_READONLY_PROPERTY(std::string, invitees);
//   RTVC_READONLY_PROPERTY(std::string, rtmp_invitees);
//   RTVC_READONLY_PROPERTY(std::string, conference_id);
//   RTVC_READONLY_PROPERTY(std::string, conference_number);
//   RTVC_READONLY_PROPERTY(std::string, conference_type);
//   RTVC_READONLY_PROPERTY(std::string, is_recurrence);
//   RTVC_READONLY_PROPERTY(std::string, presenter_pin);
//   RTVC_READONLY_PROPERTY(std::string, attendee_pin);
//   RTVC_READONLY_PROPERTY(std::string, maximum_user_count);
//   RTVC_READONLY_PROPERTY(std::string, start_time);
//   RTVC_READONLY_PROPERTY(std::string, end_time);
//   RTVC_READONLY_PROPERTY(std::string, book_start_time);
//   RTVC_READONLY_PROPERTY(std::string, book_expire_time);
//   RTVC_READONLY_PROPERTY(std::string, remind_early);
//   RTVC_READONLY_PROPERTY(std::string, create_early);
//   RTVC_READONLY_PROPERTY(std::string, recurrence_pattern);
//   RTVC_READONLY_PROPERTY(std::string, admission_policy);
//   RTVC_READONLY_PROPERTY(std::string, attendee_bypass);
//   RTVC_READONLY_PROPERTY(std::string, lobby_capable);
//   RTVC_READONLY_PROPERTY(std::string, join_url);
//   RTVC_READONLY_PROPERTY(std::string, autopromote);
//   RTVC_READONLY_PROPERTY(std::string, server_mode);
//   RTVC_READONLY_PROPERTY(std::string, hide_osd);
//   RTVC_READONLY_PROPERTY(std::string, interactive_broadcast_enabled);
//   RTVC_READONLY_PROPERTY(std::string, default_rtmp);
//   RTVC_READONLY_PROPERTY(std::string, record_id);
//   RTVC_READONLY_PROPERTY(std::string, speech_mode);
//   RTVC_READONLY_PROPERTY(std::string, record_server_type);
//   RTVC_READONLY_PROPERTY(std::string, forward_enabled);
//   RTVC_READONLY_PROPERTY(std::string, enterprise_id);

//  public:
//   ConferenceDesc() = default;
//   ~ConferenceDesc() = default;

//   std::string GetUri(DescConfUriInfo purpose) {}

//   std::string GetBanner() {}
//   std::string GetPresetBanner() {}
//   void SetBanner(std::string banner) {}
//   void SaveBanner(std::string banner) {}

//   std::string GetProcedure() {}
//   void SetProcedure(std::string procedure) {}
//   void SaveProcedure(std::string procedure) {}

//   std::string GetTitle() {}
//   void SetTitle(std::string title) {}
//   void SaveTitle(std::string title) {}
//   void CancelTitle() {}

//   std::string GetDefaultRTMP() {}
//   void SetDefaultRTMP() {}

//   std::string GetRecordServerType() {}

//   std::string GetSpeechMode() {}
//   void SetSpeechMode(std::string speech_mode) {}

//   bool GetLock() {}
//   void SetLock() {}
// };

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_CONFERENE_DESC_H_
