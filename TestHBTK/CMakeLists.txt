# HBTK tests.
cmake_minimum_required(VERSION 3.1)

# Include Catch2 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INCLUDE(ExternalProject)
ExternalProject_Add(catch2
    PREFIX 3rd_party
    GIT_REPOSITORY https://github.com/catchorg/Catch2
    INSTALL_COMMAND ""
    )
    
ExternalProject_Get_Property(catch2 source_dir binary_dir)
include_directories("${source_dir}/single_include")  

# Add HBTK library ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
include_directories ("${PROJECT_SOURCE_DIR}/HBTK/include") 
link_libraries (HBTK)

# Find all of our tests sources
file (GLOB TESTHBTK_SOURCE  "tests/*.cpp")
source_group("tests_source" FILES ${TESTHBTK_SOURCE})

# And add the main as an executable ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
enable_testing()
add_executable(all_tests ${TESTHBTK_SOURCE})
add_test(NAME all_tests
    COMMAND run_tests)
    