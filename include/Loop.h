//
// Created by Joshua Kahn on 1/20/17.
//

#ifndef CACHESIMULATOR_LOOP_H
#define CACHESIMULATOR_LOOP_H

#include <cstddef>

namespace Cache {
    typedef struct Loop {
        size_t step;
        size_t limit;
    } Loop;
}

#endif //CACHESIMULATOR_LOOP_H
