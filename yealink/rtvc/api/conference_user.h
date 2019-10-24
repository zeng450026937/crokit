#ifndef YEALINK_RTVC_API_CONFERENCE_USER_H_
#define YEALINK_RTVC_API_CONFERENCE_USER_H_

#include <string>

#include "yealink/rtvc/api/macros.h"

namespace rtvc {

enum class UserProtocolType {
  kInvalid,
  kSIP,
  kH323,
  kRTMP,
};

enum class UserPermissionType {
  kInvalid,
  kOrganizer,
  kPresenter,
  kAttendee,
  kCastviewer,
};

enum class UserDemoStateType {
  kInvalid,
  kDemonstrator,
  kAudience,
};

enum class PresenterDemoStateType {
  kInvalid,
  kDemonstrator,
  kAudience,
};

struct UserRolesInfo {
  UserPermissionType permission;
  UserDemoStateType demostate;
  PresenterDemoStateType presenter_demostate;
};

enum class UserEndpointSeesionType {
  kInvalid,
  kFocus,
  kAudioVideo,
  kApplicationSharing,
  kChat,
  kCoopshare,
};
enum class UserEndpointStatusType {
  kInvalid,
  kDialingIn,
  kDialingOut,
  kOnHold,
  kConnected,
  kDisconnected,
};
enum class UserJoinMethod {
  kInvalid,
  kDialedIn,
  kDialedOut,
};

enum class UserMediaType {
  kInvalid,
  kAudio,
  kVideo,
  kApplication,
};
enum class UserMediaLabelType {
  kInvalid,
  kMainAudio,
  kMainVideo,
  kApplication,
  kFecc,
};
enum class UserMediaDirectionType {
  kInvalid,
  kSendRecv,
  kSendOnly,
  kRecvOnly,
  kInactive,
};
enum class UserMediafilterType {
  kInvalid,
  kBlock,
  kUnblock,
  kUnblocking,
};
enum class UserMediaBlockByType {
  kInvalid,
  kNone,
  kServer,
  kClient,
};

struct UserMediaInfo {
  std::string id;
  UserMediaType type;
  UserMediaLabelType label;
  UserMediaDirectionType status;
  UserMediafilterType media_ingress_filter;
  UserMediaBlockByType media_ingress_block_by;
  UserMediafilterType media_egress_filter;
  UserMediaBlockByType media_egress_block_by;
};

struct UserMediaFilterInfo {
  UserMediafilterType media_ingress_filter;
  UserMediaBlockByType media_ingress_block_by;
  UserMediafilterType media_egress_filter;
  UserMediaBlockByType media_egress_block_by;
};

struct UserEndpointInfo {
  std::string entity;
  UserEndpointSeesionType session_type;
  UserEndpointStatusType status;
  UserJoinMethod joining_method;
  std::string when;
  std::string mcu_call_id;
  std::vector<UserMediaInfo> media;
};

struct UserInfo {
  std::string entity;
  std::string display_text;
  std::string display_number;
  std::string display_text_pinyin;
  std::string uid;
  UserProtocolType protocol;
  std::string medium_server_type;
  std::string ip;
  std::string phone;
  std::string request_uri;
  std::string user_agent;
  UserRolesInfo roles;
  std::vector<UserEndpointInfo> endpoint;
};

struct UserMediaDataInfo {
  bool enable;
  std::string ip;
  std::string codec;
  int32_t width;
  int32_t height;
  int32_t fr;
  int32_t sample_rate;
  int32_t bandwidth;
  int32_t bit_rate;
  int32_t loss_rate;
  int32_t packet_lost;
  int32_t jitter;
  int32_t rtt;
};

struct UserStatisticsInfo {
  std::string media_id;
  UserMediaLabelType label;
  UserMediaType type;
  UserMediaDataInfo send;
  UserMediaDataInfo recv;
};

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

#endif  // YEALINK_RTVC_API_CONFERENCE_USER_H_
