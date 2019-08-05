/*
 * @file log_api.h
 * @date 2019-06-29
 *
 * @brief 
 */
#ifndef __LOG_API_H__
#define __LOG_API_H__
#include <cstdint>
#include "log_define.h"

namespace yealink
{
enum LogLevel
{
    LOG_STACK,
    LOG_INFO,
    LOG_DEBUG,
    LOG_WARNING,
    LOG_ERROR
};

struct LogZipPath
{
    char path[260];
};

class LogWriter
{
public:
    /**
     * @brief destructor
     */
    virtual ~LogWriter()
    {
    }
    /**
     * @brief log callback
     * @param moduleName module name
     * @param level log level
     * @param fileName source file name
     * @param line source file line
     * @param processId process id
     * @param threadId thread id
     * @param logTime 1e-6 s
     * @param body 
     */
    virtual void PrintLog(
        const char* moduleName,
        LogLevel level,
        const char* fileName,
        int64_t line,
        int64_t processId,
        int64_t threadId,
        int64_t logTime,
        const char* body, bool isNewLine) = 0;
};

/**
 * @brief 
 */
class TarProcess
{
public:
    /**
     * @brief destructor
     */
    virtual ~TarProcess()
    {
    }
    /**
     * @brief judge progress is stop
     * @return progress status
     */
    virtual bool IsStop() = 0;
    /**
     * @brief get 
     * @param currentIndex 
     * @param totalCount 
     */
    virtual void TarProgressRate(int64_t currentIndex, int64_t totalCount) = 0;
};

/**
 * @brief print a log
 * @param level log level(stack, info, debug, warning or error)
 * @param moduleName your module name or tag
 * @param body body of log
 * @param fileName source file name(__FILE__ or "")
 * @param line source file line(__LINE__ or 0)
 */
LOG_API void PrintLog(LogLevel level, const char* moduleName, const char* body, const char* fileName, int64_t line, bool isNewLine);

class LOG_API LogService
{
public:
    /**
     * @brief register log writer
     * @param writer writer object implement by other
     */
    static void RegisterLogWriter(LogWriter* writer);
    /**
     * @brief remove log writer
     * @param writer writer object
     * @note call this interface before delete object
     */
    static void RemoveLogWriter(LogWriter* writer);
    /**
     * @brief set path in where write log
     * @param path log work path
     * @param maxLogSize max size of each log file
     * @param maxTarSize max size of tar package
     */
    static void SetFileWriterPath(const char* path, int64_t maxLogSize, int64_t maxTarSize);
    /**
     * @brief tar all log file, and return file path
     * @param externPath 
     * @param process 
     * @return file path
     */
    static LogZipPath TarAllLog(const char* externPath, TarProcess* process);
    /**
     * @brief 
     */
    static void StopFileWriter();
};

} // namespace yealink

#endif // __LOG_API_H__
