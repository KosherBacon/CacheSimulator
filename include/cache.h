#ifndef CACHE_H
#define CACHE_H

#include <deque>

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// Forward declare typedefs and methods.
typedef struct Cache Cache;
typedef struct PolicyCount PolicyCount;
typedef struct Set Set;
typedef struct Line Line;

typedef enum EvictionPolicy {
    DIRECT_MAP,
    LRU,
    LFU,
    RANDOM
} EvictionPolicy;

int cache_insert(Cache *cache, size_t set, uint32_t tag);

// Struct implementations.

struct Cache {
    size_t num_sets; // Number of sets.
    int lines_per_set; // The number of lines in a set.
    size_t tag_bits; // Number of bits to use in the tag.
    size_t b_bits; // Number of bits needed to index bytes in line.
    Set* sets;
    EvictionPolicy policy;
};

struct PolicyCount {
    int line;
    int value;

    bool operator < (const PolicyCount& p) const
    {
        return value < p.value;
    }
};

struct Set {
    Line* lines;
    std::deque<PolicyCount>* line_order;
};

struct Line {
    bool valid;
    uint32_t tag;
};

#endif
