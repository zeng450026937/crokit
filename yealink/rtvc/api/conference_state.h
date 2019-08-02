#ifndef YEALINK_RTVC_API_CONFERENCE_STATE_H_
#define YEALINK_RTVC_API_CONFERENCE_STATE_H_

#include <string>

#include "yealink/rtvc/api/macros.h"

namespace yealink {

namespace rtvc {

class ConferenceUser;

class ConferenceState {
  RTVC_READONLY_PROPERTY(std::string, active);
  RTVC_READONLY_PROPERTY(std::string, locked);
  RTVC_READONLY_PROPERTY(std::string, applicationsharer);
  RTVC_READONLY_PROPERTY(std::string, rollCallStatus);
  RTVC_READONLY_PROPERTY(std::string, forwarder);

 public:
  ConferenceState() = default;
  ~ConferenceState() = default;

  ConferenceUser* GetSharingUser();
  ConferenceUser* GetForwarder();

  bool GetLock();
  void SetLock();
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_CONFERENCE_STATE_H_
