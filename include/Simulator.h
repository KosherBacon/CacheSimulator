//
// Created by Joshua Kahn on 12/14/16.
//

#ifndef CACHESIMULATOR_SIMULATOR_H
#define CACHESIMULATOR_SIMULATOR_H

#include <map>
#include "Cache.h"
#include "DataStructure.h"

namespace Cache {
    class Simulator {
    private:
        Cache *cache;
        std::map<char, DataStructure> dataStructures;
    public:
        Simulator(const char& input);
        ~Simulator();
    };
}

#endif //CACHESIMULATOR_SIMULATOR_H
