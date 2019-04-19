#pragma once

#include "./map.h"

/**
 * Declare structs and functions for a specific Map<char*, ?>.
 *
 * @param name name to use for the type to be declared
 * @param value_type value type
 * @param default_value expression evaluated when a default value is needed
 */
#define NH_MAP_STR(name, value_type, default_value)                            \
	NH_MAP(name, char*, value_type, default_value, kh_str_hash_func,       \
	       kh_str_hash_equal)
