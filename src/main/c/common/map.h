#ifndef _HDR_NICEHASH_COMMON_MAP
#define _HDR_NICEHASH_COMMON_MAP

#include "common.h"

#define NICEHASH_CREATE_MAP_INFRA(khcode, name, key_t, value_t) \
  KHASH_MAP_INIT_##khcode(name, value_t) \
  \
  NICEHASH_CREATE_COMMON_INFRA(name, key_t) \
  \
  value_t name##_get(name##_t t, key_t k, value_t defval) { \
    khint_t bucket = kh_get(name, t, k); \
    if (bucket == kh_end(t)) return defval; \
    \
    return kh_value(t, bucket); \
  } \
  \
  void name##_set(name##_t t, key_t k, value_t v) { \
    int absent; \
    khint_t bucket = kh_put(name, t, k, &absent); \
    kh_value(t, bucket) = v; \
  }

#endif // _HDR_NICEHASH_COMMON_MAP
