//
// Created by Joshua Kahn on 12/14/16.
//

#ifndef CACHESIMULATOR_SIMULATOR_H
#define CACHESIMULATOR_SIMULATOR_H

#include <map>
#include <string>
#include <sstream>
#include "Cache.h"
#include "DataStructure.h"
#include "Loop.h"

namespace Cache {
    class Simulator {
    private:
        Cache *cache;
        std::map<char, DataStructure> dataStructures;
        std::vector<Loop> loops;
        char lhs;
        char *rhs;
        int rhsSize;
        void calculateCacheLines(std::stringstream* os);
        void loopHelper(std::stringstream* os, int* indices, int level);
    public:
        Simulator(const std::string& input);
        ~Simulator();
        void simulate();
    };
}

#endif //CACHESIMULATOR_SIMULATOR_H
