#ifndef HARMONIA_SYSTEM_STORE
#define HARMONIA_SYSTEM_STORE

#include "../utils/types.h"
#include "../utils/id_generator.h"

typedef void (*SystemFunc)(void);

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

typedef struct {
    IdGenerator* id_gen;

    DynArray(SystemFunc)* systems;
    DynArray(uint32_t)* stage_sysid[SYSTEM_STAGE_COUNT];
} SystemStore;

SystemStore systemstore_create();

void systemstore_register(SystemStore* store, enum SystemStage stage, SystemFunc system);
void systemstore_run(SystemStore* store, enum SystemStage stage);

#endif // HARMONIA_SYSTEM_STORE
