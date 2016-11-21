#include <iostream>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rapidjson/document.h"

#include "../include/simulator.h"

using namespace std;

// Method prototyes.

Simulator* parse_input(const char* input);
void simulate();

// Implementations.

Simulator* parse_input(const char* input)
{
    // TODO - Error handling.
    Simulator *sim;
    rapidjson::Document doc;
    const char* replacement_policy;
    rapidjson::SizeType i; // rapidjson uses SizeType, not size_t.

    // Allocate memory for Simulator struct.
    sim = (Simulator*) malloc(sizeof(Simulator));

    // Parse into JSON blob.
    doc.Parse(input);

    // Initialize values in Simulator struct from JSON blob.
    sim->cache.num_sets = doc["S"].GetInt(); // S
    sim->cache.b_bits = doc["b"].GetInt(); // b
    sim->cache.lines_per_set = doc["E"].GetInt(); // E
    replacement_policy = doc["replacement"].GetString(); // Replacement policy
    if (strcmp(replacement_policy, "LRU"))
    {
        sim->cache.policy = LRU;
    }
    else if (strcmp(replacement_policy, "LFU"))
    {
        sim->cache.policy = LFU;
    }
    else if (strcmp(replacement_policy, "RANDOM"))
    {
        sim->cache.policy = RANDOM;
    }
    else if (strcmp(replacement_policy, "DIRECT_MAP"))
    {
    }
    else
    {
        // TODO - ERROR.
    }
    // Check for m as a variable, if present use its value, else default to sizeof(uint32_t).
    sim->addr_size = (doc.HasMember("m") && doc["m"].IsInt() && doc["m"].GetInt() > 0) ? doc["m"].GetInt() : sizeof(uint32_t);

    // Parse data structure block.
    const rapidjson::Value& data = doc["data"];
    for (i = 0; i < data.Size(); i++)
    {
        const rapidjson::Value& data_struct = data[i];
        if (!data_struct.HasMember("name") || !data_struct.HasMember("rows")
                || !data_struct.HasMember("rows") || !data_struct.HasMember("cols"))
        {
            // TODO - ERROR.
        }
        switch (data_struct["name"].GetString()[0])
        {
            case 'A':
                sim->data_a_rows = data_struct["rows"].GetInt();
                sim->data_a_cols = data_struct["cols"].GetInt();
                break;
            case 'B':
                sim->data_b_rows = data_struct["rows"].GetInt();
                sim->data_b_cols = data_struct["cols"].GetInt();
                break;
            case 'C':
                sim->data_c_rows = data_struct["rows"].GetInt();
                sim->data_c_cols = data_struct["cols"].GetInt();
                break;
        }
    }

    // Parse loop block.
    const rapidjson::Value& loops = doc["loops"];
    for (i = 0; i < loops.Size(); i++)
    {
        const rapidjson::Value& loop = loops[i];
        if (!loop.HasMember("idx") || !loop.HasMember("step") || !loop.HasMember("limit"))
        {
            // TODO - ERROR.
        }
        switch (loop["idx"].GetString()[0])
        {
            case 'i':
                sim->i_jump = loop["step"].GetInt();
                sim->i_max = loop["limit"].GetInt();
                break;
            case 'j':
                sim->j_jump = loop["step"].GetInt();
                sim->j_max = loop["limit"].GetInt();
                break;
            case 'k':
                sim->k_jump = loop["step"].GetInt();
                sim->k_max = loop["limit"].GetInt();
                break;
        }
    }

    return sim;
}

void simulate()
{
    uint32_t i, j;
    Simulator sim;
    sim.data_a_rows = 4;
    sim.data_a_cols = 4;
    sim.data_b_rows = 4;
    sim.data_b_cols = 4;
    sim.data_c_rows = 4;
    sim.data_c_cols = 4;
    sim.i_max = 4;
    sim.i_jump = 1;
    sim.j_max = 4;
    sim.j_jump = 1;
    sim.k_max = 4;
    sim.k_jump = 1;
    sim.a_base_addr = 0xAAAA0000;
    sim.b_base_addr = 0xBBBB0000;
    sim.c_base_addr = 0xCCCC0000;
    sim.elem_size = sizeof(uint32_t);
    sim.cache.num_sets = 256;
    sim.cache.lines_per_set = 1;
    sim.cache.tag_bits = 22;
    sim.cache.b_bits = 2;
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
    std::cout << run_simulator(&sim) << std::endl;
    for (i = 0; i < sim.cache.num_sets; i++)
    {
        delete sim.cache.sets[i].line_order;
        free(sim.cache.sets[i].lines);
    }
    free(sim.cache.sets);
}

int main(int argc, char* argv[])
{
    Simulator *sim;
    sim = parse_input(
            "{\n"
            "      \"S\": 8,\n"
            "      \"b\": 3,\n"
            "      \"E\": 8,\n"
            "      \"m\": 32,\n"
            "      \"replacement\": \"LRU\",\n"
            "      \"cache-writes\": true,\n"
            "      \"data\": [\n"
            "            { \"name\": \"A\", \"color\": \"green\", \"rows\": 4, \"cols\": 4, \"wordsize\": 32 },\n"
            "            { \"name\": \"B\", \"color\": \"purple\", \"rows\": 6, \"cols\": 1, \"wordsize\": 64 }\n"
            "      ],\n"
            "      \"loops\": [\n"
            "            { \"idx\": \"i\", \"step\": 1, \"limit\": 6 },\n"
            "            { \"idx\": \"j\", \"step\": 2, \"limit\": 4 }\n"
            "      ],\n"
            "      \"computation\": \"A[j] = A[j] + B[j]\"\n"
            "}"
            );
    //simulate();
    free(sim);
    return EXIT_SUCCESS;
}

