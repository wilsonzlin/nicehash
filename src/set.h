#pragma once

#include "./hash.h"

#define NH_SET(khcode, name, type_t)                                           \
	KHASH_SET_INIT_##khcode(name);                                         \
                                                                               \
	NH_HASH_BASE(name, type_t);                                            \
                                                                               \
	void name##_add(name* t, type_t elem)                                  \
	{                                                                      \
		int absent;                                                    \
		kh_put(name, t, elem, &absent);                                \
	}
