#ifndef HARMONIA_COMPONENT
#define HARMONIA_COMPONENT

#include <stdint.h>

static uint32_t next_component_id = 0;

#define DECLARE_COMPONENT_ID(T) \
    static inline uint32_t get_component_id_##T(void) { \
        static uint32_t id = UINT32_MAX; \
        if (id == UINT32_MAX) id = next_component_id++; \
        return id; \
    }

#define COMPONENT_ID(T) get_component_id_##T()



#endif // HARMONIA_COMPONENT
