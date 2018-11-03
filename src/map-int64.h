#pragma once

#include <stdint.h>
#include "./map.h"

#define NH_MAP_INT64(value_name, value_t, defsafe_value_t, default_value) \
  NH_MAP(INT64, nh_map_int64_##value_name, int64_t, value_t, defsafe_value_t, default_value)
