#pragma once

#include "./set.h"
#include "./util.h"
#include "./view-str.h"

/**
 * Internal macro. Declare structs and functions for a Set<View<char>>, and
 * helper functions for using char arrays as elements directly.
 *
 * @param name name to use for the type to be declared
 */
#define _NH_SET_VIEW_STR_PROTO(name)                                           \
	NH_SET_PROTO(name, nh_view_str*)                                       \
                                                                               \
	bool name##_add_whole_array(name* set, char* array,                    \
				    size_t array_length);                      \
                                                                               \
	bool name##_has_whole_array(name* set, char* array,                    \
				    size_t array_length);                      \
                                                                               \
	bool name##_delete_whole_array(name* set, char* array,                 \
				       size_t array_length);

/**
 * Internal macro. Implement functions for a Set<View<char>>, and
 * helper functions for using char arrays as elements directly.
 *
 * @param name name to use for the type to be declared
 * @param fn_hash macro or function that generates a hash when called with an
 * element
 * @param fn_equals macro or function that checks whether two elements are equal
 */
#define _NH_SET_VIEW_STR_IMPL(name, fn_hash, fn_equals)                        \
	NH_SET_IMPL(name, nh_view_str*, fn_hash, fn_equals)                    \
                                                                               \
	bool name##_add_whole_array(name* set, char* array,                    \
				    size_t array_length)                       \
	{                                                                      \
		return name##_add(                                             \
			set, nh_view_str_of_whole_array(array, array_length)); \
	}                                                                      \
                                                                               \
	bool name##_has_whole_array(name* set, char* array,                    \
				    size_t array_length)                       \
	{                                                                      \
		return name##_has(                                             \
			set, nh_view_str_of_whole_array(array, array_length)); \
	}                                                                      \
                                                                               \
	bool name##_delete_whole_array(name* set, char* array,                 \
				       size_t array_length)                    \
	{                                                                      \
		return name##_delete(                                          \
			set, nh_view_str_of_whole_array(array, array_length)); \
	}

#define NH_SET_VIEW_STR_PROTO(name) _NH_SET_VIEW_STR_PROTO(name)

#define NH_SET_VIEW_STR_IMPL(name)                                             \
	_NH_SET_VIEW_STR_IMPL(name, nh_view_str_hash, nh_view_str_equals)

NH_SET_VIEW_STR_PROTO(nh_set_view_str)

/**
 * Helper macro to add to a Set<View<char>> using a string literal.
 *
 * @param set set
 * @param str string literal
 */
#define nh_set_view_str_add_whole_literal(set, str)                            \
	nh_set_view_str_add_whole_array(set, nh_litarr(str))

/**
 * Helper macro to check existence in a Set<View<char>> using a string literal.
 *
 * @param set set
 * @param str string literal
 */
#define nh_set_view_str_has_whole_literal(set, str)                            \
	nh_set_view_str_has_whole_array(set, nh_litarr(str))

/**
 * Helper macro to delete from a Set<View<char>> using a string literal.
 *
 * @param set set
 * @param str string literal
 */
#define nh_set_view_str_delete_whole_literal(set, str)                         \
	nh_set_view_str_delete_whole_array(set, nh_litarr(str))

#define NH_SET_VIEW_ISTR_PROTO(name) _NH_SET_VIEW_STR_PROTO(name)

#define NH_SET_VIEW_ISTR_IMPL(name)                                            \
	_NH_SET_VIEW_STR_IMPL(name, nh_view_str_hash_i, nh_view_str_equals_i)

NH_SET_VIEW_ISTR_PROTO(nh_set_view_istr)

/**
 * Helper macro to add to a case-insensitive Set<View<char>> using a string
 * literal.
 *
 * @param set set
 * @param str string literal
 */
#define nh_set_view_istr_add_whole_literal(set, str)                           \
	nh_set_view_istr_add_whole_array(set, nh_litarr(str))

/**
 * Helper macro to check existence in a case-insensitive Set<View<char>> using a
 * string literal.
 *
 * @param set set
 * @param str string literal
 */
#define nh_set_view_istr_has_whole_literal(set, str)                           \
	nh_set_view_istr_has_whole_array(set, nh_litarr(str))

/**
 * Helper macro to delete from a case-insensitive Set<View<char>> using a string
 * literal.
 *
 * @param set set
 * @param str string literal
 */
#define nh_set_view_istr_delete_whole_literal(set, str)                        \
	nh_set_view_istr_delete_whole_array(set, nh_litarr(str))
