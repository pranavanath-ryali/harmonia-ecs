#ifndef HARMONIA_COMPONENT_STORE
#define HARMONIA_COMPONENT_STORE

#include "../utils/types.h"
#include <stdint.h>

typedef struct {
    Dense(voidptr) * pools;
} ComponentStore;

ComponentStore componentstore_create();

void componentstore_register(ComponentStore *store, uint32_t type_id,
                               size_t stride);
void componentstore_add(ComponentStore *store, uint32_t type_id,
                          uint32_t entity_id, const void *data);
void* componentstore_get(ComponentStore* store, uint32_t entity_id, uint32_t type_id);
void componentstore_remove(ComponentStore* store, uint32_t entity_id, uint32_t type_id);

#endif // HARMONIA_COMPONENT_STORE
