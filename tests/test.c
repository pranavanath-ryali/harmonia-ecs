#include <assert.h>
#include <stdio.h>

#include "../src/utils/type_id.h"

typedef struct {} TestComponent1;
typedef struct {} TestComponent2;
typedef struct {} TestComponent3;

DECLARE_TYPE_ID(TestComponent1);
DECLARE_TYPE_ID(TestComponent2);
DECLARE_TYPE_ID(TestComponent3);

int main() {
    printf("%u\n", TYPE_ID(TestComponent1));
    printf("%u\n", TYPE_ID(TestComponent2));
    printf("%u\n", TYPE_ID(TestComponent1));
}
