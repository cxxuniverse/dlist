#if(NOT CMAKE_BUILD_TYPE)
#    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
#endif()

set(CMAKE_BUILD_TYPE "Release")

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
add_library(dlist STATIC include/dlist.cpp)
target_include_directories(dlist PRIVATE include)

# Set custom output directories based on the operating system and build type
if(WIN32)
    set_target_properties(dlist PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/win
    )
else()
    set_target_properties(dlist PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
    )
endif()



if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Create executable
    add_executable(main src/main.cpp)
    set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

    # Link dlist library with events library
    link_libraries(dlist ${CMAKE_CURRENT_SOURCE_DIR}/lib/libevents.a)

    # Link main executable with dlist library
    if(WIN32)
        target_link_libraries(main ${CMAKE_CURRENT_SOURCE_DIR}/win/dlist.lib)
    else()
        target_link_libraries(main dlist)
    endif()

    # Compiler options
    target_compile_features(main PRIVATE cxx_std_20)
    target_compile_options(main PRIVATE -g -Wall)
endif()
