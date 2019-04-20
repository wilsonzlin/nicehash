#pragma once

#include "./set.h"

#define NH_SET_STR_PROTO(name) NH_SET_PROTO(name, char*)

#define NH_SET_STR_IMPL(name)                                                  \
	NH_SET_IMPL(name, char*, kh_str_hash_func, kh_str_hash_equal)

NH_SET_STR_PROTO(nh_set_str)
