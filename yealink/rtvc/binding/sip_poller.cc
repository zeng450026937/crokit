#include "yealink/rtvc/binding/sip_poller.h"

#include "base/bind.h"
#include "v8.h"
#include "yealink/libvc/include/sip_agent/sip_agent_api.h"
#include "yealink/rtvc/binding/context.h"

namespace rtvc {

SIPPoller::SIPPoller(scoped_refptr<base::SingleThreadTaskRunner> task_runner,
                     base::WeakPtr<yealink::SIPClient> sip_client)
    : task_runner_(task_runner), sip_client_(sip_client), weak_factory_(this) {
  DCHECK(task_runner_);
  DCHECK(sip_client_);
  OnPoll();
}
SIPPoller::~SIPPoller() {}

void SIPPoller::OnPoll() {
  int reschedule_at = 10;

  v8::HandleScope handle_scope(Context::Instance()->GetIsolate());
  while (sip_client_ && sip_client_->ProcessOnce(0) && reschedule_at) {
    --reschedule_at;
  }

  task_runner_->PostDelayedTask(
      FROM_HERE, base::BindOnce(&SIPPoller::OnPoll, weak_factory_.GetWeakPtr()),
      base::TimeDelta::FromMilliseconds(reschedule_at));
}

}  // namespace rtvc
