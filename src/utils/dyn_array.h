#ifndef UTILS_DYN_ARRAY
#define UTILS_DYN_ARRAY

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define DYN_ARRAY_CONCAT_IMPL(A, B) A##_##B
#define DYN_ARRAY_CONCAT(A, B) DYN_ARRAY_CONCAT_IMPL(A, B)

#define DynArray(T) DYN_ARRAY_CONCAT(DynArray, T)

#define DEFINE_DYN_ARRAY(T)                                                    \
    typedef struct {                                                           \
        T *data;                                                               \
        size_t count;                                                          \
        size_t capacity;                                                       \
    } DynArray(T);                                                             \
                                                                               \
    static inline DynArray(T) * DYN_ARRAY_CONCAT(DynArray(T), create)() {      \
        DynArray(T) *arr = malloc(sizeof(DynArray(T)));                        \
                                                                               \
        if (!arr)                                                              \
            return NULL;                                                       \
                                                                               \
        arr->count = 0;                                                        \
        arr->capacity = 2;                                                     \
        arr->data = malloc(2 * sizeof(T));                                     \
                                                                               \
        if (!arr->data)                                                        \
            return NULL;                                                       \
                                                                               \
        return arr;                                                            \
    }                                                                          \
                                                                               \
    static inline void DYN_ARRAY_CONCAT(DynArray(T), push)(DynArray(T) * arr,     \
                                                           T value) {          \
        if (arr->count == arr->capacity) {                                     \
            arr->capacity *= 2;                                                \
            arr->data = realloc(arr->data, arr->capacity * sizeof(T));         \
                                                                               \
            if (!arr->data) {                                                  \
                fprintf(stderr,                                                \
                        "ERROR: DynArray data reallocation failed.\n");        \
                abort();                                                       \
            }                                                                  \
        }                                                                      \
                                                                               \
        arr->data[arr->count++] = value;                                       \
    }                                                                          \
                                                                               \
    static inline void DYN_ARRAY_CONCAT(DynArray(T), write_at)(                \
        DynArray(T) * arr, size_t index, T value) {                               \
        if (index >= arr->count) {                                             \
            return;                                                            \
        }                                                                      \
                                                                               \
        arr->data[index] = value;                                              \
    }                                                                          \
                                                                               \
    static inline T DYN_ARRAY_CONCAT(DynArray(T), pop)(DynArray(T) * arr) {    \
        if (arr->count == 0) {                                                 \
            fprintf(stderr, "ERROR: No value in DynArray");                    \
            abort();                                                           \
        }                                                                      \
                                                                               \
        return arr->data[--arr->count];                                        \
    }                                                                          \
                                                                               \
    static inline T DYN_ARRAY_CONCAT(DynArray(T), get)(DynArray(T) * arr,      \
                                                       size_t index) {         \
        if (index >= arr->count) {                                             \
            fprintf(stderr, "ERROR: DynArray index out of range.");            \
            abort();                                                           \
        }                                                                      \
                                                                               \
        return arr->data[index];                                               \
    }

#endif // UTILS_DYN_ARRAY
