#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "../src/utils/sparse.h"

int main() {
    SparseArray* array = sparse_create();

    sparse_add(array, 0, 123);
    sparse_add(array, 1, 456);
    sparse_add(array, 2, 789);
    sparse_add(array, 3, 111);

    printf("0: %d; 1: %d; 2: %d; 3: %d", sparse_get(array, 0), sparse_get(array, 1), sparse_get(array, 2), sparse_get(array, 3));

    sparse_add(array, 16, 135);
    printf("\nHMM: %d", sparse_get(array, 16));
    printf("\n???: %d", sparse_get(array, 10));

    sparse_pop(array, 16);
    printf("\nHMM: %d", sparse_get(array, 16));
}
