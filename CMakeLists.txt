cmake_minimum_required(VERSION 3.23)
project(WaveFunctionCollapse)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
file(GLOB_RECURSE src src/*.cpp)

add_executable(wavefunctioncollapse ${src})