#pragma once

#include <stdint.h>
#include "./set.h"

#define NH_SET_INT64_CUSTOM_NAME(key_name)                                     \
	NH_SET_CUSTOM_NAME(int64_t, key_name, kh_int64_hash_func,              \
			   kh_int64_hash_equal)

NH_SET_INT64_CUSTOM_NAME(int64)
