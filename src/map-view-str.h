#pragma once

#include "./map.h"
#include "./view-str.h"

/**
 * Internal macro. Declare structs and functions for a specific Map<View<char>,
 * ?>, and helper functions for using char arrays as keys directly.
 *
 * @param name name to use for the type to be declared
 * @param value_type value type
 * @param default_value expression evaluated when a default value is needed
 * @param fn_hash macro or function that generates a hash when called with a key
 * @param fn_equals macro or function that checks whether two keys are equal
 */
#define _NH_MAP_VIEW_STR_IMPL(name, value_type, default_value, fn_hash,        \
			      fn_equals)                                       \
	NH_MAP(name, nh_view_str*, value_type, default_value, fn_hash,         \
	       fn_equals)                                                      \
                                                                               \
	value_type name##_get_whole_array(name* map, char* array,              \
					  size_t array_length)                 \
	{                                                                      \
		return name##_get(                                             \
			map, nh_view_str_of_whole_array(array, array_length)); \
	}                                                                      \
                                                                               \
	value_type name##_get_or_default_whole_array(                          \
		name* map, char* array, size_t array_length, value_type d)     \
	{                                                                      \
		return name##_get_or_default(                                  \
			map, nh_view_str_of_whole_array(array, array_length),  \
			d);                                                    \
	}                                                                      \
                                                                               \
	void name##_set_whole_array(name* map, char* array,                    \
				    size_t array_length, value_type v)         \
	{                                                                      \
		name##_set(map,                                                \
			   nh_view_str_of_whole_array(array, array_length),    \
			   v);                                                 \
	}                                                                      \
                                                                               \
	bool name##_has_whole_array(name* map, char* array,                    \
				    size_t array_length)                       \
	{                                                                      \
		return name##_has(                                             \
			map, nh_view_str_of_whole_array(array, array_length)); \
	}                                                                      \
                                                                               \
	bool name##_delete_whole_array(name* map, char* array,                 \
				       size_t array_length)                    \
	{                                                                      \
		return name##_delete(                                          \
			map, nh_view_str_of_whole_array(array, array_length)); \
	}

/**
 * Declare structs and functions for a specific Map<View<char>, ?>.
 *
 * @param name name to use for the type to be declared
 * @param value_type value type
 * @param default_value expression evaluated when a default value is needed
 */
#define NH_MAP_VIEW_STR(name, value_type, default_value)                       \
	_NH_MAP_VIEW_STR_IMPL(name, value_type, default_value,                 \
			      nh_view_str_hash, nh_view_str_equals)

/**
 * Declare structs and functions for a specific case-insensitive Map<View<char>,
 * ?> that ignores case for keys.
 *
 * @param name name to use for the type to be declared
 * @param value_type value type
 * @param default_value expression evaluated when a default value is needed
 */
#define NH_MAP_VIEW_ISTR(name, value_type, default_value)                      \
	_NH_MAP_VIEW_STR_IMPL(name, value_type, default_value,                 \
			      nh_view_str_hash_i, nh_view_str_equals_i)
