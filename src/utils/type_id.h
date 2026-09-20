#ifndef UTILS_TYPE_ID_GEN
#define UTILS_TYPE_ID_GEN

#include <stdint.h>
static uint32_t next_component_id = 0;

#define DECLARE_TYPE_ID(T) \
    static inline uint32_t get_type_id_##T(void) { \
        static uint32_t id = UINT32_MAX; \
        if (id == UINT32_MAX) id = next_component_id++; \
        return id; \
    }

#define TYPE_ID(T) get_type_id_##T()

#endif // UTILS_TYPE_ID_GEN
