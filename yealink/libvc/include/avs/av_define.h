#ifndef __AV_DEFINE_H__
#define __AV_DEFINE_H__

#ifdef _WIN32
#    ifdef EXPORT_SYMPOLS
#        define AV_API __declspec(dllexport)
#    else
#        define AV_API __declspec(dllimport)
#    endif
#else
#    define AV_API
#endif

namespace yealink
{
enum AVContentType
{
    AV_CONTENT_NONE = 0x0000,
    AV_ONLY_VIDEO = 0x0001,
    AV_ONLY_AUDIO = 0x0002,
    AV_VIDEO_AUDIO = 0x0003,
};

} // namespace yealink

#endif //__AV_DEFINE_H__
