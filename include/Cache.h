//
// Created by Joshua Kahn on 12/7/16.
//

#ifndef CACHESIMULATOR_CACHE_H
#define CACHESIMULATOR_CACHE_H

#include <cstdint>
#include <cstddef>

namespace Cache {
    class Cache {
    public:
        static uint32_t setFromAddr(uint32_t addr, size_t bBits, size_t tagBits);
        static uint32_t tagFromAddr(uint32_t addr, size_t tagBits);
    };
}

#endif //CACHESIMULATOR_CACHE_H
