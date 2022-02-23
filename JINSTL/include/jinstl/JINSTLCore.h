#pragma once

#include <cassert>

#define JINSTL_ASSERT(CONDITION) assert(CONDITION)
#define JINSTL_MAX(A, B) (((A) > (B)) ? (A) : (B))
#define JINSTL_MIN(A, B) (((A) > (B)) ? (B) : (A))