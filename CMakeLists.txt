cmake_minimum_required(VERSION 3.5)

project(TDD-Learning-Project LANGUAGES CXX)

# 1. QT 以及 C++ 环境相关配置
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_VERBOSE_MAKEFILE OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-Wall -pedantic)

find_package(Threads)

set(LOCAL_LINK_LIB  pthread)
##通过通过静态链接使用 spdlog 库
add_definitions(-DSPDLOG_COMPILED_LIB)
add_subdirectory(Lib)

## 指定头文件、库查找路径
include_directories(Include)
link_directories(Lib)

add_subdirectory(test)