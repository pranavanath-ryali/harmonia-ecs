#ifndef HARMONIA_COMPONENT_STORE
#define HARMONIA_COMPONENT_STORE

#include "../utils/types.h"
#include "pool.h"

typedef struct {
    Dense(voidptr) * pools;
} ComponentStore;

inline ComponentStore create_component_store();
inline void register_component(ComponentStore *store, uint32_t type_id,
                               size_t stride);

inline void add_component(ComponentStore *store, uint32_t type_id,
                          uint32_t entity_id, const void *data);

#endif // HARMONIA_COMPONENT_STORE
