#pragma once

#include "./hash.h"

/**
 * Declare structs and functions for a specific Set<?>.
 *
 * @param name name to use for the type to be declared
 * @param elem_type element type
 */
#define NH_SET_PROTO(name, elem_type)                                          \
	__KHASH_TYPE(name, elem_type, char);                                   \
                                                                               \
	_NH_HASH_BASE_PROTO(name, elem_type);                                  \
                                                                               \
	bool name##_add(name* t, elem_type elem);

/**
 * Implement functions for a specific Set<?>.
 *
 * @param name name to use for the type to be declared
 * @param elem_type element type
 * @param fn_hash macro or function that generates a hash when called with an
 * element
 * @param fn_equals macro or function that checks whether two elements are equal
 */
#define NH_SET_IMPL(name, elem_type, fn_hash, fn_equals)                       \
	__KHASH_IMPL(name, static kh_inline klib_unused, elem_type, char, 0,   \
		     fn_hash, fn_equals)                                       \
                                                                               \
	_NH_HASH_BASE_IMPL(name, elem_type);                                   \
                                                                               \
	bool name##_add(name* t, elem_type elem)                               \
	{                                                                      \
		int absent;                                                    \
		kh_put(name, t, elem, &absent);                                \
		return absent;                                                 \
	}
