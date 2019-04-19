#pragma once

#include "./set.h"

#define NH_SET_STR(name)                                                       \
	NH_SET(name, char*, kh_str_hash_func, kh_str_hash_equal)

NH_SET_STR(nh_set_str)
