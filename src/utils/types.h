#ifndef HARMONIA_TYPES
#define HARMONIA_TYPES

#include "sparse.h"
#include "dyn_array.h"

#include <stdint.h>

typedef void* voidptr;

DEFINE_SPARSE(uint32_t);
DEFINE_SPARSE(voidptr);

DEFINE_DYN_ARRAY(uint32_t);

#endif // !HARMONIA_TYPES
