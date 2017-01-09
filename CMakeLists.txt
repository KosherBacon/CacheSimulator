cmake_minimum_required(VERSION 3.2)

project(CacheSimulator)

add_definitions(-std=c++0x)

set(CMAKE_CXX_STANDARD 11)

set(MAIN_FILE
        src/main.cpp)

set(SOURCE_FILES
        src/Cache.cpp
        src/Set.cpp
        include/Cache.h
        include/Set.h
        include/CacheLine.h
        include/EvictionPolicy.h
        include/CacheInsertResult.h src/Simulator.cpp include/Simulator.h include/SetInsertResult.h)
add_executable(CacheSimulator ${MAIN_FILE} ${SOURCE_FILES})


# Setup the googletest library and create a testing executable.
set(TEST_FILES
        tests/test_Cache.cpp tests/test_Set.cpp)

add_custom_target(clean-coverage
        COMMAND lcov --directory . --zerocounters -q
        )

add_custom_target(testTarget)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0") # debug, no optimisation
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage") # enabling coverage
endif()

add_subdirectory(submodules/googletest)
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runUnitTests ${TEST_FILES} ${SOURCE_FILES})
target_link_libraries(runUnitTests gtest gtest_main)
add_dependencies(testTarget runUnitTests clean-coverage)
