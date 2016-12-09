cmake_minimum_required(VERSION 2.8)

project(CacheSimulator)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

set(CMAKE_CXX_STANDARD 11)

set(MAIN_FILE
        src/main.cpp)

set(SOURCE_FILES
        src/Cache.cpp
        include/Cache.h)
add_executable(CacheSimulator ${MAIN_FILE} ${SOURCE_FILES})


# Setup the googletest library and create a testing executable.
set(TEST_FILES
        tests/test_Cache.cpp)

add_custom_target(testTarget)

add_subdirectory(submodules/googletest)
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runUnitTests ${TEST_FILES} ${SOURCE_FILES})
target_link_libraries(runUnitTests gtest gtest_main)
add_dependencies(testTarget runUnitTests)