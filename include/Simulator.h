//
// Created by Joshua Kahn on 12/14/16.
//

#ifndef CACHESIMULATOR_SIMULATOR_H
#define CACHESIMULATOR_SIMULATOR_H

#include "Cache.h"
#include "EvictionPolicy.h"

namespace Cache {
    class Simulator {
    private:
        Cache *cache;
        size_t bBits;
        size_t tagBits;
        size_t numSets;
        size_t linesPerSet;
        EvictionPolicy evictionPolicy;
    public:
        Simulator(const char* input);
        ~Simulator();
    };
}

#endif //CACHESIMULATOR_SIMULATOR_H
