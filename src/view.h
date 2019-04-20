#pragma once

#include "./util.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/**
 * Declare structs and functions for a specific View<?>.
 * A view represents the subarray [`start`, `start` + `length`) of `array`.
 * The subarray is a pointer and not a copy, so changes to elements in the
 * subarray will affect the original array.
 *
 * @param name name to use for the type to be declared
 * @param elem_type array element type
 */
#define NH_VIEW(name, elem_type)                                               \
	typedef struct {                                                       \
		size_t start;                                                  \
		size_t length;                                                 \
		elem_type* array;                                              \
	} name;                                                                \
                                                                               \
	void name##_init(name* view, elem_type* array, size_t start,           \
			 size_t length)                                        \
	{                                                                      \
		view->array = array;                                           \
		view->start = start;                                           \
		view->length = length;                                         \
	}                                                                      \
                                                                               \
	name* name##_create(elem_type* array, size_t start, size_t length)     \
	{                                                                      \
		name* view = malloc(sizeof(name));                             \
		name##_init(view, array, start, length);                       \
		return view;                                                   \
	}                                                                      \
                                                                               \
	name* name##_of_whole_array(elem_type* array, size_t length)           \
	{                                                                      \
		return name##_create(array, 0, length);                        \
	}                                                                      \
                                                                               \
	void name##_destroy(name* view)                                        \
	{                                                                      \
		free(view);                                                    \
	}                                                                      \
                                                                               \
	size_t name##_length(name* view)                                       \
	{                                                                      \
		return view->length;                                           \
	}                                                                      \
                                                                               \
	void name##_set_start(name* view, size_t start)                        \
	{                                                                      \
		view->start = start;                                           \
	}                                                                      \
                                                                               \
	void name##_set_length(name* view, size_t length)                      \
	{                                                                      \
		view->length = length;                                         \
	}                                                                      \
                                                                               \
	int name##_compare_array(name* view, elem_type* other,                 \
				 size_t other_length)                          \
	{                                                                      \
		int len_cmp =                                                  \
			nh_util_compare_sizes(view->length, other_length);     \
		if (len_cmp != 0) {                                            \
			return len_cmp;                                        \
		}                                                              \
                                                                               \
		return memcmp(&view->array[view->start], other,                \
			      view->length * sizeof(elem_type));               \
	}                                                                      \
                                                                               \
	int name##_compare(name* view, name* other)                            \
	{                                                                      \
		return name##_compare_array(view, &other->array[other->start], \
					    other->length);                    \
	}                                                                      \
                                                                               \
	bool name##_equals_array(name* view, elem_type* other,                 \
				 size_t other_length)                          \
	{                                                                      \
		return name##_compare_array(view, other, other_length) == 0;   \
	}                                                                      \
                                                                               \
	bool name##_equals(name* view, name* other)                            \
	{                                                                      \
		return name##_compare(view, other) == 0;                       \
	}
