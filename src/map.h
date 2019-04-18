#pragma once

#include "./hash.h"

/**
 * Internal macro. Declare structs and functions for a specific Map<?, ?>.
 *
 * @param name name of type to be declared
 * @param key_type key type
 * @param value_type value type
 * @param default_value expression evaluated when a default value is needed
 * @param fn_hash macro or function that generates a hash when called with a key
 * @param fn_equals macro or function that checks whether two keys are equal
 */
#define _NH_MAP_IMPL(name, key_type, value_type, default_value, fn_hash,       \
		     fn_equals)                                                \
	KHASH_INIT(name, key_type, value_type, 1, fn_hash, fn_equals);         \
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

/**
 * Declare structs and functions for a specific Map<?, ?>.
 * The name of the type will be `nh_map_{key_name}_{value_name}`.
 *
 * @param key_type key type
 * @param key_name name of the key type
 * @param value_type value type
 * @param value_name name of the value type
 * @param default_value expression evaluated when a default value is needed
 * @param fn_hash macro or function that generates a hash when called with a key
 * @param fn_equals macro or function that checks whether two keys are equal
 */
#define NH_MAP(key_type, key_name, value_type, value_name, default_value,      \
	       fn_hash, fn_equals)                                             \
	_NH_MAP_IMPL(nh_map_##key_name##_##value_name, key_type, value_type,   \
		     default_value, fn_hash, fn_equals)
