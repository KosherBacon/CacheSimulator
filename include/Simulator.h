//
// Created by Joshua Kahn on 12/14/16.
//

#ifndef CACHESIMULATOR_SIMULATOR_H
#define CACHESIMULATOR_SIMULATOR_H

#include "Cache.h"

namespace Cache {
    class Simulator {
    private:
        Cache *cache;
    public:
        Simulator(const char* input);
        ~Simulator();
    };
}

#endif //CACHESIMULATOR_SIMULATOR_H
