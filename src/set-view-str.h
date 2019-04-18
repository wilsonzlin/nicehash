#pragma once

#include "./set.h"
#include "./view-str.h"

#define NH_SET_VIEW_STR_CUSTOM_NAME(key_name)                                  \
	NH_SET_CUSTOM_NAME(nh_view_str*, key_name, nh_view_str_hash,           \
			   nh_view_str_equals)                                 \
                                                                               \
	bool nh_set_##key_name##_add_whole_array(                              \
		nh_set_##key_name* set, char* array, size_t array_length)      \
	{                                                                      \
		return nh_set_##key_name##_add(                                \
			set, nh_view_str_of_whole_array(array, array_length)); \
	}                                                                      \
                                                                               \
	bool nh_set_##key_name##_has_whole_array(                              \
		nh_set_##key_name* set, char* array, size_t array_length)      \
	{                                                                      \
		return nh_set_##key_name##_has(                                \
			set, nh_view_str_of_whole_array(array, array_length)); \
	}                                                                      \
                                                                               \
	bool nh_set_##key_name##_delete_whole_array(                           \
		nh_set_##key_name* set, char* array, size_t array_length)      \
	{                                                                      \
		return nh_set_##key_name##_delete(                             \
			set, nh_view_str_of_whole_array(array, array_length)); \
	}

NH_SET_VIEW_STR_CUSTOM_NAME(view_str)

#define nh_set_view_str_add_whole_literal(set, str)                            \
	nh_set_view_str_add_whole_array(set, str, sizeof(str) - 1)
#define nh_set_view_str_has_whole_literal(set, str)                            \
	nh_set_view_str_has_whole_array(set, str, sizeof(str) - 1)
#define nh_set_view_str_delete_whole_literal(set, str)                         \
	nh_set_view_str_delete_whole_array(set, str, sizeof(str) - 1)
