#ifndef HARMONIA_ECS_WORLD_CELL
#define HARMONIA_ECS_WORLD_CELL

#include "world.h"
#include <stdint.h>

typedef struct {
    World* world;
} WorldCell;

static inline const void* world_get_component(WorldCell* cell, uint32_t type_id, EntityId entity_id) {
    return ecs_component_get(cell->world, type_id, entity_id);
}
static inline void* world_get_component_mut(WorldCell* cell, uint32_t type_id, EntityId entity_id) {
    return ecs_component_get_mut(cell->world, type_id, entity_id);
}

#endif // !HARMONIA_ECS_WORLD_CELL
