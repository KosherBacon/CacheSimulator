//
// Created by Joshua Kahn on 12/7/16.
//

#ifndef CACHESIMULATOR_CACHE_H
#define CACHESIMULATOR_CACHE_H

#include <cstdint>
#include <cstddef>
#include <vector>
#include "CacheInsertResult.h"
#include "EvictionPolicy.h"
#include "Set.h"

namespace Cache {
    class Cache {
    private:
        EvictionPolicy policy;
        size_t numSets;
        size_t linesPerSet;
        size_t tagBits;
        size_t bBits;
        std::vector<Set> sets;
    public:
        Cache(size_t numSets, size_t linesPerSet, size_t bBits, size_t tagBits, EvictionPolicy policy);
        ~Cache();
        static uint32_t setFromAddr(uint32_t addr, size_t bBits, size_t tagBits);
        static uint32_t tagFromAddr(uint32_t addr, size_t tagBits);
        CacheInsertResult insert(uint32_t addr);
        bool contains(uint32_t tag);
        Set* getSet(unsigned int setNum);
        void markLineValid(unsigned int setNum, unsigned int lineNum);
    };
}

#endif //CACHESIMULATOR_CACHE_H
