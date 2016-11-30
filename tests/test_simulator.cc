#include <stdint.h>

// Used blocks
#include "../include/simulator.h"

// Catch
#include "../include/Catch/catch.hpp"

TEST_CASE("simulator set_from_addr", "[simulator]")
{
    SECTION("zero address, zero block offset bits, zero tag bits")
    {
        uint32_t addr = 0;
        size_t b_bits = 0;
        size_t tag_bits = 0;
        REQUIRE(set_from_addr(addr, b_bits, tag_bits) == (uint32_t) 0);
    }

    SECTION("zero address, 30 block offset bits, 1 tag bit")
    {
        uint32_t addr = 0;
        size_t b_bits = 30;
        size_t tag_bits = 1;
        REQUIRE(set_from_addr(addr, b_bits, tag_bits) == (uint32_t) 0);
    }
}
