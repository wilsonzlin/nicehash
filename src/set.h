#pragma once

#include "./hash.h"

/**
 * Internal macro. Declare structs and functions for a specific Set<?>.
 *
 * @param name name of type to be declared
 * @param elem_type element type
 * @param fn_hash macro or function that generates a hash when called with an
 * element
 * @param fn_equals macro or function that checks whether two elements are equal
 */
#define _NH_SET_IMPL(name, elem_type, fn_hash, fn_equals)                      \
	KHASH_INIT(name, elem_type, char, 0, fn_hash, fn_equals);              \
                                                                               \
	_NH_HASH_BASE_IMPL(name, elem_type);                                   \
                                                                               \
	bool name##_add(name* t, elem_type elem)                               \
	{                                                                      \
		int absent;                                                    \
		kh_put(name, t, elem, &absent);                                \
		return absent;                                                 \
	}

/**
 * Declare structs and functions for a specific Set<?>.
 * The name of the type will be `nh_set_{elem_name}`.
 *
 * @param elem_type element type
 * @param elem_name name of element type
 * @param fn_hash macro or function that generates a hash when called with an
 * element
 * @param fn_equals macro or function that checks whether two elements are equal
 */
#define NH_SET(elem_type, elem_name, fn_hash, fn_equals)                       \
	_NH_SET_IMPL(nh_set_##elem_name, elem_type, fn_hash, fn_equals)
