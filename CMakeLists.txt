cmake_minimum_required(VERSION 3.1)
project(hbtk CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HBTK_MAJOR 0)
set(HBTK_MINOR 1)
set(HBTK_PATCHLEVEL 0)
set(HBTK_VERSION ${HBTK_MAJOR}.${HBTK_MINOR}.${HBTK_PATCHLEVEL})
 
option(BUILD_DEMO_PROGRAMS "Builds demo programs" OFF)
option(BUILD_UNIT_TESTS "Builds the unit tests" OFF)
 
# Enable folders in Visual studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file (GLOB hbtk_INCLUDE "include/hbtk/*.h")
file (GLOB hbtk_SOURCE  "src/*.cpp")
source_group("" FILES ${hbtk})
source_group("include" FILES ${hbtk_INCLUDE})
source_group("source" FILES ${hbtk_SOURCE})
 
include_directories(include/hbtk)
add_library(hbtk  ${hbtk_INCLUDE} 
                  ${hbtk_SOURCE})
				  
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    link_libraries(hbtk m)   # Maths std library.
endif()
 

include(GNUInstallDirs)
set_target_properties(hbtk PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
                      PUBLIC_HEADER "${hbtk_INCLUDE}")
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS hbtk
    EXPORT hbtk-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(EXPORT hbtk-targets
  FILE
    hbtk-config.cmake
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/hbtk
)

if(BUILD_DEMO_PROGRAMS)
    add_subdirectory(demo)
endif(BUILD_DEMO_PROGRAMS)
if(BUILD_UNIT_TESTS)
    add_subdirectory(test)
endif(BUILD_UNIT_TESTS)
