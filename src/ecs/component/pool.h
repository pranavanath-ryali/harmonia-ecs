#ifndef HARMONIA_COMPONENT_POOL
#define HARMONIA_COMPONENT_POOL

#include "../../utils/types.h"

#include <stddef.h>
#include <stdint.h>

struct ComponentPool {
    void *data;
    size_t stride;
    uint32_t capacity;

    Sparse(uint32_t) * entityid_map;
    DynArray(uint32_t) * index_map;
};

struct ComponentPool *componentpool_create(size_t stride);

void componentpool_add(struct ComponentPool *pool, uint32_t entity_id,
                       const void *data);
void *componentpool_get(struct ComponentPool *pool, uint32_t entity_id);

void componentpool_remove(struct ComponentPool *pool, uint32_t entity_id);

#endif // HARMONIA_COMPONENT_POOL
