#ifndef HARMONIA_SYSTEM_STORE
#define HARMONIA_SYSTEM_STORE

#include "../../utils/types.h"
#include "../../utils/id_generator.h"

#include <stdlib.h>

struct WorldCell;
typedef void (*SystemFunc)(struct WorldCell* cell);

#define SYSTEM_STAGE_COUNT 9
enum SystemStage {
    PRE_UPDATE = 0,
    UPDATE = 1,
    POST_UPDATE = 2,

    PRE_FIXED_UPDATE = 3,
    FIXED_UPDATE = 4,
    POST_FIXED_UPDATE = 5,

    PRE_RENDER = 6,
    RENDER = 7,
    POST_RENDER = 8
};

DEFINE_DYN_ARRAY(SystemFunc);

struct SystemStore {
    DynArray(SystemFunc)* systems;
    DynArray(uint32_t)* stage_sysid[SYSTEM_STAGE_COUNT];
};

struct SystemStore systemstore_create();

void systemstore_register(struct SystemStore* store, enum SystemStage stage, SystemFunc system);
void systemstore_run(struct SystemStore* store, enum SystemStage stage, struct WorldCell* world);

static inline void systemstore_free(struct SystemStore* store) {
    free(store->systems);
    for (int i = 0; i < SYSTEM_STAGE_COUNT; ++i) {
        free(store->stage_sysid[i]);
    }
    free(store);
}

#endif // HARMONIA_SYSTEM_STORE
