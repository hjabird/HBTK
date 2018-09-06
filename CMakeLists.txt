cmake_minimum_required(VERSION 3.1)
project(HBTK_ALL)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 
option(BUILD_DEMO_PROGRAMS "Builds demo programs" OFF)
option(BUILD_UNIT_TESTS "Builds the unit tests" OFF)
 
 
# Enable folders in Visual studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
 
# Sub-directories where more CMakeLists.txt exist
add_subdirectory (HBTK)
if(BUILD_DEMO_PROGRAMS)
    add_subdirectory(Demo)
endif(BUILD_DEMO_PROGRAMS)
if(BUILD_UNIT_TESTS)
    add_subdirectory(TestHBTK)
endif(BUILD_UNIT_TESTS)

