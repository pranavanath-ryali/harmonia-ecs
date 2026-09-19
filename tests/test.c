#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "../src/component.h"

typedef struct {
    int x;
} MyC;


int main() {
    ComponentPool* pool = pool_create(sizeof(MyC));

    MyC c;
    c.x = 10;
    pool_add(pool, 0, &c);
    c.x = 20;
    pool_add(pool, 1, &c);
    c.x = 30;
    pool_add(pool, 2, &c);

    MyC* retrived = pool_get(pool, 1);
    printf("Value!: %d", retrived->x);

    pool_remove(pool, 1);

    retrived = pool_get(pool, 2);
    printf("\nValue!: %d", retrived->x);

    c.x = 40;
    pool_add(pool, 5, &c);

    retrived = pool_get(pool, 5);
    printf("\nValue!: %d", retrived->x);
}
