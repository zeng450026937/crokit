#ifndef YEALINK_RTVC_BINDING_CONTEXT_H_
#define YEALINK_RTVC_BINDING_CONTEXT_H_

#include "base/callback.h"
#include "base/at_exit.h"
#include "base/files/file_path.h"
#include "base/message_loop/message_loop.h"
#include "base/single_thread_task_runner.h"
#include "base/threading/thread_checker.h"

namespace v8 {
class Isolate;
}  // namespace v8

namespace yealink {

class Media;
class AccessAgent;

namespace rtvc {

class Context {
 public:
  static Context* Instance();

  void Initialize(v8::Isolate* isolate);
  void Initialize(v8::Isolate* isolate, const base::FilePath& workspace_folder);

  void RegisterDestructionCallback(base::OnceClosure callback);

  scoped_refptr<base::SingleThreadTaskRunner> GetTaskRunner(
      bool high_priority = false);

  bool CalledOnValidThread();

  void PostTask(const base::Location& from_here, base::OnceClosure task);
  void PostDelayedTask(const base::Location& from_here, base::OnceClosure task);

  v8::Isolate* GetIsolate();

  // application wild unique id
  std::string GetUniqueId();

  base::FilePath GetWorkspaceFolder();

  Media* GetMedia();

 protected:
  Context();
  ~Context();

 private:
  bool initialized_ = false;
  THREAD_CHECKER(thread_checker_);
    // List of callbacks should be executed before destroying JS env.
  std::list<base::OnceClosure> destructors_;
  std::unique_ptr<base::AtExitManager> at_exit_;
  std::unique_ptr<base::MessageLoop> message_loop_;
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  scoped_refptr<base::SingleThreadTaskRunner> high_priority_task_runner_;
  v8::Isolate* isolate_ = nullptr;
  std::string unique_id_;
  base::FilePath workspace_folder_;
  Media* media_ = nullptr;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONTEXT_H_
