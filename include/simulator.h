#include <stdbool.h>

#include "cache.h"

typedef struct Simulator Simulator;

struct Simulator {
    // Data structure A.
    size_t data_a_rows, data_a_cols;
    // Data structure B.
    size_t data_b_rows, data_b_cols;
    // Data structure C.
    size_t data_c_rows, data_c_cols;
    // Loop maximums.
    size_t i_max, i_jump;
    size_t j_max, j_jump;
    size_t k_max, k_jump;
    // Data base addresses.
    uint32_t a_base_addr;
    uint32_t b_base_addr;
    uint32_t c_base_addr;
    // Element size.
    size_t elem_size;
    // Cache.
    Cache cache;
};

void run_simulator(Simulator* sim);

