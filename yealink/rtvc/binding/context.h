#ifndef YEALINK_RTVC_BINDING_CONTEXT_H_
#define YEALINK_RTVC_BINDING_CONTEXT_H_

#include "base/files/file_path.h"

namespace v8 {
class Isolate;
}  // namespace v8

namespace yealink {

namespace rtvc {

class Context {
 public:
  static void Initialize(v8::Isolate* isolate);

  static v8::Isolate* GetIsolate();

  static const base::FilePath& GetWorkspaceFolder();
  static void SetWorkspaceFolder(const base::FilePath& workspace_folder);

};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONTEXT_H_
