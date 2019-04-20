#pragma once

#include "./map.h"

/**
 * Declare structs and functions for a specific Map<char*, ?>.
 *
 * @param name name to use for the type to be declared
 * @param value_type value type
 */
#define NH_MAP_STR_PROTO(name, value_type) NH_MAP_PROTO(name, char*, value_type)

/**
 * Implement functions for a specific Map<char*, ?>.
 *
 * @param name name to use for the type to be declared
 * @param value_type value type
 * @param default_value expression evaluated when a default value is needed
 */
#define NH_MAP_STR_IMPL(name, value_type, default_value)                       \
	NH_MAP_IMPL(name, char*, value_type, default_value, kh_str_hash_func,  \
		    kh_str_hash_equal)
