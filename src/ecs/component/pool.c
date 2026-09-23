#include "pool.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

ComponentPool *componentpool_create(size_t stride) {
    ComponentPool *pool = malloc(sizeof(ComponentPool));
    if (!pool)
        return NULL;

    pool->stride = stride;
    pool->capacity = 0;
    pool->data = NULL;

    pool->entityid_map = Sparse_uint32_t_create(UINT32_MAX);
    if (!pool->entityid_map) {
        free(pool);
        return NULL;
    };

    pool->index_map = DynArray_uint32_t_create();
    if (!pool->index_map) {
        free(pool);
        return NULL;
    }

    return pool;
}

void componentpool_add(ComponentPool *pool, uint32_t entity_id,
                       const void *data) {
    if (pool->index_map->count == pool->capacity) {
        pool->capacity = pool->capacity ? pool->capacity * 2 : 4;
        pool->data = realloc(pool->data, pool->capacity * pool->stride);
    }

    void *dest = (char *)pool->data + (pool->index_map->count * pool->stride);
    memcpy(dest, data, pool->stride);

    Sparse_uint32_t_add(pool->entityid_map, entity_id, pool->index_map->count);
    DynArray_uint32_t_push(pool->index_map, entity_id);
}

void *componentpool_get(ComponentPool *pool, uint32_t entity_id) {
    uint32_t dense_index = Sparse_uint32_t_get(pool->entityid_map, entity_id);
    if (dense_index == UINT32_MAX) {
        fprintf(stderr, "ERROR: Entity with id: %u does not have compoenent",
                entity_id);
        abort();
    }

    voidptr ptr = (char *)pool->data + (dense_index * pool->stride);
    return ptr;
}

void componentpool_remove(ComponentPool *pool, uint32_t entity_id) {
    uint32_t dense_index = Sparse_uint32_t_get(pool->entityid_map, entity_id);
    if (dense_index == UINT32_MAX) {
        fprintf(stderr, "ERROR: Entity with id: %u does not have compoenent",
                entity_id);
        abort();
    }
    Sparse_uint32_t_pop(pool->entityid_map, entity_id);

    if (dense_index == pool->index_map->count - 1) {
        DynArray_uint32_t_pop(pool->index_map);
        return;
    }

    const void *new_data = (const char *)pool->data +
                           ((pool->index_map->count - 1) * pool->stride);
    void *dest = (char *)pool->data + (dense_index * pool->stride);

    memcpy(dest, new_data, pool->stride);

    uint32_t last_data_entity_id = DynArray_uint32_t_pop(pool->index_map);

    Sparse_uint32_t_add(pool->entityid_map, last_data_entity_id, dense_index);
    DynArray_uint32_t_write_at(pool->index_map, dense_index,
                               last_data_entity_id);
}
