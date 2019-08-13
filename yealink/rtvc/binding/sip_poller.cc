#include "yealink/rtvc/binding/sip_poller.h"

#include "base/bind.h"
#include "yealink/libvc/include/sip_agent/sip_agent_api.h"

namespace yealink {

namespace rtvc {

SIPPoller::SIPPoller(scoped_refptr<base::SingleThreadTaskRunner> task_runner,
                     yealink::SIPClient* sip_client)
    : task_runner_(task_runner), sip_client_(sip_client), weak_factory_(this) {
  DCHECK(task_runner_);
  DCHECK(sip_client_);

  OnPoll();
}
SIPPoller::~SIPPoller() = default;

void SIPPoller::OnPoll() {
  int reschedule_at = 10;

  while (sip_client_->ProcessOnce(0) && reschedule_at) {
    --reschedule_at;
  }

  task_runner_->PostDelayedTask(
      FROM_HERE, base::BindOnce(&SIPPoller::OnPoll, weak_factory_.GetWeakPtr()),
      base::TimeDelta::FromMilliseconds(reschedule_at));
}

}  // namespace rtvc

}  // namespace yealink
