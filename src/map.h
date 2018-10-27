#pragma once

#include "./hash.h"

#define NH_MAP(khcode, name, key_t, value_t) \
  KHASH_MAP_INIT_##khcode(name, value_t) \
  \
  NH_HASH_BASE(name, key_t) \
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
