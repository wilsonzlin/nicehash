#pragma once

#include <stdint.h>
#include "./set.h"

#define NH_SET_INT32(name)                                                     \
	NH_SET(name, int32_t, kh_int_hash_func, kh_int_hash_equal)

NH_SET_INT32(nh_set_int32)
