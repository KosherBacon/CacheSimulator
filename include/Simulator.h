//
// Created by Joshua Kahn on 12/14/16.
//

#ifndef CACHESIMULATOR_SIMULATOR_H
#define CACHESIMULATOR_SIMULATOR_H

#include <map>
#include <string>
#include "Cache.h"
#include "DataStructure.h"
#include "Loop.h"

namespace Cache {
    class Simulator {
    private:
        Cache *cache;
        std::map<char, DataStructure> dataStructures;
        std::map<char, Loop> loops;
        char lhs;
        char *rhs;
    public:
        Simulator(const std::string& input);
        ~Simulator();
    };
}

#endif //CACHESIMULATOR_SIMULATOR_H
