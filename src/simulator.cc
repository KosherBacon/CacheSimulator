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
static void calculate_cache_lines(Simulator* sim, std::stringstream* os, int first, int second, int third);
static inline int get_index(int idx, int first, int second, int third);
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

static inline void calculate_cache_lines(Simulator* sim, std::stringstream* os, int first, int second, int third)
{
    int dest_line;
    bool inserted;
    size_t cols;
    char index;
    int i, idx1, idx2, color;
    uint32_t addr, base_addr, tag, set;
    Data *lhs;
    Data *rhs;
    inserted = false;

    // Handle LHS.
    lhs = &sim->lhs;
    if (lhs->name == 'A')
    {
        base_addr = sim->a_base_addr;
        color = 1;
        cols = sim->data_a_cols;
    }
    else if (lhs->name == 'B')
    {
        base_addr = sim->b_base_addr;
        color = 2;
        cols = sim->data_b_cols;
    }
    else if (lhs->name == 'C')
    {
        base_addr = sim->c_base_addr;
        color = 3;
        cols = sim->data_c_cols;
    }
    else
    {
        // TODO - ERROR.
        color = 0;
        base_addr = 0;
        cols = 0;
    }
    if (lhs->num_indices == 1)
    {
        index = lhs->first_index;
        for (idx1 = 0; idx1 < sim->num_loops; idx1++)
        {
            if (index == sim->loops[idx1].name)
            {
                break;
            }
        }
        addr = (uint32_t) (base_addr + get_index(idx1, first, second, third) * sim->elem_size);
        tag = tag_from_addr(sim->elem_size, addr, sim->cache.tag_bits);
        set = set_from_addr(addr, sim->cache.b_bits, sim->cache.tag_bits);
        if (!cache_contains(&sim->cache, tag, set))
        {
            dest_line = cache_insert(&sim->cache, set, tag);
            *os << set << "," << dest_line << "," << color << "," << tag << "$";
            inserted = true;
        }
    }
    else if (lhs->num_indices == 2)
    {
        index = lhs->first_index;
        for (idx1 = 0; idx1 < sim->num_loops; idx1++)
        {
            if (index == sim->loops[idx1].name)
            {
                break;
            }
        }
        index = lhs->second_index;
        for (idx2 = 0; idx2 < sim->num_loops; idx2++)
        {
            if (index == sim->loops[idx2].name)
            {
                break;
            }
        }
        addr = (uint32_t) (base_addr
                           + (get_index(idx1, first, second, third) * cols * sim->elem_size)
                           + (get_index(idx2, first, second, third) * sim->elem_size));
        tag = tag_from_addr(sim->elem_size, addr, sim->cache.tag_bits);
        set = set_from_addr(addr, sim->cache.b_bits, sim->cache.tag_bits);
        if (!cache_contains(&sim->cache, tag, set))
        {
            dest_line = cache_insert(&sim->cache, set, tag);
            *os << set << "," << dest_line << "," << color << "," << tag << "$";
            inserted = true;
        }
    }

    // Handle RHS.
    for (i = 0; i < sim->num_rhs; i++)
    {
        rhs = &sim->rhs[i];
        if (rhs->name == 'A')
        {
            base_addr = sim->a_base_addr;
            color = 1;
            cols = sim->data_a_cols;
        }
        else if (rhs->name == 'B')
        {
            base_addr = sim->b_base_addr;
            color = 2;
            cols = sim->data_b_cols;
        }
        else if (rhs->name == 'C')
        {
            base_addr = sim->c_base_addr;
            color = 3;
            cols = sim->data_c_cols;
        }
        else {
            // TODO - ERROR.
            color = 0;
            base_addr = 0;
            cols = 0;
        }
        if (rhs->num_indices == 1)
        {
            index = rhs->first_index;
            for (idx1 = 0; idx1 < sim->num_loops; idx1++)
            {
                if (index == sim->loops[idx1].name)
                {
                    break;
                }
            }
            addr = (uint32_t) (base_addr + get_index(idx1, first, second, third) * sim->elem_size);
            tag = tag_from_addr(sim->elem_size, addr, sim->cache.tag_bits);
            set = set_from_addr(addr, sim->cache.b_bits, sim->cache.tag_bits);
            if (!cache_contains(&sim->cache, tag, set))
            {
                printf("set: %i\n", set);
                dest_line = cache_insert(&sim->cache, set, tag);
                *os << set << "," << dest_line << "," << color << "," << tag << "$";
                inserted = true;
            }
        }
        else if (rhs->num_indices == 2)
        {
            index = rhs->first_index;
            for (idx1 = 0; idx1 < sim->num_loops; idx1++)
            {
                if (index == sim->loops[idx1].name)
                {
                    break;
                }
            }
            index = rhs->second_index;
            for (idx2 = 0; idx2 < sim->num_loops; idx2++)
            {
                if (index == sim->loops[idx2].name)
                {
                    break;
                }
            }
            addr = (uint32_t) (base_addr
                               + (get_index(idx1, first, second, third) * cols * sim->elem_size)
                               + (get_index(idx2, first, second, third) * sim->elem_size));
            tag = tag_from_addr(sim->elem_size, addr, sim->cache.tag_bits);
            set = set_from_addr(addr, sim->cache.b_bits, sim->cache.tag_bits);
            if (!cache_contains(&sim->cache, tag, set))
            {
                printf("set: %i\n", set);
                dest_line = cache_insert(&sim->cache, set, tag);
                *os << set << "," << dest_line << "," << color << "," << tag << "$";
                inserted = true;
            }
        }
    }
    if (inserted)
    {
        *os << "$";
    }
}

static inline int get_index(int idx, int first, int second, int third)
{
    if (idx == 0)
    {
        return first;
    }
    else if (idx == 1)
    {
        return second;
    }
    else if (idx == 2)
    {
        return third;
    }
    else
    {
        return -1;
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
    free(sim->rhs);
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
    std::string str;
    char *c_str;
    int idx, length;
    std::stringstream output_stream;
    int indices[] = {0, 0, 0};
    loop_helper(sim, &output_stream, indices, sim->num_loops);
    str = output_stream.str();
    c_str = new char[str.length() + 1];
    strcpy(c_str, str.c_str());
    length = (int) strlen(c_str);
    idx = length - 1;
    // Remove trailing separator characters.
    while (c_str[idx] == '$')
    {
        c_str[idx] = '\0';
        idx--;
    }
    str = string(c_str);
    delete c_str;
    return str;
}

