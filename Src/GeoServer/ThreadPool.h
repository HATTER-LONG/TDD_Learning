#pragma once

#include "Work.h"

#include <deque>
#include <string>

class ThreadPool
{
public:
    bool hasWork() { return !workQueue_.empty(); }

    void add(Work work) { workQueue_.push_front(work); }

    Work pullWork()
    {
        auto work = workQueue_.back();
        workQueue_.pop_back();
        return work;
    }

private:
    std::deque<Work> workQueue_;
};