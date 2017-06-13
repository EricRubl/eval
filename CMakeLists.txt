cmake_minimum_required(VERSION 3.7)
project(eval)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp DynamicStack.hpp DynamicQueue.hpp Expression.hpp test/TestDynamicStack.cpp)
add_executable(eval ${SOURCE_FILES})

add_subdirectory(test/googletest-master)
include_directories(test/googletest-master/googletest/include)
include_directories(test/googletest-master/googlemock/include)
target_link_libraries(eval gtest gtest_main)