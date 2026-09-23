#include "../src/ecs/world.h"
#include "../src/ecs/world_cell.h"
#include "../src/utils/type_id.h"
#include <stdio.h>

struct ComponentA {
    int x;
};

DECLARE_TYPE_ID(ComponentA);

void system_test(struct WorldCell *cell) {
    struct ComponentA *a = world_get_component(cell, TYPE_ID(ComponentA), 0);
    a->x += 10;
}
void another_system_test(struct WorldCell *cell) {
    struct ComponentA *a = world_get_component(cell, TYPE_ID(ComponentA), 0);
    printf("YAY ITS WORKING; %d\n", a->x);
}

int main() {
    struct World *world = create_world();

    uint32_t e = ecs_create_entity(world);
    ecs_component_register(world, TYPE_ID(ComponentA),
                           sizeof(struct ComponentA));

    struct ComponentA a;
    a.x = 10;
    ecs_component_add(world, TYPE_ID(ComponentA), e, &a);

    ecs_system_register(world, UPDATE, system_test);
    ecs_system_register(world, UPDATE, another_system_test);

    struct WorldCell cell;
    cell.world = world;
    ecs_system_run(world, UPDATE, &cell);
}
