#pragma once

#include "Work.h"

#include <deque>
#include <memory>
#include <string>
#include <thread>
class ThreadPool
{
public:
    virtual ~ThreadPool()
    {
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
        while (!hasWork())
            ;
        pullWork().execute();
    }


private:
    std::deque<Work> workQueue_;
    std::shared_ptr<std::thread> workThread_;
};