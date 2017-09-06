cmake_minimum_required(VERSION 3.8)
project(problem5_A_CyclicSmoothing)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp XY.cpp Smoothing.cpp parameter.h)
add_executable(problem5_A_CyclicSmoothing ${SOURCE_FILES})