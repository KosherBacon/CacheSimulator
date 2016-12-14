//
// Created by Joshua Kahn on 12/9/16.
//

#include <algorithm>
#include <cassert>
#include "../include/Cache.h"

using Cache::CacheLine;

Cache::Set::Set(size_t linesPerSet, EvictionPolicy policy) {
    assert(linesPerSet != 0); // You cannot have zero lines in a set.
    this->numLines = linesPerSet;
    this->policy = policy;
    this->lines.resize(linesPerSet, (CacheLine) {false, 0, 0});
    this->usedLines.resize(linesPerSet);
    this->usedLinesCount = 0;
}

Cache::Set::~Set() {
    this->lines.clear();
    this->usedLines.clear();
}

int Cache::Set::firstEmptyLine() {
    int i = 0;
    for (std::vector<CacheLine>::iterator it = this->lines.begin(); it < this->lines.end(); it++, i++) {
        if (!(*it).valid) {
            return i;
        }
    }
    return -1;
}

CacheLine * Cache::Set::getLine(unsigned int lineNum) {
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

int Cache::Set::contains(uint32_t tag) {
    int i = 0;
    for (std::vector<CacheLine>::iterator it = this->lines.begin(); it < this->lines.end(); it++, i++) {
        if ((*it).tag == tag && (*it).valid) {
            return i;
        }
    }
    return -1;
}

std::deque<unsigned int> Cache::Set::getUsedLines() {
    return this->usedLines;
}

int Cache::Set::insert(uint32_t tag) {
    // Double check if specified set already contains the tag.
    int lineNum = this->contains(tag);
    if (lineNum < 0) {
        if (this->policy == LRU) {
            if (this->usedLinesCount == this->numLines) {
                unsigned int lineToInsert = this->usedLines.back();
                this->updateLine(lineToInsert, tag, 0);
                this->usedLines.pop_back();
                this->usedLines.push_front(lineToInsert);
                return lineToInsert;
            } else {
                unsigned int lineToInsert = (unsigned int) this->firstEmptyLine();
                this->updateLine(lineToInsert, tag, 0);
                this->usedLines.push_front(lineToInsert);
                this->usedLinesCount++;
                return lineToInsert;
            }
        }
    }
    return -1; // TODO - Change this.
}
