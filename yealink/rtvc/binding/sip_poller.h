#ifndef YEALINK_RTVC_BINDING_SIP_POLLER_H_
#define YEALINK_RTVC_BINDING_SIP_POLLER_H_

#include <atomic>

#include "base/memory/weak_ptr.h"
#include "base/single_thread_task_runner.h"
#include "yealink/libvc/include/sip_agent/sip_agent_api.h"

namespace yealink {

namespace rtvc {

class SIPPoller {
 public:
  SIPPoller(scoped_refptr<base::SingleThreadTaskRunner> task_runner,
            base::WeakPtr<yealink::SIPClient> sip_client);
  ~SIPPoller();

  void OnPoll();

 private:
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  base::WeakPtr<yealink::SIPClient> sip_client_;
  base::WeakPtrFactory<SIPPoller> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(SIPPoller);
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_SIP_POLLER_H_
