//
// Created by Joshua Kahn on 1/17/17.
//

#ifndef CACHESIMULATOR_DATA_H
#define CACHESIMULATOR_DATA_H

#include <cstddef>
#include <cstdint>

namespace Cache {
    typedef struct DataStructure {
        uint32_t baseAddr;
        size_t rows;
        size_t cols;
    } DataStructure;
}

#endif //CACHESIMULATOR_DATA_H
