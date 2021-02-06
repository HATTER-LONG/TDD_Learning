cmake_minimum_required(VERSION 3.5)

project(TDD-Learning-Project LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_VERBOSE_MAKEFILE OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-Wall -pedantic)

find_package(Threads)
find_package(spdlog REQUIRED CONFIG)
set(LOCAL_LINK_LIB spdlog::spdlog pthread)
## 指定头文件、库查找路径

IF(NOT BOOST_ROOT AND NOT $ENV{BOOST_ROOT} STREQUAL "")
    FILE( TO_CMAKE_PATH $ENV{BOOST_ROOT} BOOST_ROOT )
    IF( NOT EXISTS ${BOOST_ROOT} )
        MESSAGE( STATUS  ${BOOST_ROOT} " does not exist. Checking if BOOST_ROOT was a quoted string.." )
        STRING( REPLACE "\"" "" BOOST_ROOT ${BOOST_ROOT} ) 
        IF( EXISTS ${BOOST_ROOT} )
            MESSAGE( STATUS "After removing the quotes " ${BOOST_ROOT} " was now found by CMake" )
        ENDIF( EXISTS ${BOOST_ROOT})
    ENDIF( NOT EXISTS ${BOOST_ROOT} )
        # Save the BOOST_ROOT in the cache
    IF( NOT EXISTS ${BOOST_ROOT} )
        MESSAGE( WARNING "BOOST_ROOT does not exist." )
    ELSE(NOT EXISTS ${BOOST_ROOT})
        SET(BOOST_ROOT ${BOOST_ROOT} CACHE STRING "Set the value of BOOST_ROOT to point to the root folder of your boost install." FORCE)
    ENDIF( NOT EXISTS ${BOOST_ROOT} )
ENDIF(NOT BOOST_ROOT AND NOT $ENV{BOOST_ROOT} STREQUAL "")

find_package(Boost REQUIRED)
IF(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    
    MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
ENDIF(Boost_FOUND)
include_directories(Include Src)
link_directories(Lib)

add_subdirectory(test)