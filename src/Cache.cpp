//
// Created by Joshua Kahn on 12/7/16.
//

#include <cassert>
#include "../include/Cache.h"

using Cache::Set;

Cache::Cache::Cache(size_t numSets, size_t linesPerSet, EvictionPolicy policy) {
    assert(numSets > 0);
    this->numSets = numSets;
    this->linesPerSet = linesPerSet;
    this->policy = policy;
    for (int i = 0; i < linesPerSet; i++) {
        this->sets.push_back(Set(linesPerSet));
    }
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

bool Cache::Cache::contains(uint32_t tag) {
    for (std::vector<Set>::iterator it = this->sets.begin(); it < this->sets.end(); it++) {
        if ((*it).contains(tag)) {
            return true;
        }
    }
    return false;
}

const Set *Cache::Cache::getSet(unsigned int setNum) const {
    return &this->sets.at(setNum);
}

void Cache::Cache::markLineValid(unsigned int setNum, unsigned int lineNum) {
    this->sets.at(setNum).markLineValid(lineNum);
}
