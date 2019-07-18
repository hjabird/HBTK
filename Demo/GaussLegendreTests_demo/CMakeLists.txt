cmake_minimum_required(VERSION 3.1)

# Target
add_executable (GaussLegendreTests GaussLegendreTests_demo/GaussLegendreTests_demo.cpp)

# Library dependencies ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
target_include_directories (GaussLegendreTests PRIVATE "${PROJECT_SOURCE_DIR}/include") 
target_link_libraries (GaussLegendreTests hbtk)
 
# Visual studio ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# VS folders.
set_property(TARGET GaussLegendreTests PROPERTY FOLDER "executables")

# Destinations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set_target_properties(GaussLegendreTests PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# INSTALL ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
install (TARGETS GaussLegendreTests
         RUNTIME DESTINATION bin)
