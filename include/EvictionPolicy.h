//
// Created by Joshua Kahn on 12/9/16.
//

#ifndef CACHESIMULATOR_EJECTIONPOLICY_H
#define CACHESIMULATOR_EJECTIONPOLICY_H

namespace Cache {
    enum EvictionPolicy {
        LRU,
        LFU,
        RANDOM
    };
}

#endif //CACHESIMULATOR_EJECTIONPOLICY_H
