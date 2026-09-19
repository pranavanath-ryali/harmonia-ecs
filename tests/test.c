#include <assert.h>
#include <stdio.h>

#include "../src/component/pool.h"

typedef struct {
    int x;
} MyC;


int main() {
    ComponentPool* pool = pool_create(sizeof(MyC));

    MyC a = {10}, b = {20}, c = {30};

    pool_add(pool, 0, &a); // entity 0 -> dense 0
    pool_add(pool, 1, &b); // entity 1 -> dense 1
    pool_add(pool, 2, &c); // entity 2 -> dense 2

    assert(((MyC*)pool_get(pool, 0))->x == 10);
    assert(((MyC*)pool_get(pool, 1))->x == 20);
    assert(((MyC*)pool_get(pool, 2))->x == 30);
    printf("initial adds OK\n");

    // remove the MIDDLE entity - forces swap-and-pop
    pool_remove(pool, 1);

    // entity 2 should have been moved into dense slot 1 (where entity 1 was)
    assert(((MyC*)pool_get(pool, 0))->x == 10); // untouched
    assert(((MyC*)pool_get(pool, 2))->x == 30); // moved, but still correct value
    printf("middle remove + swap OK\n");

    // entity 1 should no longer be accessible - this SHOULD abort if you uncomment it
    // pool_get(pool, 1);

    // add a new entity - should land in the now-freed slot cleanly, no collision
    MyC d = {40};
    pool_add(pool, 3, &d);

    assert(((MyC*)pool_get(pool, 0))->x == 10);
    assert(((MyC*)pool_get(pool, 2))->x == 30);
    assert(((MyC*)pool_get(pool, 3))->x == 40);
    printf("re-add after remove OK\n");

    // remove the LAST entity - should hit the early-return branch, no swap needed
    pool_remove(pool, 3);
    assert(((MyC*)pool_get(pool, 0))->x == 10);
    assert(((MyC*)pool_get(pool, 2))->x == 30);
    printf("last-element remove OK\n");

    printf("ALL TESTS PASSED\n");
    return 0;
}
