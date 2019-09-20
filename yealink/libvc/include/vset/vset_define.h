/*!
* @file vset_define.h
* @date 2019/06/20
*
* @brief 
*
*/
#ifndef __VSET_DEFINE_H__
#    define __VSET_DEFINE_H__

#    if defined(_WIN32) && defined(vc_sdk_native_EXPORTS)
#        ifdef EXPORT_SYMPOLS
#            define VSET_EXPORT __declspec(dllexport)
#        else
#            define VSET_EXPORT __declspec(dllimport)
#        endif
#    else
#        define VSET_EXPORT
#    endif // EXPORT_SYMPOLS
#else // _WIN32

#endif //__VSET_DEFINE_H__