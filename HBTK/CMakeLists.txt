cmake_minimum_required(VERSION 2.8.9)
project(HBTK)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include/HBTK)

file(GLOB SOURCES "src/*.cpp")

add_library(HBTK STATIC ${SOURCES})
