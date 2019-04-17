#pragma once

#include <stdint.h>
#include "./set.h"

#define NH_SET_INT32_CUSTOM_NAME(key_name)                                     \
	NH_SET_CUSTOM_NAME(int32_t, key_name, kh_int_hash_func,                \
			   kh_int_hash_equal)

NH_SET_INT32_CUSTOM_NAME(int32)
