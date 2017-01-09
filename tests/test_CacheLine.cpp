//
// Created by Joshua Kahn on 1/9/17.
//

#include "gtest/gtest.h"
#include "../include/CacheLine.h"

// CacheLine operator==

TEST(cacheLineOperatorEqualEqual, linesAreEqual) {
    Cache::CacheLine cl1 = {.valid=true, .tag=0x0, .evictionData=2};
    Cache::CacheLine cl2 = {.valid=true, .tag=0x0, .evictionData=2};
    EXPECT_TRUE(cl1 == cl2);
}

TEST(cacheLineOperatorEqualEqual, linesAreNotEqualEvictionDataDifferent) {
    Cache::CacheLine cl1 = {.valid=true, .tag=0x0, .evictionData=1};
    Cache::CacheLine cl2 = {.valid=true, .tag=0x0, .evictionData=2};
    EXPECT_FALSE(cl1 == cl2);
}

TEST(cacheLineOperatorEqualEqual, linesAreNotEqualTagDifferent) {
    Cache::CacheLine cl1 = {.valid=true, .tag=0x0, .evictionData=2};
    Cache::CacheLine cl2 = {.valid=true, .tag=0x1, .evictionData=2};
    EXPECT_FALSE(cl1 == cl2);
}

TEST(cacheLineOperatorEqualEqual, linesAreNotEqualValidDifferent) {
    Cache::CacheLine cl1 = {.valid=true, .tag=0x0, .evictionData=2};
    Cache::CacheLine cl2 = {.valid=false, .tag=0x0, .evictionData=2};
    EXPECT_FALSE(cl1 == cl2);
}
