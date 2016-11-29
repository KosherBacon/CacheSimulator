#ifndef DATA_H
#define DATA_H

#include <stdint.h>

using namespace std;

typedef struct Data Data;

struct Data {
    char name; /**< Character identifying the name of this block. */
    int color; /**< Integer representing the color of this block. */
    size_t rows; /**< Number of rows in the data block. */
    size_t cols; /**< Number of columns in the data block. */
    uint32_t base_addr; /**< Base address of the memory block. */
};

#endif
