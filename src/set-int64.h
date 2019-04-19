#pragma once

#include <stdint.h>
#include "./set.h"

#define NH_SET_INT64(name)                                                     \
	NH_SET(name, int64_t, kh_int64_hash_func, kh_int64_hash_equal)

NH_SET_INT64(nh_set_int64)
