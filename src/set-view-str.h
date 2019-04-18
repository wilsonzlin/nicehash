#pragma once

#include "./set.h"
#include "./view-str.h"

/**
 * Internal macro. Declare structs and functions for a Set<View<char>>, and
 * helper functions for using char arrays as elements directly.
 *
 * @param key_name name of the key type
 * @param fn_hash macro or function that generates a hash when called with an
 * element
 * @param fn_equals macro or function that checks whether two elements are equal
 */
#define _NH_SET_VIEW_STR_IMPL(key_name, fn_hash, fn_equals)                    \
	NH_SET(nh_view_str*, key_name, fn_hash, fn_equals)                     \
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

_NH_SET_VIEW_STR_IMPL(view_str, nh_view_str_hash, nh_view_str_equals)

/**
 * Helper macro to add to a Set<View<char>> using a string literal.
 *
 * @param set set
 * @param str string literal
 */
#define nh_set_view_str_add_whole_literal(set, str)                            \
	nh_set_view_str_add_whole_array(set, str, sizeof(str) - 1)

/**
 * Helper macro to check existence in a Set<View<char>> using a string literal.
 *
 * @param set set
 * @param str string literal
 */
#define nh_set_view_str_has_whole_literal(set, str)                            \
	nh_set_view_str_has_whole_array(set, str, sizeof(str) - 1)

/**
 * Helper macro to delete from a Set<View<char>> using a string literal.
 *
 * @param set set
 * @param str string literal
 */
#define nh_set_view_str_delete_whole_literal(set, str)                         \
	nh_set_view_str_delete_whole_array(set, str, sizeof(str) - 1)

_NH_SET_VIEW_STR_IMPL(view_istr, nh_view_str_hash_i, nh_view_str_equals_i)

/**
 * Helper macro to add to a case-insensitive Set<View<char>> using a string
 * literal.
 *
 * @param set set
 * @param str string literal
 */
#define nh_set_view_istr_add_whole_literal(set, str)                           \
	nh_set_view_istr_add_whole_array(set, str, sizeof(str) - 1)

/**
 * Helper macro to check existence in a case-insensitive Set<View<char>> using a
 * string literal.
 *
 * @param set set
 * @param str string literal
 */
#define nh_set_view_istr_has_whole_literal(set, str)                           \
	nh_set_view_istr_has_whole_array(set, str, sizeof(str) - 1)

/**
 * Helper macro to delete from a case-insensitive Set<View<char>> using a string
 * literal.
 *
 * @param set set
 * @param str string literal
 */
#define nh_set_view_istr_delete_whole_literal(set, str)                        \
	nh_set_view_istr_delete_whole_array(set, str, sizeof(str) - 1)
