/*
 * @file log_define.h
 * @date 2019-07-01
 *
 * @brief 
 */
#ifndef __LOG_DEFINE_H__
#define __LOG_DEFINE_H__

#ifdef _WIN32
#    ifndef ENABLE_UNIT_TEST
#        ifdef EXPORT_SYMPOLS
#            define LOG_API __declspec(dllexport)
#        else
#            define LOG_API __declspec(dllimport)
#        endif
#    else
#        define LOG_API
#    endif
#else
#    define LOG_API
#endif

#define LOG_OBJECT_DECLARE(type) \
public: \
    type(); \
    ~type(); \
    type(const type& other); \
    type& operator=(const type& other); \
    bool Available() const; \
    bool operator==(const type& other); \
    bool operator!=(const type& other); \
\
private: \
    void* m_data;

#endif // __LOG_DEFINE_H__
