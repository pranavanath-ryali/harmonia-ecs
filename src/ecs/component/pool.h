#ifndef HARMONIA_COMPONENT_POOL
#define HARMONIA_COMPONENT_POOL

#include "../../utils/types.h"

#include <stddef.h>
#include <stdint.h>

typedef struct {
    void *data;
    size_t stride;
    uint32_t capacity;

    Sparse(uint32_t) * entityid_map;
    DynArray(uint32_t) * index_map;
} ComponentPool;

ComponentPool *componentpool_create(size_t stride);

void componentpool_add(ComponentPool *pool, uint32_t entity_id,
                       const void *data);
void *componentpool_get(ComponentPool *pool, uint32_t entity_id);

void componentpool_remove(ComponentPool *pool, uint32_t entity_id);

#endif // HARMONIA_COMPONENT_POOL
