//
// Created by Joshua Kahn on 12/7/16.
//

#ifndef CACHESIMULATOR_CACHE_H
#define CACHESIMULATOR_CACHE_H

#include <cstdint>
#include <cstddef>
#include <vector>
#include "EvictionPolicy.h"
#include "Set.h"

namespace Cache {
    class Cache {
    private:
        EvictionPolicy policy;
        size_t numSets;
        size_t linesPerSet;
        std::vector<Set> sets;
    public:
        Cache(size_t numSets, size_t linesPerSet, EvictionPolicy policy);
        ~Cache();
        static uint32_t setFromAddr(uint32_t addr, size_t bBits, size_t tagBits);
        static uint32_t tagFromAddr(uint32_t addr, size_t tagBits);
        void insert(size_t set, uint32_t tag);
        bool contains(uint32_t addr, uint32_t tag);
    };
}

#endif //CACHESIMULATOR_CACHE_H
