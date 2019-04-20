#pragma once

#include "./set.h"
#include <stdint.h>

#define NH_SET_INT64_PROTO(name) NH_SET_PROTO(name, int64_t)

#define NH_SET_INT64_IMPL(name)                                                \
	NH_SET_IMPL(name, int64_t, kh_int64_hash_func, kh_int64_hash_equal)

NH_SET_INT64_PROTO(nh_set_int64)
