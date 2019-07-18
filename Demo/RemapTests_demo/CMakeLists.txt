cmake_minimum_required(VERSION 3.1)

# Target
add_executable (RemapTests_demo RemapTests_demo/RemapTests_demo.cpp)

# Library dependencies ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
target_include_directories (RemapTests_demo PRIVATE "${PROJECT_SOURCE_DIR}/include") 
target_link_libraries (RemapTests_demo hbtk)
 
# Visual studio ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# VS folders.
set_property(TARGET RemapTests_demo PROPERTY FOLDER "executables")

# Destinations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set_target_properties(RemapTests_demo PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# INSTALL ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
install (TARGETS RemapTests_demo
         RUNTIME DESTINATION bin)

