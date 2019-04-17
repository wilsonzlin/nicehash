#pragma once

#include "./map.h"

#define NH_MAP_STR(value_type)                                                 \
	NH_MAP_STR_CUSTOM_NAMES(str, value_type, value_type)

#define NH_MAP_STR_CUSTOM_NAMES(key_name, value_type, value_name)              \
	NH_MAP_STR_CUSTOM_NAMES_DEFAULT_VALUE(key_name, value_type,            \
					      value_name, 0)

#define NH_MAP_STR_CUSTOM_NAMES_DEFAULT_VALUE(key_name, value_type,            \
					      value_name, default_value)       \
	NH_MAP_CUSTOM_NAMES_DEFAULT_VALUE(char*, key_name, value_type,         \
					  value_name, default_value,           \
					  kh_str_hash_func, kh_str_hash_equal)
