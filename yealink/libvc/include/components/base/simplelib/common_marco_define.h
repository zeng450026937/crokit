/*
 * @file common_marco_define.h
 * @date 2019-07-13
 *
 * @brief 
 */
#ifndef __COMMON_MARCO_DEFINE_H__
#define __COMMON_MARCO_DEFINE_H__

#ifdef _WIN32
#    ifndef ENABLE_UNIT_TEST
#        ifdef EXPORT_SYMPOLS
#            define VC_EXPORT_API __declspec(dllexport)
#        else
#            define VC_EXPORT_API __declspec(dllimport)
#        endif
#    else
#        define VC_EXPORT_API
#    endif
#else
#    define VC_EXPORT_API
#endif

#define SIMPLE_OBJECT_DECLARE(type) \
public: \
    type(); \
    ~type(); \
    type(const type& other); \
    type& operator=(const type& other); \
    bool Available() const; \
    bool operator==(const type& other) const; \
    bool operator!=(const type& other) const; \
\
private: \
    type(void* data); \
    void* m_data;

#endif // __COMMON_MARCO_DEFINE_H__
