#include <iostream>

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/loop.h"
#include "../include/simulator.h"
#include "../include/rapidjson/document.h"

using namespace std;

// Method prototyes.

Simulator* parse_input(const char* input);
Simulator* prepare_input(const char* input);

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
    sim->cache.num_sets = (size_t) doc["S"].GetInt(); // S
    sim->cache.b_bits = (size_t) doc["b"].GetInt(); // b
    sim->cache.lines_per_set = doc["E"].GetInt(); // E

    // Check for m as a variable, if present use its value, else default to sizeof(uint32_t).
    sim->addr_size = (doc.HasMember("m") && doc["m"].IsInt() && doc["m"].GetInt() > 0) ? (size_t) doc["m"].GetInt()
                                                                                       : sizeof(uint32_t);

    replacement_policy = doc["replacement"].GetString(); // Replacement policy
    sim->elem_size = sizeof(uint32_t);
    sim->cache.tag_bits = sim->addr_size - sim->cache.b_bits - (int) (log2((double) sim->cache.num_sets) + 0.5);
    if (strcmp(replacement_policy, "LRU") == 0)
    {
        sim->cache.policy = LRU;
    }
    else if (strcmp(replacement_policy, "LFU") == 0)
    {
        sim->cache.policy = LFU;
    }
    else if (strcmp(replacement_policy, "RANDOM") == 0)
    {
        sim->cache.policy = RANDOM;
    }
    else if (strcmp(replacement_policy, "DIRECT_MAP") == 0)
    {
        sim->cache.policy = DIRECT_MAP;
    }
    else
    {
        // TODO - ERROR.
    }
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
                sim->data_a_rows = (size_t) data_struct["rows"].GetInt();
                sim->data_a_cols = (size_t) data_struct["cols"].GetInt();
                break;
            case 'B':
                sim->data_b_rows = (size_t) data_struct["rows"].GetInt();
                sim->data_b_cols = (size_t) data_struct["cols"].GetInt();
                break;
            case 'C':
                sim->data_c_rows = (size_t) data_struct["rows"].GetInt();
                sim->data_c_cols = (size_t) data_struct["cols"].GetInt();
                break;
            default:
                break;
        }
    }

    // Parse loop block.
    const rapidjson::Value& loops = doc["loops"];
    sim->num_loops = loops.Size();
    sim->loops = new Loop[sim->num_loops];
    for (i = 0; i < sim->num_loops; i++)
    {
        const rapidjson::Value& loop = loops[i];
        if (!loop.HasMember("idx") || !loop.HasMember("step") || !loop.HasMember("limit"))
        {
            // TODO - ERROR.
        }
        sim->loops[i].name = loop["idx"].GetString()[0];
        sim->loops[i].jump = loop["step"].GetInt();
        sim->loops[i].max = loop["limit"].GetInt();
    }
    sim->a_base_addr = 0xAAAA0000;
    sim->b_base_addr = 0xBBBB0000;
    sim->c_base_addr = 0xCCCC0000;

    // Parse computation block.
    const rapidjson::Value& computation = doc["computation"];
    const rapidjson::Value& LHS = computation["LHS"];
    sim->lhs.name = LHS["name"].GetString()[0];
    sim->lhs.num_indices = LHS["idx"].Size();
    if (sim->lhs.num_indices >= 1)
    {
        sim->lhs.first_index = LHS["idx"][0].GetString()[0];
    }
    if (sim->lhs.num_indices >= 2)
    {
        sim->lhs.second_index = LHS["idx"][0].GetString()[0];
    }
    const rapidjson::Value& RHS = computation["RHS"];
    sim->num_rhs = RHS.Size();
    sim->rhs = new Data[sim->num_rhs];
    for (i = 0; i < sim->num_rhs; i++)
    {
        sim->rhs[i].name = RHS[i]["name"].GetString()[0];
        sim->rhs[i].num_indices = RHS[i]["idx"].Size();
        if (sim->rhs[i].num_indices >= 1)
        {
            sim->rhs[i].first_index = LHS["idx"][0].GetString()[0];
        }
        if (sim->rhs[i].num_indices >= 2)
        {
            sim->rhs[i].second_index = LHS["idx"][0].GetString()[0];
        }
    }
    return sim;
}

Simulator* prepare_input(const char* input)
{
    Simulator* sim;
    sim = parse_input(input);
    allocate_simulator_data(sim);
    return sim;
}

int main(int argc, char* argv[])
{
    Simulator *sim;
    int i;
    char *buf, nextchar;

    buf = new char[2048];

    i = 0;
    while (scanf("%c", &nextchar) > 0) {
        buf[i] = nextchar;
        if (nextchar == '\0')
            break;
        i++;
    }
        
    sim = prepare_input(buf);
    std::cout << run_simulator(sim) << std::endl;
    delete buf;
    destroy_simulator(sim);
    return EXIT_SUCCESS;
}

