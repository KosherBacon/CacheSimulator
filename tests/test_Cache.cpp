//
// Created by Joshua Kahn on 12/7/16.
//

#include "../include/Cache.h"
#include "gtest/gtest.h"

// Cache constructor

TEST(cacheConstructor, oneSetDirectMap) {
    size_t numSets = 1;
    size_t linesPerSet = 1;
    Cache::EvictionPolicy policy = Cache::DIRECT_MAP;
    size_t bBits = 6;
    size_t tagBits = 26;
    Cache::Cache cache = Cache::Cache(numSets, linesPerSet, bBits, tagBits, policy);
    EXPECT_EQ(*cache.getSet(0)->getLine(0), ((Cache::CacheLine) {false, 0, 0}));
}

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

TEST(setFromAddr, nonZeroAddrZeroSetBits) {
    uint32_t addr = 0xAAAA4444;
    size_t bBits = 16;
    size_t tagBits = 16;
    EXPECT_EQ(Cache::Cache::setFromAddr(addr, bBits, tagBits), 0x0);
}

TEST(setFromAddr, nonZeroAddr1SetBit) {
    uint32_t addr = 0xAAAA0000;
    size_t bBits = 13;
    size_t tagBits = 18;
    EXPECT_EQ(Cache::Cache::setFromAddr(addr, bBits, tagBits), 0x0);
    addr = 0xAAAA2000;
    EXPECT_EQ(Cache::Cache::setFromAddr(addr, bBits, tagBits), 0x1);
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

// Cache contains

TEST(cacheContains, tagInCacheAllInvalid) {
    size_t numSets = 1;
    size_t linesPerSet = 1;
    Cache::EvictionPolicy policy = Cache::LRU;
    size_t bBits = 6;
    size_t tagBits = 26;
    Cache::Cache cache = Cache::Cache(numSets, linesPerSet, bBits, tagBits, policy);
    EXPECT_FALSE(cache.contains(0));
}

TEST(cacheContains, tagInCacheValid) {
    size_t numSets = 1;
    size_t linesPerSet = 1;
    Cache::EvictionPolicy policy = Cache::LFU;
    size_t bBits = 6;
    size_t tagBits = 26;
    Cache::Cache cache = Cache::Cache(numSets, linesPerSet, bBits, tagBits, policy);
    cache.markLineValid(0, 0);
    EXPECT_TRUE(cache.contains(0));
}

// Cache insert

TEST(cacheInsert, lruCache) {
    uint32_t addr = 0xAAAA0018;
    size_t bBits = 14;
    size_t tagBits = 18;
    uint32_t tag = Cache::Cache::tagFromAddr(addr, tagBits);
    size_t numSets = 1;
    size_t linesPerSet = 1;
    Cache::EvictionPolicy policy = Cache::LRU;
    Cache::Cache cache = Cache::Cache(numSets, linesPerSet, bBits, tagBits, policy);
    EXPECT_EQ(cache.insert(addr).lineNum, 0);
    EXPECT_TRUE(cache.contains(tag));
    // Overwrite the old line and make sure the new one takes its place.
    addr = 0xCCCCCCCC;
    tag = Cache::Cache::tagFromAddr(addr, tagBits);
    EXPECT_EQ(cache.insert(addr).lineNum, 0);
    EXPECT_TRUE(cache.contains(tag));
}

TEST(cacheInsert, lruCache2LinesInSet) {
    uint32_t addr = 0xAAAA0018;
    size_t bBits = 14;
    size_t tagBits = 18;
    uint32_t tag = Cache::Cache::tagFromAddr(addr, tagBits);
    size_t numSets = 1;
    size_t linesPerSet = 2;
    Cache::EvictionPolicy policy = Cache::LRU;
    Cache::Cache cache = Cache::Cache(numSets, linesPerSet, bBits, tagBits, policy);
    EXPECT_EQ(cache.insert(addr).lineNum, 0);
    EXPECT_EQ(cache.insert(addr).setNum, 0);
    EXPECT_TRUE(cache.contains(tag));
    // Overwrite the old line and make sure the it goes to a different cache line.
    addr = 0xCCCCCCCC;
    tag = Cache::Cache::tagFromAddr(addr, tagBits);
    EXPECT_EQ(cache.insert(addr).lineNum, 1);
    EXPECT_EQ(cache.insert(addr).setNum, 0);
    EXPECT_TRUE(cache.contains(tag));
}

TEST(cacheInsert, lruCache2Sets2LinesInSet) {
    uint32_t addr = 0xAAAA0000;
    size_t bBits = 13;
    size_t tagBits = 18;
    uint32_t tag = Cache::Cache::tagFromAddr(addr, tagBits);
    size_t numSets = 2;
    size_t linesPerSet = 2;
    Cache::EvictionPolicy policy = Cache::LRU;
    Cache::Cache cache = Cache::Cache(numSets, linesPerSet, bBits, tagBits, policy);
    Cache::CacheInsertResult result = cache.insert(addr);
    EXPECT_EQ(result.setNum, 0);
    EXPECT_EQ(result.lineNum, 0);
    EXPECT_TRUE(cache.contains(tag));
    // In this hypothetical cache, this address will go to a different set than the first address.
    addr = 0xAAAA2000;
    tag = Cache::Cache::tagFromAddr(addr, tagBits);
    result = cache.insert(addr);
    EXPECT_EQ(result.setNum, 1);
    EXPECT_EQ(result.lineNum, 0);
    EXPECT_TRUE(cache.contains(tag));
}
