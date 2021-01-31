#include "GeoServer/Work.h"

#include <catch2/catch.hpp>
#include <sstream>
using namespace std;
using namespace Catch;

TEST_CASE("DefaultsFunctionToNullObject", "[AWorkObject]")
{
    Work work;
    try
    {
        work.execute();
    }
    catch (...)
    {
        FAIL("unable to execute function");
    }
}

TEST_CASE("DefaultsFunctionToNullObjectWhenConstructedWithId", "[AWorkObject]")
{
    Work work(1);
    try
    {
        work.execute();
    }
    catch (...)
    {
        FAIL("unable to execute function");
    }
}

TEST_CASE("CanBeConstructedWithAnId", "[AWorkObject]")
{
    Work work(1);
    REQUIRE(work.id() == 1);
}

TEST_CASE("DefaultsIdTo0", "[AWorkObject]")
{
    Work work;
    REQUIRE(work.id() == 0);
}

TEST_CASE("DefaultsIdTo0WhenFunctionSpecified", "[AWorkObject]")
{
    Work work { [] {} };
    REQUIRE(work.id() == 0);
}

TEST_CASE("ExecutesFunctionStored", "[AWorkObject]")
{
    bool wasExecuted { false };
    auto executeFunction = [&]() { wasExecuted = true; };
    Work work(executeFunction);
    work.execute();
    REQUIRE(wasExecuted);
}

TEST_CASE("CanExecuteOnDataCapturedWithFunction", "[AWorkObject]")
{
    vector<string> data { "a", "b" };
    string result;
    auto callbackFunction = [&](string s) { result.append(s); };

    auto executeFunction = [&]() {
        stringstream s;
        s << data[0] << data[1];
        callbackFunction(s.str());
    };

    Work work(executeFunction);
    work.execute();
    REQUIRE_THAT(result, Equals("ab"));
}