//
// Created by Joshua Kahn on 12/7/16.
//

#include <cassert>
#include "../include/Cache.h"
#include "../include/SetInsertResult.h"

using Cache::Set;
using Cache::CacheInsertResult;
using Cache::SetInsertResult;

Cache::Cache::Cache(size_t numSets, size_t linesPerSet, size_t bBits, size_t tagBits, EvictionPolicy policy) {
    assert(numSets > 0);
    this->numSets = numSets;
    this->linesPerSet = linesPerSet;
    this->bBits = bBits;
    this->tagBits = tagBits;
    this->policy = policy;
    this->sets.resize(numSets, Set(linesPerSet, policy));
}

Cache::Cache::~Cache() {
    this->sets.clear();
}

uint32_t Cache::Cache::setFromAddr(uint32_t addr, size_t bBits, size_t tagBits) {
    if (bBits + tagBits >= 32) {
        return 0;
    }
    return ((addr << tagBits) >> tagBits) >> bBits;
}

uint32_t Cache::Cache::tagFromAddr(uint32_t addr, size_t tagBits) {
    if (tagBits >= 32) {
        return 0;
    }
    return addr >> (32 - tagBits);
}

CacheInsertResult Cache::Cache::insert(uint32_t addr) {
    uint32_t set = setFromAddr(addr, this->bBits, this->tagBits);
    uint32_t tag = tagFromAddr(addr, this->tagBits);
    SetInsertResult insertResult = this->sets.at(set).insert(tag);
    return (CacheInsertResult) {.couldInsert=insertResult.couldInsert, .setNum=set, .lineNum=insertResult.lineNum};
}

bool Cache::Cache::contains(uint32_t tag) {
    for (std::vector<Set>::iterator it = this->sets.begin(); it < this->sets.end(); it++) {
        if ((*it).contains(tag) >= 0) {
            return true;
        }
    }
    return false;
}

Set *Cache::Cache::getSet(unsigned int setNum) {
    return &this->sets.at(setNum);
}

void Cache::Cache::markLineValid(unsigned int setNum, unsigned int lineNum) {
    this->sets.at(setNum).markLineValid(lineNum);
}
