#include "GeoServer/ThreadPool.h"
#include "GeoServer/Work.h"

#include <catch2/catch.hpp>
#include <chrono>
#include <condition_variable>
#include <mutex>
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

TEST_CASE_METHOD(Fixture, "Pulls work in a thread", "[AThreadPool]")
{
    ThreadPool pool2;
    pool2.start();
    condition_variable wasExecuted;
    bool wasWorked { false };
    Work work { [&] {
        unique_lock<mutex> lock(m);
        wasWorked = true;
        wasExecuted.notify_all();
    } };
    pool2.add(work);

    unique_lock<mutex> lock(m);
    REQUIRE(wasExecuted.wait_for(lock, chrono::milliseconds(100), [&] { return wasWorked; }));
}