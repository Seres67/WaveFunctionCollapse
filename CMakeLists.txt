cmake_minimum_required(VERSION 3.23)
project(WaveFunctionCollapse)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)
file(GLOB_RECURSE src src/*.cpp)

find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
find_package(CImg REQUIRED)

add_executable(wavefunctioncollapse ${src})
target_link_libraries(wavefunctioncollapse ZLIB::ZLIB PNG::PNG CImg::CImg)