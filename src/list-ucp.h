#pragma once

#include "./list.h"
#include "./util.h"
#include <stdint.h>
#include <string.h>

NH_LIST(nh_list_ucp, int32_t, -1)

NH_LIST_DEFAULT_COMPARE(nh_list_ucp, int32_t)

int nh_list_ucp_compare_char_array(nh_list_ucp* a, char* b)
{
	for (size_t i = 0; true; i++) {
		int32_t a1 = nh_list_ucp_get(a, i);
		uint8_t b1 = b[i];

		// Check this first, as this is technically a1 < b1.
		if (a1 == -1 && b1 == 0) {
			return 0;
		}

		if (a1 < b1) {
			return -1;
		}

		if (a1 > b1) {
			return 1;
		}
	}
}
