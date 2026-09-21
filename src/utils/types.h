#ifndef HARMONIA_TYPES
#define HARMONIA_TYPES

#include "dense.h"
#include "dyn_array.h"

#include <stdint.h>

typedef void* voidptr;

DEFINE_DENSE(uint32_t);
DEFINE_DENSE(voidptr);

DEFINE_DYN_ARRAY(uint32_t);

#endif // !HARMONIA_TYPES
