# Properties->C/C++->General->Additional Include Directories
include_directories ("${PROJECT_SOURCE_DIR}/HBTK/include")
 
# Set Properties->General->Configuration Type to Application(.exe)
# Creates app.exe with the listed sources (main.cxx)
# Adds sources to the Solution Explorer
add_executable (GaussQuadrature_demo GaussQuadrature_demo/GaussQuadrature_demo.cpp)
 
# Properties->Linker->Input->Additional Dependencies
target_link_libraries (GaussQuadrature_demo HBTK)
 
# Creates a folder "executables" and adds target 
# project (app.vcproj) under it
set_property(TARGET GaussQuadrature_demo PROPERTY FOLDER "executables")
 
# Properties->General->Output Directory
set_target_properties(GaussQuadrature_demo PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
 
# Adds logic to INSTALL.vcproj to copy app.exe to destination directory
install (TARGETS GaussQuadrature_demo
         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install)