//
// Created by Joshua Kahn on 12/14/16.
//

#include <cassert>
#include "../include/Simulator.h"
#include "rapidjson/document.h"

Cache::Simulator::Simulator(const char* input) {
    if (input == nullptr) {
        // TODO - Return error message.
    }

    rapidjson::Document doc;
    doc.Parse(input);

    if (doc.HasParseError()) {
        // TODO - Return error message.
    }

    if ((!doc.HasMember("S") || !doc["S"].IsInt())
        || (!doc.HasMember("b") || !doc["b"].IsInt())
        || (!doc.HasMember("E") || !doc["E"].IsInt())) {
        // TODO - Return error message.
    }


}

Cache::Simulator::~Simulator() {
    delete this->cache;
}
