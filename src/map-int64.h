#pragma once

#include "./map.h"
#include <stdint.h>

/**
 * Declare structs and functions for a specific Map<int64_t, ?>.
 *
 * @param name name to use for the type to be declared
 * @param value_type value type
 */
#define NH_MAP_INT64_PROTO(name, value_type)                                   \
	NH_MAP_PROTO(name, int64_t, value_type)

/**
 * Implement functions for a specific Map<int64_t, ?>.
 *
 * @param name name to use for the type to be declared
 * @param value_type value type
 * @param default_value expression evaluated when a default value is needed
 */
#define NH_MAP_INT64_IMPL(name, value_type, default_value)                     \
	NH_MAP_IMPL(name, int64_t, value_type, default_value,                  \
		    kh_int64_hash_func, kh_int64_hash_equal)
