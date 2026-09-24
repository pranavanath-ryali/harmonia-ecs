#ifndef HARMONIA_APP
#define HARMONIA_APP

#include "../ecs/world_cell.h"
#include "../ecs/world.h"

static inline struct World *app_create_world() {
    struct World *world = create_world();

    return world;
}

static inline void app_system_register(struct World *world,
                                       enum SystemStage stage,
                                       SystemFunc system) {
    world_system_register(world, stage, system);
};

static inline void app_run(struct World *world) {
    world->is_running = 1;

    struct WorldCell cell;
    cell.world = world;

    while (world->is_running) {
        world_system_run(world, PRE_UPDATE, &cell);
        world_system_run(world, UPDATE, &cell);
        world_system_run(world, POST_UPDATE, &cell);

        world_system_run(world, PRE_RENDER, &cell);
        world_system_run(world, RENDER, &cell);
        world_system_run(world, POST_RENDER, &cell);

        break;
    }
}

#endif // HARMONIA_APP
