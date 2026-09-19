#include "dyn_array.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

DynArray* array_create() {
    DynArray* arr = calloc(1, sizeof(DynArray));

    arr->data = NULL;
    arr->count = 0;
    arr->capacity = 0;

    return arr;
}

void array_push(DynArray *arr, uint32_t value) {
    if (arr->count == arr->capacity) {
        arr->capacity = arr->capacity ? arr->capacity * 2 : 4;
        arr->data = realloc(arr->data, arr->capacity * sizeof(uint32_t));
    }

    arr->data[arr->count++] = value;
}

void array_write_at(DynArray *arr, uint32_t index, uint32_t value) {
    if (index >= arr->count) {
        fprintf(stderr, "ERROR");
        abort();
    }

    arr->data[index] = value;
}

uint32_t array_pop(DynArray *arr) {
    if (arr->count == 0) {
        fprintf(stderr, "ERROR");
        abort();
    }

    return arr->data[--arr->count];
}

uint32_t array_get(DynArray *arr, uint32_t index) {
    if (index >= arr->count) {
        fprintf(stderr, "ERROR");
        abort();
    }

    return arr->data[index];
}
