//
// Created by Joshua Kahn on 1/18/17.
//

#include "../include/Cache.h"
#include "../include/Simulator.h"
#include "gtest/gtest.h"

// Simulator constructor

TEST(simulatorConstructor, validConfigString) {
    const char &input = (const char &) "{\n"
                "      \"S\": 8,\n"
                "      \"b\": 3,\n"
                "      \"E\": 8,\n"
                "      \"m\": 32,\n"
                "      \"replacement\": \"LRU\",\n"
                "      \"cache-writes\": true,\n"
                "      \"data\": [\n"
                "            { \"name\": \"A\", \"rows\": 4, \"cols\": 4, \"base\": 2863311530 },\n"
                "            { \"name\": \"B\", \"rows\": 6, \"cols\": 1, \"base\": 3149642683 }\n"
                "      ],\n"
                "      \"loops\": [\n"
                "            { \"idx\": \"i\", \"step\": 1, \"limit\": 6 },\n"
                "            { \"idk\": \"j\", \"step\": 2, \"limit\": 4 }\n"
                "      ],\n"
                "      \"computation\": {\"LHS\": \"C\", \"RHS\": [\"A\", \"B\"]}\n"
                "}";
    EXPECT_NO_THROW({Cache::Simulator sim = Cache::Simulator(input);});
}