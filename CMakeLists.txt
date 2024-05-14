cmake_minimum_required(VERSION 3.20)

project(
    dlist
    VERSION 0.1
    DESCRIPTION "Doubly linked list implementation"
    LANGUAGES CXX
)

include_directories(BEFORE include)

add_library(dlist STATIC src/dlist.cpp)
target_include_directories(dlist PUBLIC include)
set_target_properties(dlist PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(main src/main.cpp)
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

target_link_libraries(main dlist)
# target_link_libraries(main test)

target_compile_features(main PUBLIC cxx_std_20)
target_compile_options(main PUBLIC -g -Wall -Werror)

