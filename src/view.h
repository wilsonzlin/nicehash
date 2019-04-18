#pragma once

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#define _NH_VIEW_IMPL(name, elem_type)                                         \
	typedef struct {                                                       \
		size_t start;                                                  \
		size_t end;                                                    \
		size_t length;                                                 \
		elem_type* array;                                              \
	} name;                                                                \
                                                                               \
	bool name##_is_invalid(name* view)                                     \
	{                                                                      \
		return view->array == NULL || view->end < view->start;         \
	}                                                                      \
                                                                               \
	static void name##_update_length(name* view)                           \
	{                                                                      \
		/* Avoid overflow by adding first. */                          \
		view->length = name##_is_invalid(view)                         \
				       ? 0                                     \
				       : view->end + 1 - view->start;          \
	}                                                                      \
                                                                               \
	name* name##_create(elem_type* array, size_t start, size_t end)        \
	{                                                                      \
		name* view = malloc(sizeof(name));                             \
		view->array = array;                                           \
		view->start = start;                                           \
		view->end = end;                                               \
		name##_update_length(view);                                    \
		return view;                                                   \
	}                                                                      \
                                                                               \
	name* name##_create_invalid()                                          \
	{                                                                      \
		return name##_create(NULL, 1, 0);                              \
	}                                                                      \
                                                                               \
	name* name##_of_whole_array(elem_type* array, size_t length)           \
	{                                                                      \
		return name##_create(array, 0, length - 1);                    \
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
		name##_update_length(view);                                    \
	}                                                                      \
                                                                               \
	void name##_set_end(name* view, size_t end)                            \
	{                                                                      \
		view->end = end;                                               \
		name##_update_length(view);                                    \
	}                                                                      \
                                                                               \
	int name##_compare_array(name* view, elem_type* other,                 \
				 size_t other_length)                          \
	{                                                                      \
		int len_cmp = view->length < other_length                      \
				      ? -1                                     \
				      : view->length > other_length ? 1 : 0;   \
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
		return name##_compare_array(view, other->array,                \
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

#define NH_VIEW(elem_type, elem_name)                                          \
	_NH_VIEW_IMPL(nh_view_##elem_name, elem_type)
