#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../include/simulator.h"

using namespace std;

// Static methods (private except for this file).

static inline bool cache_contains(Cache *cache, uint32_t tag, uint32_t set_id)
{
    register int i;
    Line* line;
    for (i = 0; i < cache->lines_per_set; i++)
    {
        line = &(cache->sets[set_id]).lines[i];
        if (!line->valid)
        {
            continue;
        }
        if (line->tag == tag)
        {
            return true;
        }
    }
    return false;
}

static inline uint32_t set_from_addr(uint32_t addr, size_t b_bits, size_t tag_bits)
{
    return ((addr << tag_bits) >> tag_bits) >> b_bits;
}

static inline uint32_t tag_from_addr(size_t elem_size, uint32_t addr, size_t tag_bits)
{
    // Keeps tag_bits number of bits in the lower bits of a uint32_t.
    return addr >> (elem_size - tag_bits);
}

// Method implementations for simulator.h.

std::string run_simulator(Simulator* sim)
{
    // TODO - Avoid assumption of standard matrix matrix multiply.
    // C[i][k] += A[i][k] * B[k][j]
    std::stringstream output_stream;
    register int i, j, k;
    int dest_line;
    bool inserted;
    uint32_t a_addr, b_addr, c_addr;
    uint32_t set_a, set_b, set_c;
    uint32_t tag_a, tag_b, tag_c;
    for (i = 0; i < sim->i_max; i+=sim->i_jump)
    {
        for (j = 0; j < sim->j_max; j+=sim->j_jump)
        {
            for (k = 0; k < sim->k_max; k+=sim->k_jump)
            {
                inserted = false;
                a_addr = sim->a_base_addr
                    + (i * sim->data_a_cols * sim->elem_size)
                    + (k * sim->elem_size);
                tag_a = tag_from_addr(sim->elem_size, a_addr, sim->cache.tag_bits);
                set_a = set_from_addr(a_addr, sim->cache.b_bits, sim->cache.tag_bits);
                if (!cache_contains(&sim->cache, tag_a, set_a))
                {
                    dest_line = cache_insert(&sim->cache, set_a, tag_a);
                    output_stream << set_a << "," << dest_line << "," << tag_a << "," << "r" << "\n";
                    inserted = true;
                }
                b_addr = sim->b_base_addr
                    + (k * sim->data_b_cols * sim->elem_size)
                    + (j * sim->elem_size);
                tag_b = tag_from_addr(sim->elem_size, b_addr, sim->cache.tag_bits);
                set_b = set_from_addr(b_addr, sim->cache.b_bits, sim->cache.tag_bits);
                if (!cache_contains(&sim->cache, tag_b, set_b))
                {
                    dest_line = cache_insert(&sim->cache, set_b, tag_b);
                    output_stream << set_b << "," << dest_line << "," << tag_b << "," << "g" << "\n";
                    inserted = true;
                }
                c_addr = sim->c_base_addr
                    + (i * sim->data_c_cols * sim->elem_size)
                    + (k * sim->elem_size);
                tag_c = tag_from_addr(sim->elem_size, c_addr, sim->cache.tag_bits);
                set_c = set_from_addr(c_addr, sim->cache.b_bits, sim->cache.tag_bits);
                if (!cache_contains(&sim->cache, tag_c, set_c))
                {
                    dest_line = cache_insert(&sim->cache, set_c, tag_c);
                    output_stream << set_c << "," << dest_line << "," << tag_c << "," << "b" << "\n";
                    inserted = true;
                }
                if (inserted)
                {
                    output_stream << "\n";
                }
            }
        }
    }
    return output_stream.str();
}

