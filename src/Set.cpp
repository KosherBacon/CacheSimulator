//
// Created by Joshua Kahn on 12/9/16.
//

#include <algorithm>
#include <cassert>
#include "../include/Cache.h"

using Cache::CacheLine;
using Cache::SetInsertResult;

Cache::Set::Set(size_t linesPerSet, EvictionPolicy policy) {
    assert(linesPerSet != 0); // You cannot have zero lines in a set.
    this->numLines = linesPerSet;
    this->policy = policy;
    this->lines.resize(linesPerSet, (CacheLine) {false, 0, 0});
    this->usedLines.resize(0);
}

Cache::Set::~Set() {
    this->lines.clear();
    this->usedLines.clear();
}

int Cache::Set::firstEmptyLine() {
    int i = 0;
    for (auto it = this->lines.begin(); it < this->lines.end(); it++, i++) {
        if (!(*it).valid) {
            return i;
        }
    }
    return -1;
}

bool Cache::Set::LFU_compare(CacheLine *l1, CacheLine *l2) {
    return l1->evictionData >= l2->evictionData;
}

CacheLine * Cache::Set::getLine(unsigned int lineNum) {
    return &this->lines.at(lineNum);
}

void Cache::Set::updateLine(CacheLine *line, uint32_t tag, uint32_t evictionData) {
    line->tag = tag;
    line->evictionData = evictionData;
    line->valid = true;
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
    for (auto it = this->lines.begin(); it < this->lines.end(); it++, i++) {
        if ((*it).tag == tag && (*it).valid) {
            return i;
        }
    }
    return -1;
}

SetInsertResult Cache::Set::insert(uint32_t tag) {
    // Double check if specified set already contains the tag.
    // However, insert should not be called if we know the cache already contains the tag.
    SetInsertResult insertResult = {.couldInsert=false, .lineNum=0};
    int lineNum = this->contains(tag);
    if (lineNum < 0) {
        if (this->policy == LRU) {
            // Check if set is full or not.
            if (this->usedLines.size() == this->numLines) { // Set is full.
                auto lineToInsert = this->usedLines.back();
                auto linePos = (unsigned int) this->usedLines.size() - 1;
                this->updateLine(lineToInsert, tag, 0);
                this->usedLines.pop_back();
                this->usedLines.push_front(lineToInsert);
                insertResult.couldInsert = true;
                insertResult.lineNum = linePos;
                return insertResult;
            } else {
                auto linePos = (unsigned int) this->firstEmptyLine();
                auto lineToInsert = &this->lines.at(linePos);
                this->updateLine(lineToInsert, tag, 0);
                this->usedLines.push_front(lineToInsert);
                insertResult.couldInsert = true;
                insertResult.lineNum = linePos;
                return insertResult;
            }
        } else if (this->policy == LFU) {
            // Check if set is full or not.
            if (this->usedLines.size() == this->numLines) { // Set is full.
                // Ensure that the used line dequeue is sorted by each line's eviction data.
                std::sort(this->usedLines.begin(), this->usedLines.end(), LFU_compare);
                auto lineToInsert = this->usedLines.back();
                auto linePos = (unsigned int) this->usedLines.size() - 1;
                this->updateLine(lineToInsert, tag, 1);
                this->usedLines.pop_back();
                this->usedLines.push_front(lineToInsert);
                insertResult.couldInsert = true;
                insertResult.lineNum = linePos;
                return insertResult;
            } else {
                auto linePos = (unsigned int) this->firstEmptyLine();
                auto lineToInsert = &this->lines.at(linePos);
                this->updateLine(lineToInsert, tag, 1);
                this->usedLines.push_front(lineToInsert);
                insertResult.couldInsert = true;
                insertResult.lineNum = linePos;
                return insertResult;
            }
        }
    }
    return insertResult; // TODO - Change this.
}
