#ifndef HARMONIA_WORLD
#define HARMONIA_WORLD

#include <stdint.h>

typedef uint32_t EntityId;

typedef struct {
    EntityId next_entityid;
    EntityId* free_list;
    EntityId free_count;
    EntityId free_capacity;
} World;

World *create_world();
void destroy_world(World* w);

EntityId ecs_create_entity(World *w);
void ecs_destroy_entity(World *w, uint32_t entity_id);

#endif // HARMONIA_WORLD
