#ifndef YEALINK_RTVC_API_MACROS_H_
#define YEALINK_RTVC_API_MACROS_H_

#define RTVC_READONLY_PROPERTY(type, property) \
 public:                                       \
  type property() { return property##_; };     \
                                               \
 private:                                      \
  type property##_

#endif  // YEALINK_RTVC_API_MACROS_H_
