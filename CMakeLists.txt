cmake_minimum_required(VERSION 3.2)

project(CacheSimulator)

add_definitions(-std=c++0x)

set(CMAKE_CXX_STANDARD 11)

set(MAIN_FILE
        src/main.cpp)

set(SOURCE_FILES
        src/Cache.cpp
        src/Set.cpp
        src/Simulator.cpp
        include/Cache.h
        include/Set.h
        include/CacheLine.h
        include/DataStructure.h
        include/EvictionPolicy.h
        include/CacheInsertResult.h
        include/Simulator.h
        include/SimulatorError.h
        include/SetInsertResult.h include/Loop.h)
add_executable(CacheSimulator ${MAIN_FILE} ${SOURCE_FILES})

set(TEST_FILES
        tests/test_Cache.cpp
        tests/test_Set.cpp
        tests/test_CacheLine.cpp
        tests/test_Simulator.cpp)

add_custom_target(clean-coverage
        COMMAND lcov --directory . --zerocounters -q
        )

add_custom_target(testTarget)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0") # debug, no optimisation
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage") # enabling coverage
endif()

# Add rapidjson library.
include_directories(submodules/rapidjson/include submodules/rapidjson)

# Setup the googletest library and create a testing executable.
add_subdirectory(submodules/googletest)
enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(runUnitTests ${TEST_FILES} ${SOURCE_FILES})
target_link_libraries(runUnitTests gtest gtest_main)
add_dependencies(testTarget runUnitTests clean-coverage)
