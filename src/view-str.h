#pragma once

#include "../lib/khash.h"
#include "./util.h"
#include "./view.h"
#include <strings.h>

#define NH_VIEW_STR(name) NH_VIEW(name, char)

NH_VIEW_STR(nh_view_str)

#define nh_view_str_of_whole_literal(str)                                      \
	nh_view_str_of_whole_array(nh_litarr(str))

#define nh_view_str_compare_literal(view, str)                                 \
	nh_view_str_compare_array(view, nh_litarr(str))

#define nh_view_str_compare_literal_i(view, str)                               \
	nh_view_str_compare_array_i(view, nh_litarr(str))

#define nh_view_str_equals_literal(view, str)                                  \
	nh_view_str_equals_array(view, nh_litarr(str))

#define nh_view_str_equals_literal_i(view, str)                                \
	nh_view_str_equals_array_i(view, nh_litarr(str))

int nh_view_str_compare_array_i(nh_view_str* view, char* other,
				size_t other_length)
{
	int len_cmp = nh_util_compare_sizes(view->length, other_length);
	if (len_cmp != 0) {
		return len_cmp;
	}
	return strncasecmp(&view->array[view->start], other, view->length);
}

int nh_view_str_compare_i(nh_view_str* view, nh_view_str* other)
{
	return nh_view_str_compare_array_i(view, &other->array[other->start],
					   other->length);
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
	int hash = 0;
	size_t end = view->start + view->length;
	for (size_t i = view->start; i < end; i++) {
		hash = (hash << 5) - hash + (int) view->array[i];
	}
	return hash;
}

// Based on khash.h string hash function.
int nh_view_str_hash_i(nh_view_str* view)
{
	int hash = 0;
	size_t end = view->start + view->length;
	for (size_t i = view->start; i < end; i++) {
		hash = (hash << 5) - hash
		       + (int) nh_util_lowercase(view->array[i]);
	}
	return hash;
}
