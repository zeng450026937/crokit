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
    Timer(const Timer& t);
    ~Timer();

    void StartTimer(int interval, const std::function<void()>& task);
    void Expire();

    template<typename callable, class... arguments>
    void SyncWait(int after, callable&& f, arguments&&... args);
    template<typename callable, class... arguments>
    void AsyncWait(int after, callable&& f, arguments&&... args);

private:
    std::atomic<bool> expired_;
    std::atomic<bool> try_to_expire_;
    std::mutex mutex_;
    std::condition_variable expired_cond_;
};
} // namespace yealink
#endif