//
// Created by Joshua Kahn on 12/9/16.
//

#include "../include/Set.h"
#include "gtest/gtest.h"

// Set constructor.

TEST(setConstructor, oneLinePerSet) {
    size_t linesPerSet = 1;
    Cache::Set set = Cache::Set(linesPerSet);
    EXPECT_EQ(*set.getLine(0), ((Cache::CacheLine) {false, 0, 0}));
}

TEST(setConstructor, zeroLinesPerSet) {
    ASSERT_DEATH(Cache::Set(0), "");
}

TEST(setConstructor, twoLinesPerSet) {
    size_t linesPerSet = 2;
    Cache::Set set = Cache::Set(linesPerSet);
    EXPECT_EQ(*set.getLine(0), ((Cache::CacheLine) {false, 0, 0}));
    EXPECT_EQ(*set.getLine(1), ((Cache::CacheLine) {false, 0, 0}));
}

TEST(setUpdateLine, twoDifferentLinesPerSet) {
    size_t linesPerSet = 2;
    Cache::Set set = Cache::Set(linesPerSet);
    set.updateLine(1, 1, 2);
    EXPECT_EQ(*set.getLine(0), ((Cache::CacheLine) {false, 0, 0}));
    EXPECT_EQ(*set.getLine(1), ((Cache::CacheLine) {true, 1, 2}));
}

TEST(setMarkLineValid, oneLinePerSet) {
    size_t linesPerSet = 1;
    Cache::Set set = Cache::Set(linesPerSet);
    set.markLineValid(0);
    EXPECT_TRUE((*set.getLine(0)).valid);
}

TEST(setIsLineValid, invalidLine) {
    size_t linesPerSet = 1;
    Cache::Set set = Cache::Set(linesPerSet);
    EXPECT_FALSE(set.isLineValid(0));
}

TEST(setIsLineValid, validLine) {
    size_t linesPerSet = 1;
    Cache::Set set = Cache::Set(linesPerSet);
    set.markLineValid(0);
    EXPECT_TRUE(set.isLineValid(0));
}
