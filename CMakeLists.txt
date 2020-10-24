cmake_minimum_required(VERSION 3.17)
project(assignment-4)

set(CMAKE_CXX_STANDARD 17)

set(
    SOURCES
    SLLString.cpp
)

add_subdirectory(tests)

add_executable(assignment-4 ass4.cpp ${SOURCES})
add_library(libassignment-4 STATIC ${SOURCES})
add_compile_options(-Wall -Wextra -pedantic)