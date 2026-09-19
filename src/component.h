#ifndef HARMONIA_COMPONENT
#define HARMONIA_COMPONENT

#include "utils/sparse.h"
#include "utils/dyn_array.h"

#include <stddef.h>
#include <stdint.h>

typedef struct {
    void* data;
    size_t stride;
    uint32_t capacity;

    SparseArray* sparse; // EntityID -> dense_index
    DynArray* dense_to_entity; // dense_index -> EntityId // TODO: Rename
} ComponentPool;

ComponentPool* pool_create(size_t stride);

void pool_add(ComponentPool* pool, uint32_t entity_id, const void* data);
void* pool_get(ComponentPool* pool, uint32_t entity_id);

void pool_remove(ComponentPool* pool, uint32_t entity_id);

#endif // HARMONIA_COMPONENT
