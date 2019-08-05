#ifndef MEDIA_EXPORT_H
#define MEDIA_EXPORT_H

#ifdef _WIN32

#    ifdef EXPORT_SYMPOLS
#        define MEDIA_EXPORT __declspec(dllexport)
#    else
#        define MEDIA_EXPORT __declspec(dllimport)
#    endif

#else // _WIN32

#    if __has_attribute(visibility) && defined(EXPORT_SYMPOLS)
#        define MEDIA_EXPORT __attribute__((visibility("default")))
#    endif

#endif // _WIN32

#ifndef MEDIA_EXPORT
#    define MEDIA_EXPORT
#endif

#endif // MEDIA_EXPORT_H
