#include "../src/app/app.h"

void test_system_1(struct WorldCell *cell) { printf("SYSTEMID: 1\n"); }

void test_system_2(struct WorldCell *cell) { printf("SYSTEMID: 2\n"); }

void test_system_3(struct WorldCell *cell) { printf("SYSTEMID: 3\n"); }

void test_system_4(struct WorldCell *cell) { printf("SYSTEMID: 4\n"); }

void test_system_5(struct WorldCell *cell) { printf("SYSTEMID: 5\n"); }

void test_system_6(struct WorldCell *cell) { printf("SYSTEMID: 6\n"); }

void test_system_7(struct WorldCell *cell) { printf("SYSTEMID: 7\n"); }

void test_system_8(struct WorldCell *cell) { printf("SYSTEMID: 8\n"); }

void test_system_9(struct WorldCell *cell) { printf("SYSTEMID: 9\n"); }

void test_system_10(struct WorldCell *cell) { printf("SYSTEMID: 10\n"); }

int main() {
    struct World* world = app_create_world();

    app_system_register(world, PRE_UPDATE, test_system_1);
    app_system_register(world, PRE_UPDATE, test_system_9);
    app_system_register(world, PRE_UPDATE, test_system_10);
    app_system_register(world, UPDATE, test_system_2);
    app_system_register(world, UPDATE, test_system_5);
    app_system_register(world, POST_UPDATE, test_system_4);
    app_system_register(world, UPDATE, test_system_3);

    app_run(world);
}
