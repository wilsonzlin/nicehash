#ifndef _HDR_NICEHASH_COMMON_SET
#define _HDR_NICEHASH_COMMON_SET

#include "common.h"

#define NICEHASH_CREATE_SET_INFRA(khcode, name, type_t) \
  KHASH_SET_INIT_##khcode(name) \
  \
  NICEHASH_CREATE_COMMON_INFRA(name, type_t) \
  \
  void name##_add(name##_t t, type_t elem) { \
    int absent; \
    khint_t bucket = kh_put(name, t, elem, &absent); \
  }

#endif // _HDR_NICEHASH_COMMON_SET
