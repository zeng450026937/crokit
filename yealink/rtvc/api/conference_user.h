#ifndef YEALINK_RTVC_API_CONFERENCE_USER_H_
#define YEALINK_RTVC_API_CONFERENCE_USER_H_

#include <string>

#include "yealink/rtvc/api/macros.h"

namespace yealink {

namespace rtvc {

enum class EndpointType {
  kFocus,
  kAudioVideo,
  kApplicationSharing,
  kChat,
};

enum class MediaType {
  kMainAudio,
  kMainVideo,
  kApplicationSharing,
  kFecc,
};

class ConferenceUser {
  RTVC_READONLY_PROPERTY(std::string, entity);
  RTVC_READONLY_PROPERTY(std::string, uid);
  RTVC_READONLY_PROPERTY(std::string, display_text);
  RTVC_READONLY_PROPERTY(std::string, display_text_pinyin);
  RTVC_READONLY_PROPERTY(std::string, protocol);
  RTVC_READONLY_PROPERTY(std::string, ip);
  RTVC_READONLY_PROPERTY(std::string, phone);
  RTVC_READONLY_PROPERTY(std::string, user_agent);
  RTVC_READONLY_PROPERTY(std::string, roles);
  RTVC_READONLY_PROPERTY(std::string, endpoint);
  RTVC_READONLY_PROPERTY(std::string, video_limit_by_licence);
  RTVC_READONLY_PROPERTY(std::string, request_uri);

 public:
  void roles_entry();
  void media_list();

  bool isConnected();
  bool isRegistered();
  bool isAudioApplicant();
  bool isVideoApplicant();
  bool isRTMP();
  bool isSIP();
  bool isPresenter();
  bool isAttendee();
  bool isCastViewer();
  bool isDemonstrator();
  bool isPresenterDemonstrator();
  bool isOnHold();
  bool isFocusAvariable();
  bool isMediaAvariable();
  bool isSharing();
  // user camera can be controlled through fecc session
  bool hasFECC();

    // user extended
  bool isShareAvariable();
  bool isCurrentUser();
  bool isOrganizer();
  bool isForwarder();

  void GetEndpoint(EndpointType type);
  void GetMedia(MediaType type);
  void GetAudioFilter();
  void GetVideoFilter();
  void GetStats();

  void SetFilter();
  void SetAudioFilter();
  void SetVideoFilter();

  void SetPermission();
  void SetDemonstrator();
  void SetPresenterDemonstrator();

  // hold user in conference room
  // user will be moved to conference lobby
  void Hold();
  // move user into conference room from conference lobby
  void Unhold();
  // unhold or delete user from conference lobby
  void Allow(bool granted);

  void Kick();

  void SendMessage(std::string msg);

 protected:
  virtual ~ConferenceUser() = default;
};

class ConferenceRTMPUser : public ConferenceUser {
  RTVC_READONLY_PROPERTY(std::string, rtmp_type);
  RTVC_READONLY_PROPERTY(std::string, rtmp_status);
  RTVC_READONLY_PROPERTY(std::string, max_video_fs);
  RTVC_READONLY_PROPERTY(std::string, mcu_session_type);
  RTVC_READONLY_PROPERTY(std::string, rtmp_duration);
  RTVC_READONLY_PROPERTY(std::string, rtmp_last_stop_duration);
  RTVC_READONLY_PROPERTY(std::string, rtmp_last_start_time);
 public:
  // user extended
  virtual void Start() = 0;
  virtual void Stop() = 0;
  virtual void Pause() = 0;
  virtual void Resume() = 0;

 protected:
  virtual ~ConferenceRTMPUser() = default;
};

class ConferenceRecordUser : public ConferenceUser {
  RTVC_READONLY_PROPERTY(std::string, record_type);
  RTVC_READONLY_PROPERTY(std::string, record_status);
  RTVC_READONLY_PROPERTY(std::string, record_server_type);
  RTVC_READONLY_PROPERTY(std::string, record_duration);
  RTVC_READONLY_PROPERTY(std::string, record_last_stop_duration);
  RTVC_READONLY_PROPERTY(std::string, record_last_start_time);
 public:
  // user extended
  virtual void Start() = 0;
  virtual void Stop() = 0;
  virtual void Pause() = 0;
  virtual void Resume() = 0;

 protected:
  virtual ~ConferenceRecordUser() = default;
};

class ConferenceSupervisionUser : public ConferenceUser {
 protected:
  virtual ~ConferenceSupervisionUser() = default;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_CONFERENCE_USER_H_
