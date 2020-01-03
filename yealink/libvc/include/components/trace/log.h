#pragma once

#include <sstream>
#include <memory>
#include <cassert>
#include "components/log/log_api.h"

namespace yealink
{
#define LOG_LEVEL_STACK 0x00000010
#define LOG_LEVEL_DEBUG 0x00000008
#define LOG_LEVEL_INFO 0x000000004
#define LOG_LEVEL_WARNING 0x00000002
#define LOG_LEVEL_CRITICAL 0x00000001

#define STACK_LOG(format, ...) \
    do \
    { \
        LogLine log(LOG_LEVEL_STACK, THIS_MOD, __FILE__, __LINE__); \
        log.Print(true, format, __VA_ARGS__); \
    } while (0);
#define DEBUG_LOG(format, ...) \
    do \
    { \
        LogLine log(LOG_LEVEL_DEBUG, THIS_MOD); \
        log.Print(true, format, __VA_ARGS__); \
    } while (0);
#define INFO_LOG(format, ...) \
    do \
    { \
        LogLine log(LOG_LEVEL_INFO, THIS_MOD); \
        log.Print(true, format, __VA_ARGS__); \
    } while (0);
#define WARNING_LOG(format, ...) \
    do \
    { \
        LogLine log(LOG_LEVEL_WARNING, THIS_MOD, __FILE__, __LINE__); \
        log.Print(true, format, __VA_ARGS__); \
    } while (0);
#define CRITICAL_LOG(format, ...) \
    do \
    { \
        LogLine log(LOG_LEVEL_CRITICAL, THIS_MOD, __FILE__, __LINE__); \
        log.Print(true, format, __VA_ARGS__); \
    } while (0);
#define ASSERT_LOG(exp, format, ...) \
    if (!(exp)) \
    { \
        CRITICAL_LOG(format, __VA_ARGS__) \
        assert(exp); \
    }

#define STACK_LOG_S(args) \
    do \
    { \
        LogLine log(LOG_LEVEL_STACK, THIS_MOD, __FILE__, __LINE__); \
        log.Stream() args; \
        log.Print(true); \
    } while (0);
#define DEBUG_LOG_S(args) \
    do \
    { \
        LogLine log(LOG_LEVEL_DEBUG, THIS_MOD); \
        log.Stream() args; \
        log.Print(true); \
    } while (0);
#define INFO_LOG_S(args) \
    do \
    { \
        LogLine log(LOG_LEVEL_INFO, THIS_MOD); \
        log.Stream() args; \
        log.Print(true); \
    } while (0);
#define WARNING_LOG_S(args) \
    do \
    { \
        LogLine log(LOG_LEVEL_WARNING, THIS_MOD, __FILE__, __LINE__); \
        log.Stream() args; \
        log.Print(true); \
    } while (0);
#define CRITICAL_LOG_S(args) \
    do \
    { \
        LogLine log(LOG_LEVEL_CRITICAL, THIS_MOD, __FILE__, __LINE__); \
        log.Stream() args; \
        log.Print(true); \
    } while (0);
#define ASSERT_LOG_S(exp, args) \
    if (!(exp)) \
    { \
        CRITICAL_LOG_S(args) \
        assert(exp); \
    }

class LogLine
{
public:
    LogLine(int nLevel, const char* strTag);
    LogLine(int nLevel, const char* strTag, const char* strFile, int nLine);

public:
    template<typename... Args>
    void Print(bool bNewLine, const char* strFormat, Args... arg)
    {
        if ((m_nLevel & m_nLevelMask) != m_nLevel)
        {
            return;
        }
        if (strFormat)
        {
            size_t size = snprintf(nullptr, 0, strFormat, arg...) + 1; // Extra space for '\0'
            std::unique_ptr<char[]> buf(new char[size]);
            snprintf(buf.get(), size, strFormat, arg...);
            buf[size - 1] = '\0';
            m_sstreamLog << buf.get();

            switch (m_nLevel)
            {
            case LOG_LEVEL_STACK:
                PrintLog(
                    LOG_STACK,
                    m_strTag,
                    m_sstreamLog.str().c_str(),
                    m_strFile ? m_strFile : "",
                    m_nLine, bNewLine);
                break;
            case LOG_LEVEL_INFO:
                PrintLog(
                    LOG_INFO,
                    m_strTag,
                    m_sstreamLog.str().c_str(),
                    m_strFile ? m_strFile : "",
                    m_nLine, bNewLine);
                break;
            case LOG_LEVEL_DEBUG:
                PrintLog(
                    LOG_DEBUG,
                    m_strTag,
                    m_sstreamLog.str().c_str(),
                    m_strFile ? m_strFile : "",
                    m_nLine, bNewLine);
                break;
            case LOG_LEVEL_WARNING:
                PrintLog(
                    LOG_WARNING,
                    m_strTag,
                    m_sstreamLog.str().c_str(),
                    m_strFile ? m_strFile : "",
                    m_nLine, bNewLine);
                break;
            case LOG_LEVEL_CRITICAL:
                PrintLog(
                    LOG_ERROR,
                    m_strTag,
                    m_sstreamLog.str().c_str(),
                    m_strFile ? m_strFile : "",
                    m_nLine, bNewLine);
                break;
            default:
                break;
            }
        }
    }
    void Print(bool bNewLine)
    {
        if ((m_nLevel & m_nLevelMask) != m_nLevel)
        {
            return;
        }
        //print
        switch (m_nLevel)
        {
        case LOG_LEVEL_STACK:
            PrintLog(
                LOG_STACK,
                m_strTag,
                m_sstreamLog.str().c_str(),
                m_strFile ? m_strFile : "",
                m_nLine, bNewLine);
            break;
        case LOG_LEVEL_INFO:
            PrintLog(
                LOG_INFO,
                m_strTag,
                m_sstreamLog.str().c_str(),
                m_strFile ? m_strFile : "",
                m_nLine, bNewLine);
            break;
        case LOG_LEVEL_DEBUG:
            PrintLog(
                LOG_DEBUG,
                m_strTag,
                m_sstreamLog.str().c_str(),
                m_strFile ? m_strFile : "",
                m_nLine, bNewLine);
            break;
        case LOG_LEVEL_WARNING:
            PrintLog(
                LOG_WARNING,
                m_strTag,
                m_sstreamLog.str().c_str(),
                m_strFile ? m_strFile : "",
                m_nLine, bNewLine);
            break;
        case LOG_LEVEL_CRITICAL:
            PrintLog(
                LOG_ERROR,
                m_strTag,
                m_sstreamLog.str().c_str(),
                m_strFile ? m_strFile : "",
                m_nLine, bNewLine);
            break;
        default:
            break;
        }
    }
    std::stringstream& Stream();

private:
    std::stringstream m_sstreamLog;
    int m_nLevelMask;
    int m_nLevel;
    const char* m_strTag;
    const char* m_strFile;
    int m_nLine;
};
} // namespace yealink
//todo Performance Logger & Diagnosis Logger
