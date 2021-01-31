#include "GeoServer/ThreadPool.h"
#include "GeoServer/Work.h"

#include <catch2/catch.hpp>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <set>
using namespace std;
using namespace Catch;
using std::chrono::milliseconds;
class Fixture
{
public:
    ThreadPool pool;
    mutex m;
};

TEST_CASE_METHOD(Fixture, "HasNoWorkOnCreation", "[AThreadPool]")
{
    ThreadPool pool2;
    REQUIRE_FALSE(pool2.hasWork());
}

// TODO 使用 Fixture 时，给 ThreadPool 中的  deque push 元素会出现段错误，初步规避使用局部创建
// ThreadPool，后续定位修复
TEST_CASE_METHOD(Fixture, "HasWorkAfterAdd", "[AThreadPool]")
{
    ThreadPool pool2;
    pool2.add(Work {});
    REQUIRE(pool2.hasWork());
}

TEST_CASE_METHOD(Fixture, "AnswersWorkAddedOnPull", "[AThreadPool]")
{
    ThreadPool pool2;
    pool2.add(Work { 1 });
    auto work = pool2.pullWork();

    REQUIRE(work.id() == 1);
}

TEST_CASE_METHOD(Fixture, "PullsElementsInFIFOOrder", "[AThreadPool]")
{
    ThreadPool pool2;
    pool2.add(Work { 1 });
    pool2.add(Work { 2 });
    auto work = pool2.pullWork();

    REQUIRE(work.id() == 1);
}

TEST_CASE_METHOD(Fixture, "HasNoWorkAfterLastElementRemoved", "[AThreadPool]")
{
    ThreadPool pool2;
    pool2.add(Work {});
    pool2.pullWork();
    REQUIRE_FALSE(pool2.hasWork());
}

TEST_CASE_METHOD(Fixture, "HasWorkAfterWorkRemovedButWorkRemains", "[AThreadPool]")
{
    ThreadPool pool2;
    pool2.add(Work {});
    pool2.add(Work {});
    pool2.pullWork();
    REQUIRE(pool2.hasWork());
}

class Fixture_Thread
{
public:
    ~Fixture_Thread()
    {
        for (auto& t : threads)
            t->join();
    }
    void incrementCountAndNotify()
    {
        std::unique_lock<std::mutex> lock(m);
        ++count;
        wasExecuted.notify_all();
    }

    void waitForCountAndFailOnTimeout(
        unsigned int expectedCount, const milliseconds& time = milliseconds(100))
    {
        unique_lock<mutex> lock(m);
        REQUIRE(wasExecuted.wait_for(lock, time, [&] { return expectedCount == count; }));
    }

    mutex m;
    condition_variable wasExecuted;
    unsigned int count { 0 };

    vector<shared_ptr<thread>> threads;
};

TEST_CASE_METHOD(Fixture_Thread, "Pulls work in a thread", "[AThreadPool_AddRequest]")
{
    ThreadPool pool2;
    pool2.start();
    Work work { [&] { incrementCountAndNotify(); } };
    unsigned int NumberOfWorkItems { 1 };
    pool2.add(work);

    waitForCountAndFailOnTimeout(NumberOfWorkItems);
}

TEST_CASE_METHOD(Fixture_Thread, "Executest all work", "[AThreadPool_AddRequest]")
{
    ThreadPool pool2;
    pool2.start();
    Work work { [&] { incrementCountAndNotify(); } };
    unsigned int NumberOfWorkItems { 3 };

    for (unsigned int i { 0 }; i < NumberOfWorkItems; i++)
        pool2.add(work);
    waitForCountAndFailOnTimeout(NumberOfWorkItems);
}
TEST_CASE_METHOD(Fixture_Thread, "HoldsUpUnderClientStress", "[AThreadPool_AddRequest]")
{
    ThreadPool pool2;
    pool2.start();

    Work work { [&] { incrementCountAndNotify(); } };
    unsigned int NumberOfWorkItems { 100 };
    unsigned int NumberOfThreads { 100 };

    for (unsigned int i { 0 }; i < NumberOfThreads; i++)
        threads.push_back(make_shared<thread>([&] {
            for (unsigned int j { 0 }; j < NumberOfWorkItems; j++)
                pool2.add(work);
        }));
    waitForCountAndFailOnTimeout(NumberOfThreads * NumberOfWorkItems);
}

class Fixture_MultipleThread : public Fixture_Thread
{
public:
    set<thread::id> threads;

    void addThreadIfUnique(const thread::id& id)
    {
        std::unique_lock<std::mutex> lock(m);
        threads.insert(id);
    }

    size_t numberOfThreadsProcessed() { return threads.size(); }
};

TEST_CASE_METHOD(Fixture_MultipleThread, "DispatchesWorkToMultipleThreads", "[AThreadPoolWithMultipleThread]")
{
    ThreadPool pool2;
    pool2.start();
    unsigned int numberOfThreads { 2 };
    pool2.start(numberOfThreads);
    Work work { [&] {
        addThreadIfUnique(this_thread::get_id());
        incrementCountAndNotify();
    } };
    unsigned int NumberOfWorkItems { 500 };

    for (unsigned int i { 0 }; i < NumberOfWorkItems; i++)
        pool2.add(work);

    waitForCountAndFailOnTimeout(NumberOfWorkItems);
    REQUIRE(numberOfThreads == numberOfThreadsProcessed());
}