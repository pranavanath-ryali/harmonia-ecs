#include "world.h"
#include <stdlib.h>

World *create_world() {
  World *w = calloc(1, sizeof(World));

  w->next_entityid = 0;

  return w;
}

EntityId ecs_create_entity(World *w) {
    if (w->free_count > 0) {
        return w->free_list[--(w->free_count)];
    }
    return w->next_entityid++;
}

void ecs_destroy_entity(World *w, EntityId entity_id) {
    if (w->free_count == w->free_capacity) {
        w->free_capacity = w->free_capacity ? w->free_capacity * 2 : 8;
        w->free_list = realloc(w->free_list, w->free_capacity);
    }

    w->free_list[w->free_count++] = entity_id;
}

void destroy_world(World* w) {
    free(w->free_list);
    free(w);
}
