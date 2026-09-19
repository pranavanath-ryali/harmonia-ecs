#ifndef UTILS_ID_GENERATOR 
#define UTILS_ID_GENERATOR

#include <stdint.h>

typedef struct {
    uint32_t next_id;

    uint32_t* free_list;
    uint32_t free_count;
    uint32_t free_capacity;
} IdGenerator;

IdGenerator* create_id_generator();

uint32_t id_generator_next(IdGenerator* generator);
void id_generator_remove(IdGenerator* generator, uint32_t id);

#endif // UTILS_ID_GENERATOR
