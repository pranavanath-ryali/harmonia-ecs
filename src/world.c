#include "world.h"
#include "utils/id_generator.h"
#include <stdlib.h>

World *create_world() {
  World *w = calloc(1, sizeof(World));

  w->id_gen = create_id_generator();

  return w;
}

EntityId ecs_create_entity(World *w) {
    return id_generator_next(w->id_gen);
}

void ecs_destroy_entity(World *w, EntityId entity_id) {
    id_generator_remove(w->id_gen, entity_id);
}

void destroy_world(World* w) {
    free(w->id_gen);
    free(w);
}
