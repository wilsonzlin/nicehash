#pragma once

#include <stdint.h>
#include "./map.h"

#define NH_MAP_INT32(value_name, value_t) \
  NH_BASE(INT, nh_map_int32_##value_name, int32_t, value_t)