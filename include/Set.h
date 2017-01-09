//
// Created by Joshua Kahn on 12/9/16.
//

#ifndef CACHESIMULATOR_SET_H
#define CACHESIMULATOR_SET_H

#include <cstddef>
#include <deque>
#include <vector>
#include "CacheLine.h"
#include "EvictionPolicy.h"
#include "SetInsertResult.h"

namespace Cache {
    class Set {
    private:
        size_t numLines;
        Cache::EvictionPolicy policy;
        std::vector<CacheLine> lines;
        // Used for keeping track of lines and which ones we are going to eject.
        std::deque<CacheLine*> usedLines;
        int firstEmptyLine();
        static bool LFU_compare(CacheLine *l1, CacheLine *l2);
    public:
        Set(size_t linesPerSet, EvictionPolicy policy);
        ~Set();
        CacheLine * getLine(unsigned int lineNum);
        void updateLine(unsigned int lineNum, uint32_t tag, uint32_t evictionData);
        void updateLine(CacheLine *line, uint32_t tag, uint32_t evictionData);
        void markLineValid(unsigned int lineNum);
        bool isLineValid(unsigned int lineNum);
        int contains(uint32_t tag);
        SetInsertResult insert(uint32_t tag);
    };
}

#endif //CACHESIMULATOR_SET_H
