//
// Created by Joshua Kahn on 12/14/16.
//

#include <cassert>
#include <cmath>
#include <stdexcept>
#include <string>
#include "../include/Simulator.h"
#include "rapidjson/document.h"

#define ADDR_SIZE 32

Cache::Simulator::Simulator(const std::string& input) {
    rapidjson::Document doc;
    doc.Parse(input.c_str());

    if (doc.HasParseError()) {
        // TODO - Return error message.
        throw std::invalid_argument("Invalid JSON, cannot be parsed.");
    }

    if ((!doc.HasMember("S") || !doc["S"].IsInt() || doc["S"].GetInt() <= 0)
        || (!doc.HasMember("b") || !doc["b"].IsInt() || doc["b"].GetInt() <= 0)
        || (!doc.HasMember("E") || !doc["E"].IsInt() || doc["E"].GetInt() <= 0)) {
        // TODO - Return error message.
        throw std::invalid_argument("Missing or invalid parameters: E, b, E.");
    }

    if (!doc.HasMember("replacement") || !doc["replacement"].IsString()) {
        // TODO - Return error message.
        throw std::invalid_argument("Missing or invalid parameter: replacement.");
    }

    size_t numSets = (size_t) doc["S"].GetInt();
    size_t bBits = (size_t) doc["b"].GetInt();
    size_t linesPerSet = (size_t) doc["E"].GetInt();
    size_t tagBits = ADDR_SIZE - bBits - (unsigned int) (log2((double) numSets) + 0.5);
    const char* replacementPolicyStr;
    EvictionPolicy policy;
    replacementPolicyStr = doc["replacement"].GetString();

    if (strcmp(replacementPolicyStr, "LRU") == 0) {
        policy = LRU;
    } else if (strcmp(replacementPolicyStr, "LFU") == 0) {
        policy = LFU;
    } else {
        // TODO - Return error message.
        throw std::invalid_argument("Invalid replacement policy.");
    }

    // For now we can assume that the policy is valid.
    this->cache = new Cache(numSets, linesPerSet, bBits, tagBits, policy);

    if (!doc.HasMember("data") || !doc["data"].IsArray()) {
        // TODO - Return error message.
        throw std::invalid_argument("Missing or invalid parameter: data.");
    }

    const rapidjson::Value& data = doc["data"];
    for (rapidjson::SizeType i = 0; i < data.Size(); i++) {
        const rapidjson::Value& dataStruct = data[i];
        if ((!dataStruct.HasMember("name") || !dataStruct["name"].IsString() ||
                dataStruct["name"].GetStringLength() != 1)
            || (!dataStruct.HasMember("rows") || !dataStruct["rows"].IsInt() || dataStruct["rows"].GetInt() <= 0)
            || (!dataStruct.HasMember("cols") || !dataStruct["cols"].IsInt() || dataStruct["cols"].GetInt() <= 0)
            || (!dataStruct.HasMember("base") || !dataStruct["base"].IsInt64() || dataStruct["base"].GetInt64() < 0)) {
            // TODO - Return error message.
            throw std::invalid_argument("Missing or invalid parameters: name, rows, cols, base.");
        }
        const char name = dataStruct["name"].GetString()[0];
        size_t rows = (size_t) dataStruct["rows"].GetInt();
        size_t cols = (size_t) dataStruct["cols"].GetInt();
        uint32_t base = (uint32_t) dataStruct["base"].GetInt64();
        if (this->dataStructures.find(name) != this->dataStructures.end()) {
            throw std::invalid_argument("Duplicate name entries in parameter: data.");
        }
        DataStructure ds = {.baseAddr=base, .rows=rows, .cols = cols};
        this->dataStructures[name] = ds;
    }

    if (!doc.HasMember("loops") || !doc["loops"].IsArray()) {
        // TODO - Return error message.
        throw std::invalid_argument("Missing or invalid parameter: loops.");
    }

    const rapidjson::Value& loops = doc["loops"];
    int loopsSize = loops.Size();
    for (int i = 0; i < loopsSize; i++) {
        const rapidjson::Value& loop = loops[i];
        if ((!loop.HasMember("idx") || !loop["idx"].IsString() || loop["idx"].GetStringLength() != 1)
            || (!loop.HasMember("step") || !loop["step"].IsInt() || loop["step"].GetInt() <= 0)
            || (!loop.HasMember("limit") || !loop["limit"].IsInt() || loop["limit"].GetInt() <= 0)) {
            throw std::invalid_argument("Missing or invalid parameters: idx, step, limit.");
        }
        const char idx = loop["idx"].GetString()[0];
        size_t step = (size_t) loop["step"].GetInt();
        size_t limit = (size_t) loop["limit"].GetInt();
        if (this->loops.find(idx) != this->loops.end()) {
            throw std::invalid_argument("Duplicate idx entries in parameter: loops.");
        }
        Loop loopStruct = {.step=step, .limit=limit};
        this->loops[idx] = loopStruct;
    }

    if (!doc.HasMember("computation") || !doc["computation"].IsObject()) {
        throw std::invalid_argument("Missing or invalid parameter: computation.");
    }

    const rapidjson::Value& computation = doc["computation"];
    if (!computation.HasMember("LHS") || !computation["LHS"].IsString() || computation["LHS"].GetStringLength() != 1
            || !computation.HasMember("RHS") || !computation["RHS"].IsArray()) {
        throw std::invalid_argument("Missing or invalid parameters: LHS, RHS.");
    }
    const rapidjson::Value& lhs = computation["LHS"];
    const char lhsStructure = lhs.GetString()[0];
    if (this->dataStructures.find(lhsStructure) == this->dataStructures.end()) {
        // The lhs data structure wasn't previously defined.
        throw std::invalid_argument("Data structure in LHS was not previously defined.");
    }
    this->lhs = lhsStructure; // Actually set the lhs structure after checking the input format.

    const rapidjson::Value& rhs = computation["RHS"];
    int rhsSize = rhs.GetArray().Size();
    this->rhs = new char[rhsSize];
    for (int i = 0; i < rhsSize; i++) {
        if (!rhs[i].IsString() || rhs[i].GetStringLength() != 1) {
            // Error out that the data input is of the wrong type.
            throw std::invalid_argument("Malformed entry in RHS, expecting strings of length 1.");
        }
        const char rhsStructure = rhs[i].GetString()[0];
        if (this->dataStructures.find(rhsStructure) == this->dataStructures.end()) {
            // The rhs data structure wasn't previously defined.
            throw std::invalid_argument("Data structure in RHS was not previously defined.");
        }
        this->rhs[i] = rhsStructure;
    }
}

Cache::Simulator::~Simulator() {
    delete this->cache;
    this->dataStructures.clear();
    delete this->rhs;
}

void Cache::Simulator::simulate() {
    
}
