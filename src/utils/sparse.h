#ifndef UTILS_SPARSE
#define UTILS_SPARSE

#include <stdio.h>
#include <stdlib.h>

// Two-level macro expansion ensures aliases and types expand fully before
// pasting
#define SPARSE_CONCAT_IMPL(A, B) A##_##B
#define SPARSE_CONCAT(A, B) SPARSE_CONCAT_IMPL(A, B)

// Clean type constructor syntax: Sparse(u32) -> Sparse_u32
#define Sparse(T) SPARSE_CONCAT(Sparse, T)

#define DEFINE_SPARSE(T)                                                        \
    typedef struct {                                                           \
        T *data;                                                               \
        size_t capacity;                                                       \
        T sentinal;                                                            \
    } Sparse(T);                                                                \
                                                                               \
    static inline Sparse(T) * SPARSE_CONCAT(Sparse(T), create)(T sentinal) {      \
        Sparse(T) *arr = malloc(sizeof(Sparse(T)));                              \
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
    static inline void SPARSE_CONCAT(Sparse(T), free)(Sparse(T) * arr) {          \
        if (!arr)                                                              \
            return;                                                            \
        free(arr->data);                                                       \
        free(arr);                                                             \
    }                                                                          \
                                                                               \
    static inline void SPARSE_CONCAT(Sparse(T), add)(Sparse(T) * arr, size_t key, \
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
    static inline T SPARSE_CONCAT(Sparse(T), get)(Sparse(T) * arr, size_t key) {  \
        if (key >= arr->capacity) {                                            \
            return arr->sentinal;                                              \
        }                                                                      \
        return arr->data[key];                                                 \
    }                                                                          \
                                                                               \
    static inline void SPARSE_CONCAT(Sparse(T), pop)(Sparse(T) * arr,             \
                                                   size_t key) {               \
        if (key < arr->capacity) {                                             \
            arr->data[key] = arr->sentinal;                                    \
        }                                                                      \
    }

#endif // UTILS_SPARSE
