#pragma once

#include <stdint.h>
#include "./map.h"

/**
 * Declare structs and functions for a specific Map<int64_t, ?>.
 *
 * @param name name to use for the type to be declared
 * @param value_type value type
 * @param default_value expression evaluated when a default value is needed
 */
#define NH_MAP_INT64(name, value_type, default_value)                          \
	NH_MAP(name, int64_t, value_type, default_value, kh_int64_hash_func,   \
	       kh_int64_hash_equal)
