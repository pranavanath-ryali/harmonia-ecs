#ifndef UTILS_SPARE
#define UTILS_SPARE

#include <stdint.h>

typedef struct {
    uint32_t* data;
    uint32_t capacity;
} SparseArray;

SparseArray* sparse_create();

void sparse_add(SparseArray* array, uint32_t key, uint32_t value);
uint32_t sparse_get(SparseArray* array, uint32_t key);
void sparse_pop(SparseArray* array, uint32_t key);

#endif // UTILS_SPARE
