//
// Created by Joshua Kahn on 12/14/16.
//

#include <cassert>
#include "../include/Simulator.h"

Cache::Simulator::Simulator(const char* input) {
    assert(input != nullptr);
}

Cache::Simulator::~Simulator() {
    delete this->cache;
}
