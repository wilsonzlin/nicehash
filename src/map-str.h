#pragma once

#include "./map.h"

#define NH_MAP_STR(value_name, value_t) \
  NH_BASE(STR, nh_map_str_##value_name, char *, value_t)