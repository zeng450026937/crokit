#ifndef YEALINK_RTVC_BINDING_CONTEXT_H_
#define YEALINK_RTVC_BINDING_CONTEXT_H_

#include "base/files/file_path.h"
#include "base/single_thread_task_runner.h"

namespace v8 {
class Isolate;
}  // namespace v8

namespace yealink {

class Media;

namespace rtvc {

class Context {
 public:
  static Context* Instance();

  void Initialize(v8::Isolate* isolate);
  void Initialize(v8::Isolate* isolate, const base::FilePath& workspace_folder);

  scoped_refptr<base::SingleThreadTaskRunner> GetTaskRunner(bool high_priority = true);

  v8::Isolate* GetIsolate();

  base::FilePath GetWorkspaceFolder();

  Media* GetMedia();

 protected:
  Context();
  ~Context();

 private:
  bool initialized_ = false;
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  scoped_refptr<base::SingleThreadTaskRunner> high_priority_task_runner_;
  v8::Isolate* isolate_ = nullptr;
  base::FilePath workspace_folder_;
  Media* media_ = nullptr;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONTEXT_H_
