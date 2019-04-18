#pragma once

#include <string.h>
#include "../lib/khash.h"
#include "./view.h"

NH_VIEW(char, str)

#define nh_view_str_of_whole_literal(str)                                      \
	nh_view_str_of_whole_array(str, sizeof(str) - 1)

#define nh_view_str_compare_literal(view, str)                                 \
	nh_view_str_compare_array(view, str, sizeof(str) - 1)

#define nh_view_str_compare_literal_i(view, str)                               \
	nh_view_str_compare_array_i(view, str, sizeof(str) - 1)

#define nh_view_str_equals_literal(view, str)                                  \
	nh_view_str_equals_array(view, str, sizeof(str) - 1)

#define nh_view_str_equals_literal_i(view, str)                                \
	nh_view_str_equals_array_i(view, str, sizeof(str) - 1)

int nh_view_str_compare_array_i(nh_view_str* view, char* other,
				size_t other_length)
{
	int len_cmp = nh_util_compare_integers(view->length, other_length);
	if (len_cmp != 0) {
		return len_cmp;
	}
	return strncasecmp(&view->array[view->start], other, view->length);
}

int nh_view_str_compare_i(nh_view_str* view, nh_view_str* other)
{
	return nh_view_str_compare_array_i(view, other->array, other->length);
}

bool nh_view_str_equals_array_i(nh_view_str* view, char* other,
				size_t other_length)
{
	return nh_view_str_compare_array_i(view, other, other_length) == 0;
}

bool nh_view_str_equals_i(nh_view_str* view, nh_view_str* other)
{
	return nh_view_str_compare_i(view, other) == 0;
}

// Based on khash.h string hash function.
int nh_view_str_hash(nh_view_str* view)
{
	if (nh_view_str_is_invalid(view))
		return 0;
	int hash = 0;
	for (size_t i = view->start; i <= view->end; i++) {
		hash = (hash << 5) - hash + (int) view->array[i];
	}
	return hash;
}
