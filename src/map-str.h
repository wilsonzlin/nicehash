#pragma once

#include "./map.h"

/**
 * Declare structs and functions for a specific Map<char*, ?>.
 * The name of the type will be `nh_map_str_{value_name}`.
 *
 * @param value_type value type
 * @param value_name name of the value type
 * @param default_value expression evaluated when a default value is needed
 */
#define NH_MAP_STR(value_type, value_name, default_value)                      \
	NH_MAP(char*, str, value_type, value_name, default_value,              \
	       kh_str_hash_func, kh_str_hash_equal)
