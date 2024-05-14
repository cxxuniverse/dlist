cmake_minimum_required(VERSION 3.20)

# Project configuration
project(
    dlist
    VERSION 0.1
    DESCRIPTION "Doubly linked list implementation"
    LANGUAGES CXX
)

# Include directories
include_directories(include)

# Create static library
add_library(dlist STATIC src/dlist.cpp)
target_include_directories(dlist PRIVATE include)
set_target_properties(dlist PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Create executable
add_executable(main src/main.cpp)
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Link dlist library with events library
link_libraries(dlist ${CMAKE_CURRENT_SOURCE_LIB}/lib/libevents.a)

# Link main executable with dlist library
target_link_libraries(main dlist)

# Compiler options
target_compile_features(main PRIVATE cxx_std_20)
target_compile_options(main PRIVATE -g -Wall)