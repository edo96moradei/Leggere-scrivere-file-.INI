cmake_minimum_required(VERSION 3.6)

add_subdirectory(./lib/googletest-main)
set(gtest_SOURCE_DIR, ./lib/googletest-main)
include_directories(${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR})
set(SOURCE_TEST_FILES testINI.cpp)
add_executable(runINITests ${SOURCE_TEST_FILES})
target_link_libraries(runINITests gtest gtest_main core)