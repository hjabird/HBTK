cmake_minimum_required(VERSION 2.8.9)
project(HBTK)
set(CMAKE_BUILD_TYPE Release)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_library(HBTK STATIC ${SOURCES})
