#ifndef HARMONIA_ECS_WORLD_CELL
#define HARMONIA_ECS_WORLD_CELL

#include <stdint.h>
#include "world.h"

struct WorldCell {
    struct World* world;
};

static inline const void* world_get_component(struct WorldCell* cell, uint32_t type_id, uint32_t entity_id) {
    return world_component_get(cell->world, type_id, entity_id);
}
static inline void* world_get_component_mut(struct WorldCell* cell, uint32_t type_id, uint32_t entity_id) {
    return world_component_get_mut(cell->world, type_id, entity_id);
}

#endif // !HARMONIA_ECS_WORLD_CELL
