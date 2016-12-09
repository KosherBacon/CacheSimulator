//
// Created by Joshua Kahn on 12/9/16.
//

#ifndef CACHESIMULATOR_SET_H
#define CACHESIMULATOR_SET_H

#include <cstddef>
#include <vector>
#include "CacheLine.h"

namespace Cache {
    class Set {
    private:
        size_t numLines;
        std::vector<CacheLine> lines;
    public:
        Set(size_t linesPerSet);
        ~Set();
        const struct CacheLine* getLine(unsigned int lineNum) const;
        void updateLine(unsigned int lineNum, uint32_t tag, uint32_t evictionData);
        void markLineValid(unsigned int lineNum);
        bool isLineValid(unsigned int lineNum);
    };
}

#endif //CACHESIMULATOR_SET_H
