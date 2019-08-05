/*!
* @file vset_define.h
* @date 2019/06/20
*
* @brief 
*
*/
#ifndef __VSET_DEFINE_H__
#    define __VSET_DEFINE_H__

#    ifdef _WIN32
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