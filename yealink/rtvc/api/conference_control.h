#ifndef YEALINK_RTVC_API_CONFERENCE_CONTROL_H_
#define YEALINK_RTVC_API_CONFERENCE_CONTROL_H_

#include <string>
#include <vector>

#include "base/optional.h"

#include "yealink/rtvc/api/conference_user.h"

namespace rtvc {

struct RTMPOptions {};

class RTMPCon {
 public:
  virtual void default_rtmp_user() = 0;
  // default rtmp from conference description
  virtual void config() = 0;
  // default status, alias for defaultRTMPUser
  virtual void status() = 0;
  virtual void GetStatus(std::string entity) = 0;

  // apply conference default rtmp options
  virtual void Apply() = 0;

  virtual void Start(base::Optional<std::string> entity = base::nullopt) = 0;
  virtual void Stop(base::Optional<std::string> entity = base::nullopt) = 0;
  virtual void Pause(base::Optional<std::string> entity = base::nullopt) = 0;
  virtual void Resume(base::Optional<std::string> entity = base::nullopt) = 0;

  virtual void Invite(std::string entity) = 0;
  // modify rtmp user options
  virtual void Modify(std::string entity, RTMPOptions options) = 0;

  virtual void GetInfo() = 0;

 protected:
  virtual ~RTMPCon() = default;
};

class RecordCon {
 public:
  virtual void default_rtmp_user() = 0;
  // default status, alias for defaultRecordUser
  virtual void status() = 0;

  virtual void GetRecordList() = 0;

  virtual void Start(std::string entity) = 0;
  virtual void Stop(std::string entity) = 0;
  virtual void Pause(std::string entity) = 0;
  virtual void Resume(std::string entity) = 0;

 protected:
  virtual ~RecordCon() = default;
};

class LobbyCon {
 public:
  // apply conference lock options
  virtual void Apply() = 0;

  virtual void Hold() = 0;
  virtual void Unhold() = 0;
  virtual void Allow() = 0;
  virtual void Refuse() = 0;

  // alias for refuse()
  virtual void kick() = 0;

 protected:
  virtual ~LobbyCon() = default;
};

class RollCallCon {
 public:
  virtual void Apply() = 0;
  virtual void Modify(std::string entity) = 0;
  virtual void Reset() = 0;

  virtual void Start() = 0;
  virtual void Stop() = 0;
  virtual void Pause() = 0;
  virtual void Resume() = 0;

  virtual void GetStatus() = 0;
  virtual void GetResult() = 0;

 protected:
  virtual ~RollCallCon() = default;
};

enum class CameraAction {
  LEFT = 0,
  RIGHT = 1,
  DOWN = 2,
  UP = 3,
  ZOOMOUT = 4,
  ZOOMIN = 5,
};

class CameraCon {
 public:
  virtual void Action(CameraAction type, int step = 1) = 0;

  virtual void Up(int step = 1) = 0;
  virtual void Down(int step = 1) = 0;
  virtual void Left(int step = 1) = 0;
  virtual void Right(int step = 1) = 0;
  virtual void Zoomin(int step = 1) = 0;
  virtual void Zoomout(int step = 1) = 0;

 protected:
  virtual ~CameraCon() = default;
};

enum class UserRole {};
struct MediaFilter {};

class UserCon {
 public:
  virtual const std::vector<ConferenceUser>& users() = 0;
  virtual const ConferenceUser& current_user() = 0;
  virtual const ConferenceUser& sharing_user() = 0;
  virtual const ConferenceUser& organizer() = 0;

  virtual const ConferenceUser& GetUser(std::string entity) = 0;
  virtual bool HasUser(std::string entity) = 0;

  // invite user
  virtual void Invite(std::vector<std::string> users) = 0;
  // invite user with command batched
  virtual void InviteBatch(std::vector<std::string> users) = 0;

  virtual void SetDemonstrator(std::vector<std::string> entities,
                               bool enable) = 0;
  // server do not support
  // virtual void SetDemonstratorBatch(std::vector<std::string> entities,
  //                                   bool enable) = 0;

  virtual void SetPermission(std::vector<std::string> entities, UserRole role) = 0;
  virtual void SetPermissionBatch(std::vector<std::string> entities, UserRole role) = 0;

  virtual void SetFilter(std::vector<std::string> entities, MediaFilter filter) = 0;
  virtual void SetAudioFilter(std::vector<std::string> entities, MediaFilter filter) = 0;
  virtual void SetVideoFilter(std::vector<std::string> entities, MediaFilter filter) = 0;

  virtual void Hold(std::vector<std::string> entities) = 0;
  virtual void Unhold(std::vector<std::string> entities) = 0;
  virtual void Allow(std::vector<std::string> entities, bool granted) = 0;

  virtual void Kick(std::vector<std::string> entities) = 0;

  virtual void GetStatistics(std::vector<std::string> entities) = 0;
  virtual void GetStatisticsBatch(std::vector<std::string> entities) = 0;

 protected:
  virtual ~UserCon() = default;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_API_CONFERENCE_CONTROL_H_
