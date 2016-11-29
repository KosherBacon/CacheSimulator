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

// Method prototypes.

static inline bool cache_contains(Cache *cache, uint32_t tag, uint32_t set_id);
static void calculate_cache_lines(Simulator* sim, std::stringstream* os, int i, int j, int k);
static inline uint32_t set_from_addr(uint32_t addr, size_t b_bits, size_t tag_bits);
static inline uint32_t tag_from_addr(size_t elem_size, uint32_t addr, size_t tag_bits);

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

static void calculate_cache_lines(Simulator* sim, std::stringstream* os, int i, int j, int k)
{
    int dest_line;
    bool inserted;
    uint32_t a_addr, b_addr, c_addr;
    uint32_t set_a, set_b, set_c;
    uint32_t tag_a, tag_b, tag_c;
    inserted = false;
    a_addr = sim->a_base_addr
        + (i * sim->data_a_cols * sim->elem_size)
        + (k * sim->elem_size);
    tag_a = tag_from_addr(sim->elem_size, a_addr, sim->cache.tag_bits);
    set_a = set_from_addr(a_addr, sim->cache.b_bits, sim->cache.tag_bits);
    if (!cache_contains(&sim->cache, tag_a, set_a))
    {
        dest_line = cache_insert(&sim->cache, set_a, tag_a);
        *os << set_a << "," << dest_line << "," << "1" << "," << tag_a << "\n";
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
        *os << set_b << "," << dest_line << "," << "2" << "," << tag_b << "\n";
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
        *os << set_c << "," << dest_line << "," << "3" << "," << tag_c << "\n";
        inserted = true;
    }
    if (inserted)
    {
        *os << "\n";
    }

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

void allocate_simulator_data(Simulator* sim)
{
    uint32_t i, j;
    // Allocate space for cache sets.
    sim->cache.sets = (Set*) malloc(sim->cache.num_sets * sizeof(Set));
    // Initialize each cache set with appropriate number of cache lines.
    for (i = 0; i < sim->cache.num_sets; i++)
    {
        sim->cache.sets[i].lines = (Line*) malloc(sim->cache.lines_per_set * sizeof(Line));
        sim->cache.sets[i].line_order = new std::deque<PolicyCount>();
        // Initialize each cache line.
        for (j = 0; j < sim->cache.lines_per_set; j++)
        {
            sim->cache.sets[i].lines[j].valid = false;
            sim->cache.sets[i].lines[j].tag = 0;
        }
    }
}

void destroy_simulator(Simulator* sim)
{
    uint32_t i;
    free(sim->loops);
    for (i = 0; i < sim->cache.num_sets; i++)
    {
        delete sim->cache.sets[i].line_order;
        free(sim->cache.sets[i].lines);
    }
    free(sim->cache.sets);
    free(sim);
}

void loop_helper(Simulator* sim, std::stringstream* os, int* indices, int level)
{
    if (level == 0)
    {
        calculate_cache_lines(sim, os, indices[0], indices[1], indices[2]);
    }
    else
    {
        indices[level - 1] = 0;
        for (indices[level - 1] = 0; indices[level - 1] < sim->loops[level - 1].max; indices[level - 1]+=sim->loops[level - 1].jump)
        {
            loop_helper(sim, os, indices, level - 1);
        }
    }
}

std::string run_simulator(Simulator* sim)
{
    // TODO - Avoid assumption of standard matrix matrix multiply.
    // C[i][k] += A[i][k] * B[k][j]
    std::stringstream output_stream;
    int indices[] = {0, 0, 0};
    loop_helper(sim, &output_stream, indices, sim->num_loops);
    return output_stream.str();
}

