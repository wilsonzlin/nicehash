#pragma once

#include "./map.h"
#include "./view-str.h"

/**
 * Internal macro. Declare structs and functions for a specific Map<View<char>,
 * ?>, and helper functions for using char arrays directly as keys.
 *
 * @param value_type value type
 * @param value_name name of the value type
 * @param default_value expression evaluated when a default value is needed
 * @param fn_hash macro or function that generates a hash when called with a key
 * @param fn_equals macro or function that checks whether two values are equal
 */
#define _NH_MAP_VIEW_STR_IMPL(value_type, value_name, default_value, fn_hash,  \
			      fn_equals)                                       \
	NH_MAP(nh_view_str*, view_str, value_type, value_name, default_value,  \
	       fn_hash, fn_equals)                                             \
                                                                               \
	value_type nh_map_view_str_##value_name##_get_whole_array(             \
		nh_map_view_str_##value_name* map, char* array,                \
		size_t array_length)                                           \
	{                                                                      \
		return nh_map_view_str_##value_name##_get(                     \
			map, nh_view_str_of_whole_array(array, array_length)); \
	}                                                                      \
                                                                               \
	value_type nh_map_view_str_##value_name##_get_or_default_whole_array(  \
		nh_map_view_str_##value_name* map, char* array,                \
		size_t array_length, value_type d)                             \
	{                                                                      \
		return nh_map_view_str_##value_name##_get_or_default(          \
			map, nh_view_str_of_whole_array(array, array_length),  \
			d);                                                    \
	}                                                                      \
                                                                               \
	void nh_map_view_str_##value_name##_set_whole_array(                   \
		nh_map_view_str_##value_name* map, char* array,                \
		size_t array_length, value_type v)                             \
	{                                                                      \
		nh_map_view_str_##value_name##_set(                            \
			map, nh_view_str_of_whole_array(array, array_length),  \
			v);                                                    \
	}                                                                      \
                                                                               \
	bool nh_map_view_str_##value_name##_has_whole_array(                   \
		nh_map_view_str_##value_name* map, char* array,                \
		size_t array_length)                                           \
	{                                                                      \
		return nh_map_view_str_##value_name##_has(                     \
			map, nh_view_str_of_whole_array(array, array_length)); \
	}                                                                      \
                                                                               \
	bool nh_map_view_str_##value_name##_delete_whole_array(                \
		nh_map_view_str_##value_name* map, char* array,                \
		size_t array_length)                                           \
	{                                                                      \
		return nh_map_view_str_##value_name##_delete(                  \
			map, nh_view_str_of_whole_array(array, array_length)); \
	}

/**
 * Declare structs and functions for a specific Map<View<char>, ?>.
 * The name of the type will be `nh_map_view_str_{value_name}`.
 *
 * @param value_type value type
 * @param value_name name of the value type
 * @param default_value expression evaluated when a default value is needed
 */
#define NH_MAP_VIEW_STR(value_type, value_name, default_value)                 \
	_NH_MAP_VIEW_STR_IMPL(value_type, value_name, default_value,           \
			      nh_view_str_hash, nh_view_str_equals)

/**
 * Helper macro to get using a string literal for a specific Map<View<char>, ?>.
 * The name of the value type of the map must be provided.
 *
 * @param value_name name of the value type
 * @param map map
 * @param str string literal
 */
#define nh_map_view_str_get_whole_literal(value_name, map, str)                \
	nh_map_view_str_##value_name##_get_whole_array(map, str,               \
						       sizeof(str) - 1)

/**
 * Helper macro to get using a string literal for a specific Map<View<char>, ?>,
 * returning a default value if the key doesn't exist.
 * The name of the value type of the map must be provided.
 *
 * @param value_name name of the value type
 * @param map map
 * @param str string literal
 * @param d default value
 */
#define nh_map_view_str_get_or_default_whole_literal(value_name, map, str, d)  \
	nh_map_view_str_##value_name##_get_or_default_whole_array(             \
		map, str, sizeof(str) - 1, d)

/**
 * Helper macro to set using a string literal for a specific Map<View<char>, ?>.
 * The name of the value type of the map must be provided.
 *
 * @param value_name name of the value type
 * @param map map
 * @param str string literal
 * @param v value to set
 */
#define nh_map_view_str_set_whole_literal(value_name, map, str, v)             \
	nh_map_view_str_##value_name##_set_whole_array(map, str,               \
						       sizeof(str) - 1, v)

/**
 * Helper macro to check existence using a string literal for a specific
 * Map<View<char>, ?>. The name of the value type of the map must be provided.
 *
 * @param value_name name of the value type
 * @param map map
 * @param str string literal
 */
#define nh_map_view_str_has_whole_literal(value_name, map, str)                \
	nh_map_view_str_##value_name##_has_whole_array(map, str,               \
						       sizeof(str) - 1)

/**
 * Helper macro to delete using a string literal for a specific Map<View<char>,
 * ?>. The name of the value type of the map must be provided.
 *
 * @param value_name name of the value type
 * @param map map
 * @param str string literal
 */
#define nh_map_view_str_delete_whole_literal(value_name, map, str)             \
	nh_map_view_str_##value_name##_delete_whole_array(map, str,            \
							  sizeof(str) - 1)

/**
 * Declare structs and functions for a specific case-insensitive Map<View<char>,
 * ?> that ignores case for keys. The name of the type will be
 * `nh_map_view_istr_{value_name}`.
 *
 * @param value_type value type
 * @param value_name name of the value type
 * @param default_value expression evaluated when a default value is needed
 */
#define NH_MAP_VIEW_ISTR(value_type, value_name, default_value)                \
	_NH_MAP_VIEW_STR_IMPL(value_type, value_name, default_value,           \
			      nh_view_str_hash_i, nh_view_str_equals_i)

/**
 * Helper macro to get using a string literal for a specific case-insensitive
 * Map<View<char>, ?>. The name of the value type of the map must be provided.
 *
 * @param value_name name of the value type
 * @param map map
 * @param str string literal
 */
#define nh_map_view_istr_get_whole_literal(value_name, map, str)               \
	nh_map_view_istr_##value_name##_get_whole_array(map, str,              \
							sizeof(str) - 1)
/**
 * Helper macro to get using a string literal for a specific case-insensitive
 * Map<View<char>, ?>, returning a default value if the key doesn't exist. The
 * name of the value type of the map must be provided.
 *
 * @param value_name name of the value type
 * @param map map
 * @param str string literal
 * @param d default value
 */
#define nh_map_view_istr_get_or_default_whole_literal(value_name, map, str, d) \
	nh_map_view_istr_##value_name##_get_or_default_whole_array(            \
		map, str, sizeof(str) - 1, d)

/**
 * Helper macro to set using a string literal for a specific case-insensitive
 * Map<View<char>, ?>. The name of the value type of the map must be provided.
 *
 * @param value_name name of the value type
 * @param map map
 * @param str string literal
 * @param v value to set
 */
#define nh_map_view_istr_set_whole_literal(value_name, map, str, v)            \
	nh_map_view_istr_##value_name##_set_whole_array(map, str,              \
							sizeof(str) - 1, v)

/**
 * Helper macro to check existence using a string literal for a specific
 * case-insensitive Map<View<char>, ?>. The name of the value type of the map
 * must be provided.
 *
 * @param value_name name of the value type
 * @param map map
 * @param str string literal
 */
#define nh_map_view_istr_has_whole_literal(value_name, map, str)               \
	nh_map_view_istr_##value_name##_has_whole_array(map, str,              \
							sizeof(str) - 1)

/**
 * Helper macro to delete using a string literal for a specific case-insensitive
 * Map<View<char>, ?>. The name of the value type of the map must be provided.
 *
 * @param value_name name of the value type
 * @param map map
 * @param str string literal
 */
#define nh_map_view_istr_delete_whole_literal(value_name, map, str)            \
	nh_map_view_istr_##value_name##_delete_whole_array(map, str,           \
							   sizeof(str) - 1)
