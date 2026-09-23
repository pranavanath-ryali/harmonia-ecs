#ifndef HARMONIA_WORLD
#define HARMONIA_WORLD

#include "../utils/id_generator.h"
#include "component/store.h"
#include "system/store.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

struct World {
    IdGenerator *id_gen;

    struct ComponentStore component_store;
    struct SystemStore system_store;
} World;

struct World *create_world() {
    struct World *w = malloc(sizeof(World));

    w->id_gen = create_id_generator();
    w->component_store = componentstore_create();
    w->system_store = systemstore_create();

    return w;
};
void destroy_world(struct World *w) {
    componentstore_free(&w->component_store);
    systemstore_free(&w->system_store);

    free(w->id_gen);
    free(w);
};

static inline uint32_t ecs_create_entity(struct World *w) {
    return id_generator_next(w->id_gen);
};
static inline void ecs_destroy_entity(struct World *w, uint32_t entity_id) {
    id_generator_remove(w->id_gen, entity_id);
    // TODO: keep track of waht components the entity has and delete them all
};

static inline void ecs_component_register(struct World *w, uint32_t type_id,
                                          size_t stride) {
    componentstore_register(&w->component_store, type_id, stride);
};
static inline void ecs_component_add(struct World *w, uint32_t type_id,
                                     uint32_t entity_id, const void *data) {
    componentstore_add(&w->component_store, type_id, entity_id, data);
};
static inline const void *ecs_component_get(struct World *w, uint32_t type_id,
                                            uint32_t entity_id) {
    return componentstore_get(&w->component_store, type_id, entity_id);
};
static inline void *ecs_component_get_mut(struct World *w, uint32_t type_id,
                                          uint32_t entity_id) {
    return componentstore_get(&w->component_store, type_id, entity_id);
}
static inline void ecs_component_remove(struct World *w, uint32_t type_id,
                                        uint32_t entity_id) {
    componentstore_remove(&w->component_store, type_id, entity_id);
};

static inline void ecs_system_register(struct World *w, enum SystemStage stage,
                                       SystemFunc system) {
    systemstore_register(&w->system_store, stage, system);
};
static inline void ecs_system_run(struct World *w, enum SystemStage stage, struct WorldCell* cell) {
    systemstore_run(&w->system_store, stage, cell);
};

#endif // HARMONIA_WORLD
