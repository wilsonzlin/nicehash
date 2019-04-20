#pragma once

#include "./hash.h"

/**
 * Declare structs and functions for a specific Map<?, ?>.
 *
 * @param name name to use for the type to be declared
 * @param key_type key type
 * @param value_type value type
 */
#define NH_MAP_PROTO(name, key_type, value_type)                               \
	__KHASH_TYPE(name, key_type, value_type);                              \
                                                                               \
	_NH_HASH_BASE_PROTO(name, key_type);                                   \
                                                                               \
	value_type name##_get(name* t, key_type k);                            \
                                                                               \
	value_type name##_get_or_default(name* t, key_type k, value_type d);   \
                                                                               \
	void name##_set(name* t, key_type k, value_type v);

/**
 * Implement functions for a specific Map<?, ?>.
 *
 * @param name name to use for the type to be declared
 * @param key_type key type
 * @param value_type value type
 * @param default_value expression evaluated when a default value is needed
 * @param fn_hash macro or function that generates a hash when called with a key
 * @param fn_equals macro or function that checks whether two keys are equal
 */
#define NH_MAP_IMPL(name, key_type, value_type, default_value, fn_hash,        \
		    fn_equals)                                                 \
	__KHASH_IMPL(name, static kh_inline klib_unused, key_type, value_type, \
		     1, fn_hash, fn_equals)                                    \
                                                                               \
	_NH_HASH_BASE_IMPL(name, key_type);                                    \
                                                                               \
	value_type name##_get(name* t, key_type k)                             \
	{                                                                      \
		khint_t bucket = kh_get(name, t, k);                           \
		if (bucket == kh_end(t))                                       \
			return default_value;                                  \
                                                                               \
		return kh_value(t, bucket);                                    \
	}                                                                      \
                                                                               \
	value_type name##_get_or_default(name* t, key_type k, value_type d)    \
	{                                                                      \
		khint_t bucket = kh_get(name, t, k);                           \
		if (bucket == kh_end(t))                                       \
			return d;                                              \
                                                                               \
		return kh_value(t, bucket);                                    \
	}                                                                      \
                                                                               \
	void name##_set(name* t, key_type k, value_type v)                     \
	{                                                                      \
		int absent;                                                    \
		khint_t bucket = kh_put(name, t, k, &absent);                  \
		kh_value(t, bucket) = v;                                       \
	}
