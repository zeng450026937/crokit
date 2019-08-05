/*
 * @file schedule_define.h
 * @date 2019-04-10
 *
 * @brief 
 */
#ifndef __SCHEDULE_DEFINE_H__
#define __SCHEDULE_DEFINE_H__

#ifdef _WIN32
#    ifdef EXPORT_SYMPOLS
#        define SCHEDULE_API __declspec(dllexport)
#    else
#        define SCHEDULE_API __declspec(dllimport)
#    endif
#else
#    define SCHEDULE_API
#endif

#define SCHEDULE_COMPONENT_DECLARE(type) \
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
    type(void* data); \
    void* m_data;

#endif // __SCHEDULE_DEFINE_H__
