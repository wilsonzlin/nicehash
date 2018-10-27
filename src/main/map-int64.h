#pragma once

#include <stdint.h>
#include "./map.h"

#define NH_MAP_INT64(value_name, value_t) \
  NH_BASE(INT64, nh_map_int64_##value_name, int64_t, value_t)
