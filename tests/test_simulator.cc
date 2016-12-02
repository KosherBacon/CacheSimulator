#include <stdint.h>

#include "../include/simulator.h"

// Catch testing framework.
#include "../include/Catch/catch.hpp"

TEST_CASE("simulator set_from_addr", "[simulator]")
{
    SECTION("zero address, zero block offset bits, zero tag bits")
    {
        uint32_t addr = 0;
        size_t b_bits = 0;
        size_t tag_bits = 0;
        REQUIRE(set_from_addr(addr, b_bits, tag_bits) == (uint32_t) 0x0);
    }

    SECTION("zero address, 30 block offset bits, 1 tag bit")
    {
        uint32_t addr = 0;
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
