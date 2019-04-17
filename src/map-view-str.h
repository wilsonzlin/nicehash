#pragma once

#include "./map.h"
#include "./view-str.h"

#define NH_MAP_VIEW_STR(value_type)                                            \
	NH_MAP_VIEW_STR_CUSTOM_NAMES(view_str, value_type, value_type)

#define NH_MAP_VIEW_STR_CUSTOM_NAMES(key_name, value_type, value_name)         \
	NH_MAP_VIEW_STR_CUSTOM_NAMES_DEFAULT_VALUE(key_name, value_type,       \
						   value_name, 0)

#define NH_MAP_VIEW_STR_CUSTOM_NAMES_DEFAULT_VALUE(key_name, value_type,       \
						   value_name, default_value)  \
	NH_MAP_CUSTOM_NAMES_DEFAULT_VALUE(                                     \
		nh_view_str*, key_name, value_type, value_name, default_value, \
		nh_view_str_hash, nh_view_str_equals)
