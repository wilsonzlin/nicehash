#pragma once

#include "./map.h"

#define NH_MAP_STR(value_name, value_t, defsafe_value_t, default_value) \
  NH_MAP(STR, nh_map_str_##value_name, char*, value_t, defsafe_value_t, default_value)
