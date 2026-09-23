#include "store.h"
#include "pool.h"

#include <stdio.h>
#include <stdlib.h>

ComponentStore componentstore_create() {
    ComponentStore store;
    store.pools = Sparse_voidptr_create(NULL);

    return store;
}

void componentstore_register(ComponentStore *store, uint32_t type_id,
                               size_t stride) {
    ComponentPool *pool = componentpool_create(stride);
    if (!pool) {
        fprintf(stderr,
                "ERROR: Couldn't create new pool for component typeId: %u",
                type_id);
        abort();
    }

    Sparse_voidptr_add(store->pools, type_id, (void *)pool);
}

void componentstore_add(ComponentStore *store, uint32_t type_id, uint32_t entity_id, const void *data) {
    ComponentPool* pool = (ComponentPool*)Sparse_voidptr_get(store->pools, type_id);
    if (!pool) {
        fprintf(stderr, "ERROR: Tried to add a component before registering");
        abort();
    }

    componentpool_add(pool, entity_id, data);
}

void* componentstore_get(ComponentStore* store, uint32_t type_id, uint32_t entity_id) {
    ComponentPool* pool = Sparse_voidptr_get(store->pools, type_id);
    if (!pool) {
        fprintf(stderr, "ERROR: Component previously not registred");
        abort();
    }

    return componentpool_get(pool, entity_id);
}

void componentstore_remove(ComponentStore *store, uint32_t type_id, uint32_t entity_id) {
    ComponentPool* pool = Sparse_voidptr_get(store->pools, type_id);
    if (!pool) {
        fprintf(stderr, "ERROR: Component previously not registred");
        abort();
    }

    componentpool_remove(pool, entity_id);
}
