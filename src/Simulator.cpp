//
// Created by Joshua Kahn on 12/14/16.
//

#include <cassert>
#include <cmath>
#include <stdexcept>
#include "../include/Simulator.h"
#include "rapidjson/document.h"

#define ADDR_SIZE 32

Cache::Simulator::Simulator(const char& input) {
    rapidjson::Document doc;
    doc.Parse(&input);

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
                dataStruct["name"].GetStringLength() == 0)
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
        DataStructure ds = {.baseAddr=base, .rows=rows, .cols = cols};
        this->dataStructures[name] = ds;
    }
}

Cache::Simulator::~Simulator() {
    delete this->cache;
    this->dataStructures.clear();
}
