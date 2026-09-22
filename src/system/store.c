#include "store.h"
#include <stdint.h>

SystemStore systemstore_create() {
    SystemStore store;

    store.id_gen = create_id_generator();
    store.systems = DynArray_SystemFunc_create();

    for (int i = 0; i < SYSTEM_STAGE_COUNT; ++i) {
        store.stage_sysid[i] = DynArray_uint32_t_create();
    }

    return store;
}

void systemstore_register(SystemStore *store, enum SystemStage stage,
                          SystemFunc system) {
    uint8_t stage_int = stage;
    uint32_t system_id = store->systems->count;

    DynArray_uint32_t_push(store->stage_sysid[stage_int], system_id);
    DynArray_SystemFunc_push(store->systems, system);
}

void systemstore_run(SystemStore *store, enum SystemStage stage) {
    DynArray(uint32_t) *system_ids = store->stage_sysid[(int)stage];
    for (size_t i = 0; i < system_ids->count; ++i) {
        SystemFunc system = DynArray_SystemFunc_get(
            store->systems, DynArray_uint32_t_get(system_ids, i));
        system();
    }
}
