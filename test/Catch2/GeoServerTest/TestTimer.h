#pragma once

#include <chrono>
#include <string>
namespace ToolBox
{
struct TestTimer
{
    TestTimer();
    TestTimer(const std::string& text);
    ~TestTimer();

    std::chrono::time_point<std::chrono::system_clock> Start;
    std::chrono::time_point<std::chrono::system_clock> Stop;
    std::chrono::microseconds Elapsed;
    std::string Text;
};
}   // namespace ToolBox