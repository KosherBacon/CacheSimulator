#include <stdint.h>

#include "../include/simulator.h"

// Catch testing framework.
#include "../include/Catch/catch.hpp"

TEST_CASE("simulator set_from_addr", "[simulator]")
{
    SECTION("zero address, zero block offset bits, zero tag bits")
    {
        uint32_t addr = 0x0;
        size_t b_bits = 0;
        size_t tag_bits = 0;
        REQUIRE(set_from_addr(addr, b_bits, tag_bits) == (uint32_t) 0x0);
    }

    SECTION("zero address, 30 block offset bits, 1 tag bit")
    {
        uint32_t addr = 0x0;
        size_t b_bits = 30;
        size_t tag_bits = 1;
        REQUIRE(set_from_addr(addr, b_bits, tag_bits) == (uint32_t) 0x0);
    }

    SECTION("non-zero address, 5 block offset bits, 18 tag bits")
    {
        uint32_t addr = 0xAAAA0020;
        size_t b_bits = 5;
        size_t tag_bits = 18;
        REQUIRE(set_from_addr(addr, b_bits, tag_bits) == (uint32_t) 0x1);
    }

    SECTION("non-zero address, 2 block offset bits, 22 tag bits")
    {
        uint32_t addr = 0xAAAA4444;
        size_t b_bits = 2;
        size_t tag_bits = 22;
        REQUIRE(set_from_addr(addr, b_bits, tag_bits) == (uint32_t) 0x11);
    }
}

TEST_CASE("simulator tag_from_addr", "[simulator]")
{
    SECTION("zero address, zero tag bits")
    {
        uint32_t addr = 0x0;
        size_t tag_bits = 0;
        REQUIRE(tag_from_addr(addr, tag_bits) == (uint32_t) 0x0);
    }

    SECTION("non-zero address, 32 tag bits")
    {
        uint32_t addr = 0xAAAA0000;
        size_t tag_bits = 32;
        REQUIRE(tag_from_addr(addr, tag_bits) == (uint32_t) 0x0);
    }

    SECTION("non-zero address, 22 tag bits")
    {
        uint32_t addr = 0xAAAA0000;
        size_t tag_bits = 22;
        REQUIRE(tag_from_addr(addr, tag_bits) == (uint32_t) 0x2AAA80);
    }

    SECTION("non-zero address, 11 tag bits")
    {
        uint32_t addr = 0xCCCCCCCC;
        size_t tag_bits = 11;
        REQUIRE(tag_from_addr(addr, tag_bits) == (uint32_t) 0x666);
    }
}
