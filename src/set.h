#pragma once

#include "./hash.h"

/**
 * Declare structs and functions for a specific Set<?>.
 *
 * @param name name to use for the type to be declared
 * @param elem_type element type
 * @param fn_hash macro or function that generates a hash when called with an
 * element
 * @param fn_equals macro or function that checks whether two elements are equal
 */
#define NH_SET(name, elem_type, fn_hash, fn_equals)                            \
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
