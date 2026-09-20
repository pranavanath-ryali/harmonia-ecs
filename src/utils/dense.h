#ifndef UTILS_DENSE
#define UTILS_DENSE

#include <stdio.h>
#include <stdlib.h>

// Two-level macro expansion ensures aliases and types expand fully before
// pasting
#define DENSE_CONCAT_IMPL(A, B) A##_##B
#define DENSE_CONCAT(A, B) DENSE_CONCAT_IMPL(A, B)

// Clean type constructor syntax: Dense(u32) -> Dense_u32
#define Dense(T) DENSE_CONCAT(Dense, T)

#define DEFINE_DENSE(T)                                                        \
    typedef struct {                                                           \
        T *data;                                                               \
        size_t capacity;                                                       \
        T sentinal;                                                            \
    } Dense(T);                                                                \
                                                                               \
    static inline Dense(T) * DENSE_CONCAT(Dense(T), create)(T sentinal) {      \
        Dense(T) *arr = malloc(sizeof(Dense(T)));                              \
                                                                               \
        if (!arr)                                                              \
            return NULL;                                                       \
                                                                               \
        arr->capacity = 2;                                                     \
        arr->sentinal = sentinal;                                              \
        arr->data = malloc(2 * sizeof(T));                                     \
                                                                               \
        if (!arr->data) {                                                      \
            free(arr);                                                         \
            return NULL;                                                       \
        }                                                                      \
                                                                               \
        arr->data[0] = sentinal;                                               \
        arr->data[1] = sentinal;                                               \
                                                                               \
        return arr;                                                            \
    }                                                                          \
                                                                               \
    static inline void DENSE_CONCAT(Dense(T), free)(Dense(T) * arr) {          \
        if (!arr)                                                              \
            return;                                                            \
        free(arr->data);                                                       \
        free(arr);                                                             \
    }                                                                          \
                                                                               \
    static inline void DENSE_CONCAT(Dense(T), add)(Dense(T) * arr, size_t key, \
                                                   T value) {                  \
        if (key >= arr->capacity) {                                            \
            size_t old_capacity = arr->capacity;                               \
                                                                               \
            while (key >= arr->capacity) {                                     \
                arr->capacity *= 2;                                            \
            }                                                                  \
                                                                               \
            arr->data = realloc(arr->data, arr->capacity * sizeof(T));         \
            if (!arr->data) {                                                  \
                fprintf(stderr,                                                \
                        "ERROR: Memory reallocation failed in dense_add\n");   \
                abort();                                                       \
            }                                                                  \
            for (size_t i = old_capacity; i < arr->capacity; ++i) {            \
                arr->data[i] = arr->sentinal;                                  \
            }                                                                  \
        }                                                                      \
        arr->data[key] = value;                                                \
    }                                                                          \
                                                                               \
    static inline T DENSE_CONCAT(Dense(T), get)(Dense(T) * arr, size_t key) {  \
        if (key >= arr->capacity) {                                            \
            return arr->sentinal;                                              \
        }                                                                      \
        return arr->data[key];                                                 \
    }                                                                          \
                                                                               \
    static inline void DENSE_CONCAT(Dense(T), pop)(Dense(T) * arr,             \
                                                   size_t key) {               \
        if (key < arr->capacity) {                                             \
            arr->data[key] = arr->sentinal;                                    \
        }                                                                      \
    }

#endif // UTILS_DENSE
