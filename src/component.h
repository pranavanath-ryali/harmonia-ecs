#ifndef HARMONIA_COMPONENT
#define HARMONIA_COMPONENT

#include <stddef.h>
#include <stdint.h>

static uint32_t next_component_id = 0;

#define DECLARE_COMPONENT_ID(T) \
    static inline uint32_t get_component_id_##T(void) { \
        static uint32_t id = UINT32_MAX; \
        if (id == UINT32_MAX) id = next_component_id++; \
        return id; \
    }

#define COMPONENT_ID(T) get_component_id_##T()

typedef struct {
    void* data;
    size_t stride;
    uint32_t count;
    uint32_t capacity;
} ComponentPool;

void ecs_add_component_to_pool(ComponentPool* pool, const void* component_data);

#endif // HARMONIA_COMPONENT
