#ifndef YEALINK_RTVC_BINDING_SIP_CLIENT_H_
#define YEALINK_RTVC_BINDING_SIP_CLIENT_H_

#include "base/memory/ref_counted.h"

namespace yealink {

class SIPClient;

namespace rtvc {

class ScopedSIPClient : public base::RefCounted<SIPClient> {
 public:
  ScopedSIPClient();

  SIPClient* get() const {
    return client_;
  }

  SIPClient& operator*() const {
    DCHECK(get() != nullptr);
    return *get();
  }
  SIPClient* operator->() const {
    DCHECK(get() != nullptr);
    return get();
  }

 protected:
  ~ScopedSIPClient();

 private:
  yealink::SIPClient* client_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_SIP_CLIENT_H_
