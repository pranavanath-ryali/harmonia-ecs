#ifndef HARMONIA_WORLD
#define HARMONIA_WORLD

#include "utils/id_generator.h"
#include <stdint.h>

typedef uint32_t EntityId;

typedef struct {
    IdGenerator* id_gen;
} World;

World *create_world();
void destroy_world(World* w);

EntityId ecs_create_entity(World *w);
void ecs_destroy_entity(World *w, uint32_t entity_id);

#endif // HARMONIA_WORLD
