#include "store.h"
#include "pool.h"
#include <stdio.h>
#include <stdlib.h>

inline ComponentStore create_component_store() {
    ComponentStore store;
    store.pools = Dense_voidptr_create(NULL);

    return store;
}

inline void register_component(ComponentStore *store, uint32_t type_id,
                               size_t stride) {
    ComponentPool *pool = pool_create(stride);
    if (!pool) {
        fprintf(stderr,
                "ERROR: Couldn't create new pool for component typeId: %u",
                type_id);
        abort();
    }

    Dense_voidptr_add(store->pools, type_id, (void *)pool);
}

inline void add_component(ComponentStore *store, uint32_t type_id, uint32_t entity_id, const void *data) {
    ComponentPool* pool = (ComponentPool*)Dense_voidptr_get(store->pools, type_id);
    if (!pool) {
        fprintf(stderr, "ERROR: Tried to add a component before registering");
        abort();
    }

    pool_add(pool, entity_id, data);
}
