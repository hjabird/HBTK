cmake_minimum_required(VERSION 3.1)


message("CMAKE_INSTALL_PREFIX " ${CMAKE_INSTALL_PREFIX})
message("CMAKE_PREFIX_PATH " ${CMAKE_PREFIX_PATH})
message("CMAKE_INCLUDE_PATH " ${CMAKE_PREFIX_PATH})
 

file (GLOB HBTK_INCLUDE "include/HBTK/*.h")
file (GLOB HBTK_SOURCE  "src/*.cpp")
source_group("" FILES ${HBTK})
source_group("include" FILES ${HBTK_INCLUDE})
source_group("source" FILES ${HBTK_SOURCE})
 
include_directories (include/HBTK)
 
add_library(HBTK  ${HBTK_INCLUDE} 
                  ${HBTK_SOURCE})
 
set_property(TARGET HBTK PROPERTY FOLDER "libraries")
set_target_properties(HBTK PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
		      PUBLIC_HEADER "${HBTK_INCLUDE}")
 
 

install (TARGETS HBTK EXPORT FindHBTK
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	PUBLIC_HEADER DESTINATION include/HBTK
	INCLUDES DESTINATION include/)
install (EXPORT FindHBTK
	DESTINATION cmake/
	CONFIGURATIONS DEBUG RELEASE)
         

