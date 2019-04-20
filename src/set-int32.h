#pragma once

#include "./set.h"
#include <stdint.h>

#define NH_SET_INT32_PROTO(name) NH_SET_PROTO(name, int32_t)

#define NH_SET_INT32_IMPL(name)                                                \
	NH_SET_IMPL(name, int32_t, kh_int_hash_func, kh_int_hash_equal)

NH_SET_INT32_PROTO(nh_set_int32)
