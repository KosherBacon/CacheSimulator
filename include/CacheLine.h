//
// Created by Joshua Kahn on 12/9/16.
//

#ifndef CACHESIMULATOR_CACHELINE_H
#define CACHESIMULATOR_CACHELINE_H

#include <cstdint>

namespace Cache {
    typedef struct CacheLine {
        bool valid;
        uint32_t tag;
        uint32_t evictionData;

        friend bool operator==(const CacheLine &lhs, const CacheLine &rhs) {
            return lhs.valid == rhs.valid && lhs.tag == rhs.tag && lhs.evictionData == rhs.evictionData;
        }
    } CacheLine;
}

#endif //CACHESIMULATOR_CACHELINE_H
