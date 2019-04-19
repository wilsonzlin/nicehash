#pragma once

#include "./map.h"
#include <stdint.h>

/**
 * Declare structs and functions for a specific Map<int32_t, ?>.
 *
 * @param name name to use for the type to be declared
 * @param value_type value type
 * @param default_value expression evaluated when a default value is needed
 */
#define NH_MAP_INT32(name, value_type, default_value)                          \
	NH_MAP(name, int32_t, value_type, default_value, kh_int_hash_func,     \
	       kh_int_hash_equal)
