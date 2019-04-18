#pragma once

#include <stdint.h>
#include "./map.h"

/**
 * Declare structs and functions for a specific Map<int64_t, ?>.
 * The name of the type will be `nh_map_int64_{value_name}`.
 *
 * @param value_type value type
 * @param value_name name of the value type
 * @param default_value expression evaluated when a default value is needed
 */
#define NH_MAP_INT64(value_type, value_name, default_value)                    \
	NH_MAP(int64_t, int64, value_type, value_name, default_value,          \
	       kh_int64_hash_func, kh_int64_hash_equal)
