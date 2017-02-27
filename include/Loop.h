//
// Created by Joshua Kahn on 1/20/17.
//

#ifndef CACHESIMULATOR_LOOP_H
#define CACHESIMULATOR_LOOP_H

#include <cstddef>

namespace Cache {
    typedef struct Loop {
        char index;
        size_t step;
        size_t limit;

        friend bool operator==(const Loop& l1, const Loop& l2) {
            return l1.index == l2.index;
        }
    } Loop;
}

#endif //CACHESIMULATOR_LOOP_H
