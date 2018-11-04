#pragma once

#include "./hash.h"

#define NH_MAP(khcode, name, key_t, value_t, defsafe_value_t, default_value)   \
	KHASH_MAP_INIT_##khcode(name, value_t);                                \
                                                                               \
	NH_HASH_BASE(name, key_t);                                             \
                                                                               \
	defsafe_value_t name##_get(name* t, key_t k)                           \
	{                                                                      \
		khint_t bucket = kh_get(name, t, k);                           \
		if (bucket == kh_end(t))                                       \
			return default_value;                                  \
                                                                               \
		return kh_value(t, bucket);                                    \
	}                                                                      \
                                                                               \
	value_t name##_get_or_default(name* t, key_t k, value_t defval)        \
	{                                                                      \
		khint_t bucket = kh_get(name, t, k);                           \
		if (bucket == kh_end(t))                                       \
			return defval;                                         \
                                                                               \
		return kh_value(t, bucket);                                    \
	}                                                                      \
                                                                               \
	void name##_set(name* t, key_t k, value_t v)                           \
	{                                                                      \
		int absent;                                                    \
		khint_t bucket = kh_put(name, t, k, &absent);                  \
		kh_value(t, bucket) = v;                                       \
	}
