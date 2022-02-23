cmake_minimum_required(VERSION 3.6)
project(ReadWrite_INI)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp INI.cpp INI.h NegozioCD.ini)
add_executable(ReadWrite_INI ${SOURCE_FILES})

add_subdirectory(test)
set(SOURCE_FILES INI.cpp)
add_executable(unit_testing_self_contained main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(unit_testing_self_contained core)
