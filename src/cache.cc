#include <stdint.h>
#include <stdlib.h>

#include "../include/cache.h"

// Method implementations.

void cache_insert(Cache* cache, size_t set, uint32_t tag)
{
    // Assuming direct-mapped cache for now.
    // TODO - Implement LRU and LFU.
    (cache->sets[set]).lines[0].valid = true;
    (cache->sets[set]).lines[0].tag = tag;
}

