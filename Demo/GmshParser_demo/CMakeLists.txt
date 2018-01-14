
# Properties->C/C++->General->Additional Include Directories
include_directories ("${PROJECT_SOURCE_DIR}/HBTK/include")
 
# Set Properties->General->Configuration Type to Application(.exe)
# Creates app.exe with the listed sources (main.cxx)
# Adds sources to the Solution Explorer
add_executable (GMSH_Info GmshParser_demo/GmshParser_demo.cpp)
 
# Properties->Linker->Input->Additional Dependencies
target_link_libraries (GMSH_Info HBTK)
 
# Creates a folder "executables" and adds target 
# project (app.vcproj) under it
set_property(TARGET GMSH_Info PROPERTY FOLDER "executables")
 
# Properties->General->Output Directory
set_target_properties(GMSH_Info PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
 
# Adds logic to INSTALL.vcproj to copy app.exe to destination directory
install (TARGETS GMSH_Info
         RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/_install)
