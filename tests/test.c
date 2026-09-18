#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "../src/world.h"
#include "../src/component.h"


typedef struct {} TestComponent1;
typedef struct {} TestComponent2;
typedef struct {} TestComponent3;

DECLARE_COMPONENT_ID(TestComponent1);
DECLARE_COMPONENT_ID(TestComponent2);
DECLARE_COMPONENT_ID(TestComponent3);

int main() {
    World *w = create_world();

    uint32_t e1 = ecs_create_entity(w);
    uint32_t e2 = ecs_create_entity(w);
    uint32_t e3 = ecs_create_entity(w);

    printf("Created %d %d %d\n", e1, e2, e3);

    ecs_destroy_entity(w, e2);

    uint32_t e4 = ecs_create_entity(w);

    printf("God new entity: %d\n", e4);

    printf("Components: %d %d %d\n", COMPONENT_ID(TestComponent1), COMPONENT_ID(TestComponent2), COMPONENT_ID(TestComponent3));


    return 0;
}
