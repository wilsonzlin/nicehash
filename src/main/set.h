#pragma once

#include "common.h"

#define NH_SET(khcode, name, type_t) \
  KHASH_SET_INIT_##khcode(name) \
  \
  NH_BASE(name, type_t) \
  \
  void name##_add(name##_t t, type_t elem) { \
    int absent; \
    kh_put(name, t, elem, &absent); \
  }
