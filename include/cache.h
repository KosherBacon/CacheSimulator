#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// Forward declare typedefs and methods.
typedef struct Cache Cache;
typedef struct Set Set;
typedef struct Line Line;

void cache_insert(Cache *cache, size_t set, uint32_t tag);

// Struct implementations.

struct Cache {
    size_t num_sets; // Number of sets.
    size_t lines_per_set; // The number of lines in a set.
    size_t tag_bits; // Number of bits to use in the tag.
    size_t b_bits; // Number of bits needed to index bytes in line.
    Set* sets;
};

struct Set{
    Line* lines;
};

struct Line {
    bool valid;
    uint32_t tag;
    uint8_t eviction_bits; // 8 bits, 2^8 = 256, max of 256 lines per set.
};

