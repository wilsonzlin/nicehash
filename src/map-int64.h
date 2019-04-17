#pragma once

#include <stdint.h>
#include "./map.h"

#define NH_MAP_INT64(value_type, fn_hash, fn_equals) \
  NH_MAP_INT64_CUSTOM_NAMES(int64, value_type, value_type)

#define NH_MAP_INT64_CUSTOM_NAMES(key_name, value_type, value_name) \
  NH_MAP_INT64_CUSTOM_NAMES_DEFAULT_VALUE(key_name, value_type, value_name, 0)

#define NH_MAP_INT64_CUSTOM_NAMES_DEFAULT_VALUE(key_name, value_type, value_name, default_value)   \
  NH_MAP_CUSTOM_NAMES_DEFAULT_VALUE(int64_t, key_name, value_type, value_name, default_value, kh_int64_hash_func, kh_int64_hash_equal)
