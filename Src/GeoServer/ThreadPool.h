#pragma once

#include "Work.h"

#include <atomic>
#include <deque>
#include <memory>
#include <string>
#include <thread>
class ThreadPool
{
public:
    virtual ~ThreadPool() { stop(); }

    void stop()
    {
        done_ = true;
        if (workThread_)
            workThread_->join();
    }
    void start() { workThread_ = std::make_shared<std::thread>(&ThreadPool::worker, this); }
    bool hasWork() { return !workQueue_.empty(); }

    void add(Work work) { workQueue_.push_front(work); }

    Work pullWork()
    {
        auto work = workQueue_.back();
        workQueue_.pop_back();
        return work;
    }

private:
    void worker()
    {
        while (!done_)
        {
            while (!done_ && !hasWork())
                ;
            if (done_)
                break;
            pullWork().execute();
        }
    }


private:
    std::atomic<bool> done_ { false };
    std::deque<Work> workQueue_;
    std::shared_ptr<std::thread> workThread_;
};