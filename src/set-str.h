#pragma once

#include "./set.h"

#define NH_SET_STR_CUSTOM_NAME(key_name) \
  NH_SET_CUSTOM_NAME(char*, key_name, kh_str_hash_func, kh_str_hash_equal)

NH_SET_STR_CUSTOM_NAME(str)
