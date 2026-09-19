#include "sparse.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

SparseArray* sparse_create() {
    SparseArray *array = calloc(1, sizeof(SparseArray));

    array->capacity = 2;

    array->data = malloc(2 * sizeof(uint32_t));
    array->data[0] = UINT32_MAX;
    array->data[1] = UINT32_MAX;

    return array;
}

void sparse_add(SparseArray *array, uint32_t key, uint32_t value) {
    if (key >= array->capacity) {
        uint32_t old_capacity = array->capacity;

        while (key >= array->capacity) {
            array->capacity *= 2;
        }

        array->data = realloc(array->data, array->capacity * sizeof(uint32_t));

        for (uint32_t i = old_capacity; i < array->capacity; ++i) {
            array->data[i] = UINT32_MAX;
        }
    }

    array->data[key] = value;
}

uint32_t sparse_get(SparseArray *array, uint32_t key) {
    if (key >= array->capacity) {
        fprintf(stderr, "ERROR: Given key: %d is beyond the size of current sparse", key);
        abort();
    }

    return array->data[key];
}

void sparse_pop(SparseArray *array, uint32_t key) {
    if (key >= array->capacity) {
        fprintf(stderr, "ERROR: Given key: %d is beyond the size of current sparse", key);
        abort();
    }

    array->data[key] = UINT32_MAX;
}
