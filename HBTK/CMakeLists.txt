# Collect sources into the variable MATH_SOURCES without
# having to explicitly list each header and source file.
#
# CMake documentation states "We do not recommend using GLOB to collect a
# list of source files from your source tree. If no CMakeLists.txt file
# changes when a source is added or removed then the generated build system
# cannot know when to ask CMake to regenerate".
#file (GLOB MATH_SOURCES
#      "*.h")
message("CMAKE_INSTALL_PREFIX " ${CMAKE_INSTALL_PREFIX})
message("CMAKE_PREFIX_PATH " ${CMAKE_PREFIX_PATH})
message("CMAKE_INCLUDE_PATH " ${CMAKE_PREFIX_PATH})
 
# Collect sources into the variable SIMPLE_FUNCTION_SOURCES
file (GLOB HBTK_INCLUDE "include/HBTK/*.h")
file (GLOB HBTK_SOURCE  "src/*.cpp")
 
# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("" FILES ${HBTK})
source_group("include" FILES ${HBTK_INCLUDE})
source_group("source" FILES ${HBTK_SOURCE})
 
# Properties->C/C++->General->Additional Include Directories
include_directories (include/HBTK)
 
# Set Properties->General->Configuration Type to Dynamic Library(.dll)
# Creates math.dll with the listed sources collected in the variables
# Also adds sources to the Solution Explorer
add_library(HBTK STATIC ${HBTK_INCLUDE} 
                        ${HBTK_SOURCE})
 
# Creates folder "libraries" and adds target project (math.vcproj)
set_property(TARGET HBTK PROPERTY FOLDER "libraries")
 
# Properties->General->Output Directory
set_target_properties(HBTK PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
 
 
# Adds logic to INSTALL.vcproj to copy math.dll to the destination directory

install (TARGETS HBTK
	EXPORT HBTK_export
	DESTINATION lib)
install (FILES ${HBTK_INCLUDE}
	DESTINATION include/HBTK/)
         

