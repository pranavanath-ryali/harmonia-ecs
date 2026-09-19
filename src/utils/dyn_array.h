#ifndef UTILS_DYN_ARRAY
#define UTILS_DYN_ARRAY

#include <stdint.h>

typedef struct {
    uint32_t* data;
    uint32_t count;
    uint32_t capacity;
} DynArray;

DynArray* array_create();

void array_push(DynArray* arr, uint32_t value);
void array_write_at(DynArray* arr, uint32_t index, uint32_t value);
uint32_t array_pop(DynArray* arr);
uint32_t array_get(DynArray* arr, uint32_t index);

#endif // UTILS_DYN_ARRAY
