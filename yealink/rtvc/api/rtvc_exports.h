#ifndef YEALINK_RTVC_API_RTVC_EXPORTS_H_
#define YEALINK_RTVC_API_RTVC_EXPORTS_H_

#if defined(COMPONENT_BUILD)
#if defined(WIN32)

#if defined(RTVC_IMPLEMENTATION)
#define RTVC_EXPORT __declspec(dllexport)
#else
#define RTVC_EXPORT __declspec(dllimport)
#endif  // defined(RTVC_IMPLEMENTATION)

#else  // defined(WIN32)
#if defined(RTVC_IMPLEMENTATION)
#define RTVC_EXPORT __attribute__((visibility("default")))
#else
#define RTVC_EXPORT
#endif  // defined(RTVC_IMPLEMENTATION)
#endif

#else  // defined(COMPONENT_BUILD)
#define RTVC_EXPORT
#endif

#endif  // YEALINK_RTVC_API_RTVC_EXPORTS_H_
