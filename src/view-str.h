#pragma once

#include "../lib/khash.h"
#include "./view.h"

NH_VIEW(char, str)

#define nh_view_str_of_whole_literal(str)                                      \
	nh_view_str_of_whole_array(str, sizeof(str) - 1)

// Based on khash's string hash function.
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
