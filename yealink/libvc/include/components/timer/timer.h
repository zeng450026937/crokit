#ifndef _TIMER_H_
#define _TIMER_H_
#include <functional>
#include <chrono>
#include <thread>
#include <atomic>
#include <memory>
#include <mutex>
#include <condition_variable>
namespace yealink
{
class Timer
{
public:
    Timer();
    ~Timer();

    void StartTimer(int interval, const std::function<void()>& task);
    void Stop();

private:
    std::mutex m_mutex;
    bool m_bActived;
    std::condition_variable m_condExpired;
};
} // namespace yealink
#endif