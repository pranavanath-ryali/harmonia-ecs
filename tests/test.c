#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "../src/utils/id_generator.h"

int main() {
    IdGenerator* gen = create_id_generator();

    for (int i = 0; i < 512; i++) {
        uint32_t id = id_generator_next(gen);
        printf("%u\n", id);
    }

    id_generator_remove(gen, 128);

    uint32_t id = id_generator_next(gen);
    printf("%u\n", id);
}
