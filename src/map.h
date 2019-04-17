#pragma once

#include "./hash.h"

#define _NH_MAP_IMPL(name, key_type, value_type, default_value, fn_hash, fn_equals) \
	KHASH_INIT(name, key_type, value_type, 1, fn_hash, fn_equals);                                \
                                                                               \
	_NH_HASH_BASE_IMPL(name, key_type);                                             \
                                                                               \
	value_type name##_get(name* t, key_type k)                           \
	{                                                                      \
		khint_t bucket = kh_get(name, t, k);                           \
		if (bucket == kh_end(t))                                       \
			return default_value;                                  \
                                                                               \
		return kh_value(t, bucket);                                    \
	}                                                                      \
                                                                               \
	value_type name##_get_or_default(name* t, key_type k, value_type d)        \
	{                                                                      \
		khint_t bucket = kh_get(name, t, k);                           \
		if (bucket == kh_end(t))                                       \
			return d;                                         \
                                                                               \
		return kh_value(t, bucket);                                    \
	}                                                                      \
                                                                               \
	void name##_set(name* t, key_type k, value_type v)                           \
	{                                                                      \
		int absent;                                                    \
		khint_t bucket = kh_put(name, t, k, &absent);                  \
		kh_value(t, bucket) = v;                                       \
	}

#define NH_MAP(key_type, value_type, fn_hash, fn_equals) \
  NH_MAP_CUSTOM_NAMES(key_type, key_type, value_type, value_type, fn_hash, fn_equals)

#define NH_MAP_CUSTOM_NAMES(key_type, key_name, value_type, value_name, fn_hash, fn_equals) \
  NH_MAP_CUSTOM_NAMES_DEFAULT_VALUE(key_type, key_name, value_type, value_name, 0, fn_hash, fn_equals)

#define NH_MAP_CUSTOM_NAMES_DEFAULT_VALUE(key_type, key_name, value_type, value_name, default_value, fn_hash, fn_equals)   \
  _NH_MAP_IMPL(nh_map_##key_name##_##value_name, key_type, value_type, default_value, fn_hash, fn_equals)
