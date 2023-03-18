
cmake_minimum_required(VERSION 3.20)

project(strsh)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -Werror -fcolor-diagnostics")


add_executable(strsh
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/Location.cpp
    ${CMAKE_SOURCE_DIR}/src/SourceBuffer.cpp)
