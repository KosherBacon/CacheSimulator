//
// Created by Joshua Kahn on 12/9/16.
//

#include <cassert>
#include "../include/Set.h"

Cache::Set::Set(size_t linesPerSet) {
    assert(linesPerSet != 0); // You cannot have zero lines in a set.
    this->lines.resize(linesPerSet, {false, 0, 0});
}

Cache::Set::~Set() {
    this->lines.clear();
}

const struct Cache::CacheLine* Cache::Set::getLine(unsigned int lineNum) const {
    return &this->lines.at(lineNum);
}

void Cache::Set::updateLine(unsigned int lineNum, uint32_t tag, uint32_t evictionData) {
    this->lines.at(lineNum).tag = tag;
    this->lines.at(lineNum).evictionData = evictionData;
    this->markLineValid(lineNum);
}

void Cache::Set::markLineValid(unsigned int lineNum) {
    this->lines.at(lineNum).valid = true;
}

bool Cache::Set::isLineValid(unsigned int lineNum) {
    return this->lines.at(lineNum).valid;
}
