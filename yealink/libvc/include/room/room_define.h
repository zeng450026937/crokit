/*
 * @file room_define.h
 * @date 2019-03-21
 * 
 * @brief 
 */

#ifndef __ROOM_DEFINE_H__
#define __ROOM_DEFINE_H__

#ifdef _WIN32
#    ifdef EXPORT_SYMPOLS
#        define ROOM_API __declspec(dllexport)
#    else
#        define ROOM_API __declspec(dllimport)
#    endif
#else
#    define ROOM_API
#endif

#define ROOM_COMPONENT_DECLARE(type) \
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

#endif // __ROOM_DEFINE_H__
