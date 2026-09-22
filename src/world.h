#ifndef HARMONIA_WORLD
#define HARMONIA_WORLD

#include "component/store.h"
#include "system/store.h"
#include "utils/id_generator.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint32_t EntityId;

typedef struct {
    IdGenerator *id_gen;

    ComponentStore component_store;
    SystemStore system_store;
} World;

World *create_world() {
    World *w = malloc(sizeof(World));

    w->id_gen = create_id_generator();
    w->component_store = componentstore_create();
    w->system_store = systemstore_create();

    return w;
};
void destroy_world(World *w) {
    componentstore_free(&w->component_store);
    systemstore_free(&w->system_store);

    free(w->id_gen);
    free(w);
};

static inline EntityId ecs_create_entity(World *w) {
    return id_generator_next(w->id_gen);
};
static inline void ecs_destroy_entity(World *w, uint32_t entity_id) {
    id_generator_remove(w->id_gen, entity_id);
    // TODO: keep track of waht components the entity has and delete them all
};

static inline void ecs_component_register(World *w, uint32_t type_id,
                                          size_t stride) {
    componentstore_register(&w->component_store, type_id, stride);
};
static inline void ecs_component_add(World *w, uint32_t type_id,
                                     EntityId entity_id, const void *data) {
    componentstore_add(&w->component_store, type_id, entity_id, data);
};
static inline void ecs_component_get(World *w, uint32_t type_id,
                                     EntityId entity_id) {
    componentstore_get(&w->component_store, type_id, entity_id);
};
static inline void ecs_component_remove(World *w, uint32_t type_id,
                                        EntityId entity_id) {
    componentstore_remove(&w->component_store, type_id, entity_id);
};

static inline void ecs_system_register(World *w, enum SystemStage stage,
                                       SystemFunc system) {
    systemstore_register(&w->system_store, stage, system);
};
static inline void ecs_system_run(World *w, enum SystemStage stage) {
    systemstore_run(&w->system_store, stage);
};

#endif // HARMONIA_WORLD
