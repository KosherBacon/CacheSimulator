#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/simulator.h"

void simulate()
{
    uint32_t i, j;
    Simulator sim;
    sim.data_a_rows = 256;
    sim.data_a_cols = 256;
    sim.data_b_rows = 256;
    sim.data_b_cols = 256;
    sim.data_c_rows = 256;
    sim.data_c_cols = 256;
    sim.i_max = 256;
    sim.i_jump = 1;
    sim.j_max = 256;
    sim.j_jump = 1;
    sim.k_max = 256;
    sim.k_jump = 1;
    sim.a_base_addr = 0xAAAA0000;
    sim.b_base_addr = 0xBBBB0000;
    sim.c_base_addr = 0xCCCC0000;
    sim.elem_size = sizeof(uint32_t);
    sim.cache.num_sets = 1024;
    sim.cache.lines_per_set = 4;
    sim.cache.tag_bits = 19;
    sim.cache.b_bits = 3;
    sim.cache.policy = LRU;
    sim.cache.sets = (Set*) malloc(sim.cache.num_sets * sizeof(Set));
    for (i = 0; i < sim.cache.num_sets; i++)
    {
        sim.cache.sets[i].lines = (Line*) malloc(sim.cache.lines_per_set * sizeof(Line));
        sim.cache.sets[i].line_order = new std::deque<PolicyCount>();
        for (j = 0; j < sim.cache.lines_per_set; j++)
        {
            sim.cache.sets[i].lines[j].valid = false;
            sim.cache.sets[i].lines[j].tag = 0;
        }
    }
    run_simulator(&sim);
    for (i = 0; i < sim.cache.num_sets; i++)
    {
        delete sim.cache.sets[i].line_order;
        free(sim.cache.sets[i].lines);
    }
    free(sim.cache.sets);
}

int main(int argc, char* argv[])
{
    simulate();
    return EXIT_SUCCESS;
}

