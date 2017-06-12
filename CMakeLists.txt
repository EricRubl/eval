cmake_minimum_required(VERSION 3.7)
project(eval)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp DynamicStack.hpp DynamicQueue.hpp Expression.hpp)
add_executable(eval ${SOURCE_FILES})