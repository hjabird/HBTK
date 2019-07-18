cmake_minimum_required(VERSION 3.1)

# Target
add_executable (Plot3D_converter Plot3D_converter_demo/Plot3D_converter_demo.cpp)

# Library dependencies ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
target_include_directories (Plot3D_converter PRIVATE "${PROJECT_SOURCE_DIR}/include") 
target_link_libraries (Plot3D_converter hbtk)
 
# Visual studio ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# VS folders.
set_property(TARGET Plot3D_converter PROPERTY FOLDER "executables")

# Destinations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set_target_properties(Plot3D_converter PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# INSTALL ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
install (TARGETS Plot3D_converter
         RUNTIME DESTINATION bin)
