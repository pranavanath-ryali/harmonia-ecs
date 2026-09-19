#ifndef HARMONIA_COMPONENT
#define HARMONIA_COMPONENT

#include <stddef.h>
#include <stdint.h>

typedef struct {
    void* data;
    size_t stride;
    uint32_t count;
    uint32_t capacity;
} ComponentPool;

#endif // HARMONIA_COMPONENT
