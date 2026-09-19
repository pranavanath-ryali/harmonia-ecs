#include "id_generator.h"
#include <stdint.h>
#include <stdlib.h>

IdGenerator* create_id_generator() {
    IdGenerator* gen = calloc(1, sizeof(IdGenerator));

    gen->next_id = 0;

    gen->free_list = NULL;
    gen->free_count = 0;
    gen->free_capacity = 0;

    return gen;
}

uint32_t id_generator_next(IdGenerator *generator) {
    if (generator->free_count > 0) {
        return generator->free_list[--generator->free_count];
    }

    return generator->next_id++;
}

void id_generator_remove(IdGenerator *generator, uint32_t id) {
    if (generator->free_count == generator->free_capacity) {
        generator->free_capacity = generator->free_capacity ? generator->free_capacity * 2 : 4;
        generator->free_list = realloc(generator->free_list, generator->free_capacity * sizeof(uint32_t));
    }

    generator->free_list[generator->free_count++] = id;
}
