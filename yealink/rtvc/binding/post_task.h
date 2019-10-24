#ifndef YEALINK_RTVC_BINDING_POST_TASK_H_
#define YEALINK_RTVC_BINDING_POST_TASK_H_

#include "base/bind.h"

namespace rtvc {

void PostTask(base::OnceClosure task);

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_POST_TASK_H_
