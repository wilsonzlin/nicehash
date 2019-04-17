#pragma once

#include "./hash.h"

#define _NH_SET_IMPL(name, key_type, fn_hash, fn_equals) \
	KHASH_INIT(name, key_type, char, 0, fn_hash, fn_equals);                                \
                                                                               \
	_NH_HASH_BASE_IMPL(name, key_type);                                             \
  \
	bool name##_add(name* t, key_type elem)                                  \
	{                                                                      \
		int absent;                                                    \
		kh_put(name, t, elem, &absent);                                \
    return absent; \
	}

#define NH_SET(key_type, fn_hash, fn_equals) \
  NH_SET_CUSTOM_NAME(key_type, key_type, fn_hash, fn_equals)

#define NH_SET_CUSTOM_NAME(key_type, key_name, fn_hash, fn_equals) \
  _NH_SET_IMPL(nh_set_##key_name, key_type, fn_hash, fn_equals)
