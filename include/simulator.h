#include <string>

#include <stdbool.h>

#include "cache.h"

using namespace std;

typedef struct Simulator Simulator;

struct Simulator {
    // Data structure A.
    size_t data_a_rows; /**< Number of rows in the A array/matrix. */
    size_t data_a_cols; /**< Number of columns in the A array/matrix. */
    // Data structure B.
    size_t data_b_rows; /**< Number of rows in the B array/matrix. */
    size_t data_b_cols; /**< Number of columns in the B array/matrix. */
    // Data structure C.
    size_t data_c_rows; /**< Number of rows in the C array/matrix. */
    size_t data_c_cols; /**< Number of columns in the C array/matrix. */
    // Loop maximums and jumps.
    int i_max; /**< Maximum value of the i loop. */
    int i_jump; /**< The step for each iteration of the i loop. */
    int j_max; /**< Maximum value of the j loop. */
    int j_jump; /**< The step for each iteration of the j loop. */
    int k_max; /**< Maximum value of the k loop. */
    int k_jump; /**< The step for each iteration of the k loop. */
    // Data base addresses.
    uint32_t a_base_addr; /**< Base address of the A data array/matrix. */
    uint32_t b_base_addr; /**< Base address of the B data array/matrix. */
    uint32_t c_base_addr; /**< Base address of the C data array/matrix. */
    // Size of a memory address in the cache.
    size_t addr_size; /**< Size of a memory address in this cache system. */
    // Size of a data element in each array/matrix.
    size_t elem_size; /**< Represents the size of each matrix element. */
    Cache cache; /**< Holds the actual cache data. */
};

void allocate_simulator_data(Simulator* sim);
void destroy_simulator(Simulator* sim);
std::string run_simulator(Simulator* sim);

