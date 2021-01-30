#include "TestTimer.h"

#include <catch2/catch.hpp>
#include <iostream>

using namespace std;

namespace ToolBox
{
TestTimer::TestTimer()
        : TestTimer(Catch::getCurrentContext().getConfig()->name())
{
}

TestTimer::TestTimer(const string& text)
        : Start { chrono::system_clock::now() }
        , Text { text }
{
}

TestTimer::~TestTimer()
{
    Stop = chrono::system_clock::now();
    Elapsed = chrono::duration_cast<chrono::microseconds>(Stop - Start);
    cout << endl << Text << " elapsed time = " << Elapsed.count() * 0.001 << "ms" << endl;
}

}   // namespace ToolBox
