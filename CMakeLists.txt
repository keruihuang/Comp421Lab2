cmake_minimum_required(VERSION 3.6)
project(Comp421Lab2)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES Yalnix.c help.h)
add_executable(Comp421Lab2 ${SOURCE_FILES})