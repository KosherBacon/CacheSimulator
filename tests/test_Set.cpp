//
// Created by Joshua Kahn on 12/9/16.
//

#include "../include/EvictionPolicy.h"
#include "../include/Set.h"
#include "gtest/gtest.h"

// Set constructor.

TEST(setConstructor, oneLinePerSet) {
    size_t linesPerSet = 1;
    Cache::Set set = Cache::Set(linesPerSet, Cache::LRU);
    EXPECT_EQ(*set.getLine(0), ((Cache::CacheLine) {false, 0, 0}));
}

TEST(setConstructor, zeroLinesPerSet) {
    ASSERT_DEATH(Cache::Set(0, Cache::LRU), "");
}

TEST(setConstructor, twoLinesPerSet) {
    size_t linesPerSet = 2;
    Cache::Set set = Cache::Set(linesPerSet, Cache::LRU);
    EXPECT_EQ(*set.getLine(0), ((Cache::CacheLine) {false, 0, 0}));
    EXPECT_EQ(*set.getLine(1), ((Cache::CacheLine) {false, 0, 0}));
}

TEST(setUpdateLine, twoDifferentLinesPerSet) {
    size_t linesPerSet = 2;
    Cache::Set set = Cache::Set(linesPerSet, Cache::LRU);
    set.updateLine(1, 1, 2);
    EXPECT_EQ(*set.getLine(0), ((Cache::CacheLine) {false, 0, 0}));
    EXPECT_EQ(*set.getLine(1), ((Cache::CacheLine) {true, 1, 2}));
}

// Set LFU_Compare

TEST(setLFUCompare, firstLineMoreFrequentlyUsed) {
    Cache::CacheLine cl1 = {.valid=true, .tag=0xAAAAAAAA, .evictionData=2};
    Cache::CacheLine cl2 = {.valid=true, .tag=0xBBBBBBBB, .evictionData=1};
    EXPECT_TRUE(Cache::Set::LFU_compare(&cl1, &cl2));
}

TEST(setLFUCompare, secondLineMoreFrequentlyUsed) {
    Cache::CacheLine cl1 = {.valid=true, .tag=0xAAAAAAAA, .evictionData=1};
    Cache::CacheLine cl2 = {.valid=true, .tag=0xBBBBBBBB, .evictionData=2};
    EXPECT_FALSE(Cache::Set::LFU_compare(&cl1, &cl2));
}

TEST(setLFUCompare, bothLinesEqualFrequentlyUsed) {
    Cache::CacheLine cl1 = {.valid=true, .tag=0xAAAAAAAA, .evictionData=1};
    Cache::CacheLine cl2 = {.valid=true, .tag=0xBBBBBBBB, .evictionData=1};
    EXPECT_TRUE(Cache::Set::LFU_compare(&cl1, &cl2));
}

// Set markLineValid

TEST(setMarkLineValid, oneLinePerSet) {
    size_t linesPerSet = 1;
    Cache::Set set = Cache::Set(linesPerSet, Cache::LRU);
    set.markLineValid(0);
    EXPECT_TRUE((*set.getLine(0)).valid);
}

// Set isLineValid

TEST(setIsLineValid, invalidLine) {
    size_t linesPerSet = 1;
    Cache::Set set = Cache::Set(linesPerSet, Cache::LRU);
    EXPECT_FALSE(set.isLineValid(0));
}

TEST(setIsLineValid, validLine) {
    size_t linesPerSet = 1;
    Cache::Set set = Cache::Set(linesPerSet, Cache::LRU);
    set.markLineValid(0);
    EXPECT_TRUE(set.isLineValid(0));
}

// Set contains

TEST(setContains, containsInvalidLine) {
    size_t linesPerSet = 1;
    Cache::Set set = Cache::Set(linesPerSet, Cache::LRU);
    EXPECT_EQ(set.contains(0), -1);
}

TEST(setContains, containsValidLine) {
    size_t linesPerSet = 1;
    Cache::Set set = Cache::Set(linesPerSet, Cache::LRU);
    set.markLineValid(0);
    EXPECT_EQ(set.contains(0), 0);
}

TEST(setContains, notContainsInvalidLine) {
    size_t linesPerSet = 1;
    Cache::Set set = Cache::Set(linesPerSet, Cache::LRU);
    EXPECT_EQ(set.contains(1), -1);
}

TEST(setContains, notContainsValidLine) {
    size_t linesPerSet = 1;
    Cache::Set set = Cache::Set(linesPerSet, Cache::LRU);
    set.markLineValid(0);
    EXPECT_EQ(set.contains(1), -1);
}
