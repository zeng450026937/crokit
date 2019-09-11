#ifndef YEALINK_RTVC_API_CONFERENCE_H_
#define YEALINK_RTVC_API_CONFERENCE_H_

#include <memory>
#include <string>

namespace yealink {

namespace rtvc {

enum class RequesrResult {
  kSuccess,
  kInvalidParam,
  kSipFailure,
  kInvalid,
};

struct ResponseInfo {
  int64_t request_id;
  RequesrResult result;
};

class ConferenceDescription;
class ConferenceState;
class ConferenceView;
class UserCon;
class RTMPCon;
class RecordCon;
class LobbyCon;
class RollCallCon;

class ConferenceObserver {
 public:
  virtual void OnDescriptionUpdated() = 0;
  virtual void OnStateUpdated() = 0;
  virtual void OnViewUpdate() = 0;
  virtual void OnUsersUpdated() = 0;
  virtual void OnRTMPUserUpdated() = 0;
  virtual void OnRecordUserUpdated() = 0;
  virtual void OnPrivateDateUpdated() = 0;

  virtual void OnUserAdded() = 0;
  virtual void OnUserUpdated() = 0;
  virtual void OnUserDeleted() = 0;

  virtual void OnChatMessage() = 0;

 protected:
  virtual ~ConferenceObserver() = default;
};

class Conference {
 public:
  static std::unique_ptr<Conference> Create(ConferenceObserver* observer);

  // connect for conference control
  virtual void Connect() = 0;
  virtual void Disconnect() = 0;

  virtual bool isInProgress() = 0;
  virtual bool isEstablished() = 0;
  virtual bool isEnded() = 0;

  // custom data which was setted when user create conference with open api
  virtual void data() = 0;
  virtual void SetData() = 0;

  virtual const ConferenceDescription* description() = 0;
  virtual const ConferenceState* state() = 0;
  virtual const ConferenceView* view() = 0;
  // user parts
  virtual const UserCon* user_con() = 0;
  // rtmp parts
  virtual const RTMPCon* rtmp_con() = 0;
  // record parts
  virtual const RecordCon* record_con() = 0;
  // lobby parts
  virtual const LobbyCon* lobby_con() = 0;
  // roll call parts
  virtual const RollCallCon* rollcall_con() = 0;

 protected:
  virtual ~Conference() = default;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_CONFERENCE_H_
