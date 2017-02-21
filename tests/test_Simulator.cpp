//
// Created by Joshua Kahn on 1/18/17.
//

#include "../include/Cache.h"
#include "../include/Simulator.h"
#include "gtest/gtest.h"

// Simulator constructor

TEST(simulatorConstructor, validConfigString) {
    const std::string input = "{\n"
                "      \"S\": 8,\n"
                "      \"b\": 3,\n"
                "      \"E\": 8,\n"
                "      \"m\": 32,\n"
                "      \"replacement\": \"LRU\",\n"
                "      \"cache-writes\": true,\n"
                "      \"data\": [\n"
                "            { \"name\": \"A\", \"rows\": 4, \"cols\": 4, \"base\": 2863311530 },\n"
                "            { \"name\": \"B\", \"rows\": 4, \"cols\": 4, \"base\": 3149642683 },\n"
                "            { \"name\": \"C\", \"rows\": 4, \"cols\": 4, \"base\": 6012954213 }\n"
                "      ],\n"
                "      \"loops\": [\n"
                "            { \"idx\": \"i\", \"step\": 1, \"limit\": 4 },\n"
                "            { \"idx\": \"j\", \"step\": 2, \"limit\": 4 }\n"
                "      ],\n"
                "      \"computation\": {\"LHS\": \"C\", \"RHS\": [\"A\", \"B\"]}\n"
                "}";
    EXPECT_NO_THROW({Cache::Simulator sim = Cache::Simulator(input);});
}

TEST(simulatorConstructor, invalidJSON) {
    const std::string input = "{\n"
            "      \"S\": 8\n"
            "      \"b\": 3\n"
            "      \"E\": 8\n"
            "      \"m\": 32\n"
            "      \"replacement\": \"LRU\",\n"
            "      \"cache-writes\": true,\n"
            "      \"data\": [\n"
            "            { \"name\": \"A\", \"rows\": 4, \"cols\": 4, \"base\": 2863311530 },\n"
            "            { \"name\": \"B\", \"rows\": 6, \"cols\": 1, \"base\": 3149642683 }\n"
            "      ],\n"
            "      \"loops\": [\n"
            "            { \"idx\": \"i\", \"step\": 1, \"limit\": 6 },\n"
            "            { \"idx\": \"j\", \"step\": 2, \"limit\": 4 }\n"
            "      ],\n"
            "      \"computation\": {\"LHS\": \"C\", \"RHS\": [\"A\", \"B\"]}\n"
            "}";
    EXPECT_ANY_THROW({Cache::Simulator sim = Cache::Simulator(input);});
}

TEST(simulatorConstructor, missingSbE) {
    const std::string input = "{\n"
            "      \"m\": 32,\n"
            "      \"replacement\": \"LRU\",\n"
            "      \"cache-writes\": true,\n"
            "      \"data\": [\n"
            "            { \"name\": \"A\", \"rows\": 4, \"cols\": 4, \"base\": 2863311530 },\n"
            "            { \"name\": \"B\", \"rows\": 6, \"cols\": 1, \"base\": 3149642683 }\n"
            "      ],\n"
            "      \"loops\": [\n"
            "            { \"idx\": \"i\", \"step\": 1, \"limit\": 6 },\n"
            "            { \"idx\": \"j\", \"step\": 2, \"limit\": 4 }\n"
            "      ],\n"
            "      \"computation\": {\"LHS\": \"C\", \"RHS\": [\"A\", \"B\"]}\n"
            "}";
    EXPECT_ANY_THROW({Cache::Simulator sim = Cache::Simulator(input);});
}

TEST(simulatorConstructor, invalidReplacementType) {
    const std::string input = "{\n"
            "      \"S\": 8,\n"
            "      \"b\": 3,\n"
            "      \"E\": 8,\n"
            "      \"m\": 32,\n"
            "      \"replacement\": 5,\n"
            "      \"cache-writes\": true,\n"
            "      \"data\": [\n"
            "            { \"name\": \"A\", \"rows\": 4, \"cols\": 4, \"base\": 2863311530 },\n"
            "            { \"name\": \"B\", \"rows\": 6, \"cols\": 1, \"base\": 3149642683 }\n"
            "      ],\n"
            "      \"loops\": [\n"
            "            { \"idx\": \"i\", \"step\": 1, \"limit\": 6 },\n"
            "            { \"idx\": \"j\", \"step\": 2, \"limit\": 4 }\n"
            "      ],\n"
            "      \"computation\": {\"LHS\": \"C\", \"RHS\": [\"A\", \"B\"]}\n"
            "}";
    EXPECT_ANY_THROW({Cache::Simulator sim = Cache::Simulator(input);});
}

TEST(simulatorConstructor, invalidReplacementString) {
    const std::string input = "{\n"
            "      \"S\": 8,\n"
            "      \"b\": 3,\n"
            "      \"E\": 8,\n"
            "      \"m\": 32,\n"
            "      \"replacement\": \"ABC\",\n"
            "      \"cache-writes\": true,\n"
            "      \"data\": [\n"
            "            { \"name\": \"A\", \"rows\": 4, \"cols\": 4, \"base\": 2863311530 },\n"
            "            { \"name\": \"B\", \"rows\": 6, \"cols\": 1, \"base\": 3149642683 }\n"
            "      ],\n"
            "      \"loops\": [\n"
            "            { \"idx\": \"i\", \"step\": 1, \"limit\": 6 },\n"
            "            { \"idx\": \"j\", \"step\": 2, \"limit\": 4 }\n"
            "      ],\n"
            "      \"computation\": {\"LHS\": \"C\", \"RHS\": [\"A\", \"B\"]}\n"
            "}";
    EXPECT_ANY_THROW({Cache::Simulator sim = Cache::Simulator(input);});
}

TEST(simulatorConstructor, missingDataArray) {
    const std::string input = "{\n"
            "      \"S\": 8,\n"
            "      \"b\": 3,\n"
            "      \"E\": 8,\n"
            "      \"m\": 32,\n"
            "      \"replacement\": \"LRU\",\n"
            "      \"cache-writes\": true,\n"
            "      \"loops\": [\n"
            "            { \"idx\": \"i\", \"step\": 1, \"limit\": 6 },\n"
            "            { \"idx\": \"j\", \"step\": 2, \"limit\": 4 }\n"
            "      ],\n"
            "      \"computation\": {\"LHS\": \"C\", \"RHS\": [\"A\", \"B\"]}\n"
            "}";
    EXPECT_ANY_THROW({Cache::Simulator sim = Cache::Simulator(input);});
}

TEST(simulatorConstructor, dataMissingNameRows) {
    const std::string input = "{\n"
            "      \"S\": 8,\n"
            "      \"b\": 3,\n"
            "      \"E\": 8,\n"
            "      \"m\": 32,\n"
            "      \"replacement\": \"LRU\",\n"
            "      \"cache-writes\": true,\n"
            "      \"data\": [\n"
            "            { \"cols\": 4, \"base\": 2863311530 },\n"
            "            { \"name\": \"B\", \"rows\": 6, \"cols\": 1, \"base\": 3149642683 }\n"
            "      ],\n"
            "      \"loops\": [\n"
            "            { \"idx\": \"i\", \"step\": 1, \"limit\": 6 },\n"
            "            { \"idx\": \"j\", \"step\": 2, \"limit\": 4 }\n"
            "      ],\n"
            "      \"computation\": {\"LHS\": \"C\", \"RHS\": [\"A\", \"B\"]}\n"
            "}";
    EXPECT_ANY_THROW({Cache::Simulator sim = Cache::Simulator(input);});
}

TEST(simulatorConstructor, duplicateDataName) {
    const std::string input = "{\n"
            "      \"S\": 8,\n"
            "      \"b\": 3,\n"
            "      \"E\": 8,\n"
            "      \"m\": 32,\n"
            "      \"replacement\": \"LRU\",\n"
            "      \"cache-writes\": true,\n"
            "      \"data\": [\n"
            "            { \"name\": \"A\", \"rows\": 4, \"cols\": 4, \"base\": 2863311530 },\n"
            "            { \"name\": \"A\", \"rows\": 6, \"cols\": 1, \"base\": 3149642683 }\n"
            "      ],\n"
            "      \"loops\": [\n"
            "            { \"idx\": \"i\", \"step\": 1, \"limit\": 6 },\n"
            "            { \"idx\": \"j\", \"step\": 2, \"limit\": 4 }\n"
            "      ],\n"
            "      \"computation\": {\"LHS\": \"C\", \"RHS\": [\"A\", \"B\"]}\n"
            "}";
    EXPECT_ANY_THROW({Cache::Simulator sim = Cache::Simulator(input);});
}

TEST(simulatorConstructor, missingLoops) {
    const std::string input = "{\n"
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
            "      \"computation\": {\"LHS\": \"C\", \"RHS\": [\"A\", \"B\"]}\n"
            "}";
    EXPECT_ANY_THROW({Cache::Simulator sim = Cache::Simulator(input);});
}

TEST(simulatorConstructor, invalidLoops) {
    const std::string input = "{\n"
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
            "            { \"idx\": \"i\"},\n"
            "            { \"idx\": \"j\", \"step\": 2, \"limit\": 4 }\n"
            "      ],\n"
            "      \"computation\": {\"LHS\": \"C\", \"RHS\": [\"A\", \"B\"]}\n"
            "}";
    EXPECT_ANY_THROW({Cache::Simulator sim = Cache::Simulator(input);});
}

TEST(simulatorConstructor, duplicateLoopIdx) {
    const std::string input = "{\n"
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
            "            { \"idx\": \"i\", \"step\": 2, \"limit\": 4 }\n"
            "      ],\n"
            "      \"computation\": {\"LHS\": \"C\", \"RHS\": [\"A\", \"B\"]}\n"
            "}";
    EXPECT_ANY_THROW({Cache::Simulator sim = Cache::Simulator(input);});
}

TEST(simulatorConstructor, missingComputation) {
    const std::string input = "{\n"
            "      \"S\": 8,\n"
            "      \"b\": 3,\n"
            "      \"E\": 8,\n"
            "      \"m\": 32,\n"
            "      \"replacement\": \"LFU\",\n"
            "      \"cache-writes\": true,\n"
            "      \"data\": [\n"
            "            { \"name\": \"A\", \"rows\": 4, \"cols\": 4, \"base\": 2863311530 },\n"
            "            { \"name\": \"B\", \"rows\": 6, \"cols\": 1, \"base\": 3149642683 }\n"
            "      ],\n"
            "      \"loops\": [\n"
            "            { \"idx\": \"i\", \"step\": 1, \"limit\": 6 },\n"
            "            { \"idx\": \"j\", \"step\": 2, \"limit\": 4 }\n"
            "      ],\n"
            "}";
    EXPECT_ANY_THROW({Cache::Simulator sim = Cache::Simulator(input);});
}
