cmake_minimum_required(VERSION 3.12)
project(cpuScheduller)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpuScheduller main.cpp process.cpp process.h event.cpp event.h thread.cpp thread.h burst.cpp burst.h)