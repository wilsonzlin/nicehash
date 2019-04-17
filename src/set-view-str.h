#pragma once

#include "./set.h"
#include "./view-str.h"

#define NH_SET_VIEW_STR_CUSTOM_NAME(key_name)                                  \
	NH_SET_CUSTOM_NAME(nh_view_str*, key_name, nh_view_str_hash,           \
			   nh_view_str_equals)

NH_SET_VIEW_STR_CUSTOM_NAME(view_str)
