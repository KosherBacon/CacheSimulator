cmake_minimum_required(VERSION 3.6)
project(CacheSimulator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_MAIN
    src/main.cc)

set(SOURCE_FILES
    include/rapidjson/error/en.h
    include/rapidjson/error/error.h
    include/rapidjson/internal/biginteger.h
    include/rapidjson/internal/diyfp.h
    include/rapidjson/internal/dtoa.h
    include/rapidjson/internal/ieee754.h
    include/rapidjson/internal/itoa.h
    include/rapidjson/internal/meta.h
    include/rapidjson/internal/pow10.h
    include/rapidjson/internal/regex.h
    include/rapidjson/internal/stack.h
    include/rapidjson/internal/strfunc.h
    include/rapidjson/internal/strtod.h
    include/rapidjson/internal/swap.h
    include/rapidjson/msinttypes/inttypes.h
    include/rapidjson/msinttypes/stdint.h
    include/cache.h
    include/data.h
    include/loop.h
    include/simulator.h
    src/cache.cc
    src/simulator.cc)

set(TEST_FILES
    include/Catch/catch.hpp
    tests/test_main.cc
    tests/test_simulator.cc)

add_executable(CacheSimulator ${SOURCE_MAIN} ${SOURCE_FILES})
add_executable(tests ${SOURCE_FILES} ${TEST_FILES})
