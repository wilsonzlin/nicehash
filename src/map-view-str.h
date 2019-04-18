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
		nh_view_str_hash, nh_view_str_equals)                          \
                                                                               \
	value_type nh_map_##key_name##_##value_name##_get_whole_array(         \
		nh_map_##key_name##_##value_name* map, char* array,            \
		size_t array_length)                                           \
	{                                                                      \
		return nh_map_##key_name##_##value_name##_get(                 \
			map, nh_view_str_of_whole_array(array, array_length)); \
	}                                                                      \
                                                                               \
	value_type                                                             \
		nh_map_##key_name##_##value_name##_get_or_default_whole_array( \
			nh_map_##key_name##_##value_name* map, char* array,    \
			size_t array_length, value_type d)                     \
	{                                                                      \
		return nh_map_##key_name##_##value_name##_get_or_default(      \
			map, nh_view_str_of_whole_array(array, array_length),  \
			d);                                                    \
	}                                                                      \
                                                                               \
	void nh_map_##key_name##_##value_name##_set_whole_array(               \
		nh_map_##key_name##_##value_name* map, char* array,            \
		size_t array_length, value_type v)                             \
	{                                                                      \
		nh_map_##key_name##_##value_name##_set(                        \
			map, nh_view_str_of_whole_array(array, array_length),  \
			v);                                                    \
	}                                                                      \
                                                                               \
	bool nh_map_##key_name##_##value_name##_has_whole_array(               \
		nh_map_##key_name##_##value_name* map, char* array,            \
		size_t array_length)                                           \
	{                                                                      \
		return nh_map_##key_name##_##value_name##_has(                 \
			map, nh_view_str_of_whole_array(array, array_length)); \
	}                                                                      \
                                                                               \
	bool nh_map_##key_name##_##value_name##_delete_whole_array(            \
		nh_map_##key_name##_##value_name* map, char* array,            \
		size_t array_length)                                           \
	{                                                                      \
		return nh_map_##key_name##_##value_name##_delete(              \
			map, nh_view_str_of_whole_array(array, array_length)); \
	}

#define nh_map_view_str_get_whole_literal(value_name, map, str)                \
	nh_map_view_str_##value_name##_get_whole_array(map, str,               \
						       sizeof(str) - 1)

#define nh_map_view_str_get_or_default_whole_literal(value_name, map, str, d)  \
	nh_map_view_str_##value_name##_get_or_default_whole_array(             \
		map, str, sizeof(str) - 1, d)

#define nh_map_view_str_set_whole_literal(value_name, map, str, v)             \
	nh_map_view_str_##value_name##_set_whole_array(map, str,               \
						       sizeof(str) - 1, v)

#define nh_map_view_str_has_whole_literal(value_name, map, str)                \
	nh_map_view_str_##value_name##_has_whole_array(map, str,               \
						       sizeof(str) - 1)

#define nh_map_view_str_delete_whole_literal(value_name, map, str)             \
	nh_map_view_str_##value_name##_delete_whole_array(map, str,            \
							  sizeof(str) - 1)
