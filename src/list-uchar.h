#pragma once

#include "./list.h"
#include "./util.h"
#include <stdint.h>
#include <string.h>

#define NH_LIST_UCHAR_PROTO(name)                                              \
	NH_LIST_PROTO(name, int32_t)                                           \
                                                                               \
	int name##_compare_char_array(name* a, char* b);

#define NH_LIST_UCHAR_IMPL(name)                                               \
	NH_LIST_IMPL(name, int32_t, -1)                                        \
	NH_LIST_DEFAULT_COMPARE_IMPL(name, int32_t)                            \
                                                                               \
	int name##_compare_char_array(name* a, char* b)                        \
	{                                                                      \
		for (size_t i = 0; true; i++) {                                \
			int32_t a1 = name##_get(a, i);                         \
			uint8_t b1 = b[i];                                     \
                                                                               \
			/* Check this first, as this is technically a1 < b1.   \
			 */                                                    \
			if (a1 == -1 && b1 == 0) {                             \
				return 0;                                      \
			}                                                      \
                                                                               \
			if (a1 < b1) {                                         \
				return -1;                                     \
			}                                                      \
                                                                               \
			if (a1 > b1) {                                         \
				return 1;                                      \
			}                                                      \
		}                                                              \
	}

NH_LIST_UCHAR_PROTO(nh_list_uchar)
