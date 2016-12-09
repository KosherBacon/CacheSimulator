//
// Created by Joshua Kahn on 12/7/16.
//

#include "../include/Cache.h"
#include "gtest/gtest.h"

// setFromAddr

TEST(setFromAddr, zeroAddrZeroBBitsZeroTBits) {
    uint32_t addr = 0x00000000;
    size_t bBits = 0;
    size_t tagBits = 0;
    EXPECT_EQ(Cache::Cache::setFromAddr(addr, bBits, tagBits), 0x0);
}

TEST(setFromAddr, zeroAddrZero30BitsZero1Bit) {
    uint32_t addr = 0x00000000;
    size_t bBits = 30;
    size_t tagBits = 1;
    EXPECT_EQ(Cache::Cache::setFromAddr(addr, bBits, tagBits), 0x0);
}

TEST(setFromAddr, nonZeroAddrZero5BitsZero18Bits) {
    uint32_t addr = 0xAAAA0020;
    size_t bBits = 5;
    size_t tagBits = 18;
    EXPECT_EQ(Cache::Cache::setFromAddr(addr, bBits, tagBits), 0x1);
}

TEST(setFromAddr, nonZeroAddrZero2BitsZero22Bits) {
    uint32_t addr = 0xAAAA4444;
    size_t bBits = 2;
    size_t tagBits = 22;
    EXPECT_EQ(Cache::Cache::setFromAddr(addr, bBits, tagBits), 0x11);
}

// tagFromAddr

TEST(tagFromAddr, zeroAddrZeroTBits) {
    uint32_t addr = 0x000000;
    size_t tagBits = 0;
    EXPECT_EQ(Cache::Cache::tagFromAddr(addr, tagBits), 0x0);
}

TEST(tagFromAddr, nonZeroAddr32TBits) {
    uint32_t addr = 0xAAAA0000;
    size_t tagBits = 32;
    EXPECT_EQ(Cache::Cache::tagFromAddr(addr, tagBits), 0x0);
}

TEST(tagFromAddr, nonZeroAddr22TBits) {
    uint32_t addr = 0xAAAA0000;
    size_t tagBits = 22;
    EXPECT_EQ(Cache::Cache::tagFromAddr(addr, tagBits), 0x2AAA80);
}

TEST(tagFromAddr, nonZeroAddr11TBits) {
    uint32_t addr = 0xCCCCCCCC;
    size_t tagBits = 11;
    EXPECT_EQ(Cache::Cache::tagFromAddr(addr, tagBits), 0x666);
}

TEST(tagFromAddr, nonZeroAddr18TBits) {
    uint32_t addr = 0xAAAA0018;
    size_t tagBits = 18;
    EXPECT_EQ(Cache::Cache::tagFromAddr(addr, tagBits), 0x2AAA8);
}
