cmake_minimum_required(VERSION 3.12)
project(cpuScheduller)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpuScheduller main.cpp Process.cpp Process.h Event.cpp Event.h Thread.cpp Thread.h Burst.cpp Burst.h Cpu.h Cpu.cpp)