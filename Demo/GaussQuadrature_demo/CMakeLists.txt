cmake_minimum_required(VERSION 3.1)

# Target
add_executable (GaussQuadrature_demo GaussQuadrature_demo/GaussQuadrature_demo.cpp)

# Library dependencies ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
target_include_directories (GaussQuadrature_demo PRIVATE "${PROJECT_SOURCE_DIR}/HBTK/include") 
target_link_libraries (GaussQuadrature_demo HBTK)
 
# Visual studio ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# VS folders.
set_property(TARGET GaussQuadrature_demo PROPERTY FOLDER "executables")

# Destinations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set_target_properties(GaussQuadrature_demo PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# INSTALL ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
install (TARGETS GaussQuadrature_demo
         RUNTIME DESTINATION bin)

