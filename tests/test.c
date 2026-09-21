#include <assert.h>
#include <stdio.h>

#include "../src/utils/type_id.h"
#include "../src/component/pool.h"
#include "../src/component/store.h"

typedef struct { int x; } MyA;
typedef struct { int x; } MyB;
typedef struct { int x; } MyC;

DECLARE_TYPE_ID(MyA);
DECLARE_TYPE_ID(MyB);
DECLARE_TYPE_ID(MyC);

int main() {
    ComponentStore store = componentstore_create();

    componentstore_register(&store, TYPE_ID(MyA), sizeof(MyA));
    componentstore_register(&store, TYPE_ID(MyB), sizeof(MyB));
    componentstore_register(&store, TYPE_ID(MyC), sizeof(MyC));

    MyA a;
    a.x = 10;
    componentstore_add(&store, TYPE_ID(MyA), 0, (const void*)&a);

    MyA* yay = componentstore_get(&store, 0, TYPE_ID(MyA));
    printf("OUTPUT: %d\n", yay->x);
}
