//
// Created by Joshua Kahn on 12/7/16.
//

#include "../include/Cache.h"

uint32_t Cache::Cache::setFromAddr(uint32_t addr, size_t bBits, size_t tagBits) {
    if (bBits + tagBits >= 32) {
        return 0;
    }
    return ((addr << tagBits) >> tagBits) >> bBits;
}

uint32_t Cache::Cache::tagFromAddr(uint32_t addr, size_t tagBits) {
    if (tagBits >= 32) {
        return 0;
    }
    return addr >> (32 - tagBits);
}
