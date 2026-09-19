#include "pool.h"
#include "../utils/dyn_array.h"
#include "../utils/sparse.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

ComponentPool* pool_create(size_t stride) {
    ComponentPool* pool = calloc(1, sizeof(ComponentPool));

    pool->stride = stride;
    pool->capacity = 0;
    pool->data = NULL;

    pool->sparse = sparse_create();
    pool->dense_to_entity = array_create();

    return pool;
}

void pool_add(ComponentPool *pool, uint32_t entity_id, const void *data) {
    if (pool->dense_to_entity->count== pool->capacity) {
        pool->capacity = pool->capacity ? pool->capacity * 2 : 4;
        pool->data = realloc(pool->data, pool->capacity * pool->stride);
    }

    void* dest = (char*)pool->data + (pool->dense_to_entity->count* pool->stride);
    memcpy(dest, data, pool->stride);

    sparse_add(pool->sparse, entity_id, pool->dense_to_entity->count);
    array_push(pool->dense_to_entity, entity_id);
}

void* pool_get(ComponentPool* pool, uint32_t entity_id) {
    uint32_t dense_index = sparse_get(pool->sparse, entity_id);
    if (dense_index == UINT32_MAX) {
        fprintf(stderr, "ERROR: Entity with id: %u does not have compoenent", entity_id);
        abort();
    }

    void* ptr = (char*)pool->data + (dense_index * pool->stride);
    return ptr;
}

void pool_remove(ComponentPool *pool, uint32_t entity_id) {
    uint32_t dense_index = sparse_get(pool->sparse, entity_id);
    if (dense_index == UINT32_MAX) {
        fprintf(stderr, "ERROR: Entity with id: %u does not have compoenent", entity_id);
        abort();
    }
    sparse_pop(pool->sparse, entity_id);

    if (dense_index == pool->dense_to_entity->count - 1) {
        array_pop(pool->dense_to_entity);
        return;
    }

    const void* new_data = (const char*)pool->data + ((pool->dense_to_entity->count - 1) * pool->stride);
    void* dest = (char*)pool->data + (dense_index * pool->stride);

    memcpy(dest, new_data, pool->stride);

    uint32_t last_data_entity_id = array_pop(pool->dense_to_entity);

    sparse_add(pool->sparse, last_data_entity_id, dense_index);
    array_write_at(pool->dense_to_entity, dense_index, last_data_entity_id);
}
