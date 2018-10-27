#pragma once

#include <stdbool.h>
#include "../lib/khash.h"

#define NH_HASH_BASE(name, key_t) \
  typedef khash_t(name) * name##_t; \
  \
  name##_t name##_create(void) { \
    name##_t t = kh_init(name); \
    return t; \
  } \
  \
  void name##_destroy(name##_t t) { \
    kh_destroy(name, t); \
  } \
  \
  bool name##_has(name##_t t, key_t elem) { \
    khint_t bucket = kh_get(name, t, elem); \
    return bucket != kh_end(t); \
  } \
  \
  bool name##_delete(name##_t t, key_t elem) { \
    khint_t bucket = kh_get(name, t, elem); \
    if (bucket != kh_end(t)) { \
      kh_del(name, t, bucket); \
      return true; \
    } \
    return false; \
  } \
  \
  void name##_clear(name##_t t) { \
    for (khint_t bucket = kh_begin(t); bucket != kh_end(t); ++bucket) { \
      if (kh_exist(t, bucket)) { \
        kh_del(name, t, bucket); \
      } \
    } \
  }
