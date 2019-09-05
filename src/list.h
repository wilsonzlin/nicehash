#pragma once

#include "./util.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define _NH_LIST_INITIAL_SIDE_SIZE 10
#define _NH_LIST_GROWTH_RATE 1.5

/**
 * Implement the comparison function for a specific list, satisfying the
 * prototype declared by {@link NH_LIST_PROTO}. The function compares the
 * lengths of both lists. If both lists have the same length, `memcmp` is used
 * to compare the bytes directly.
 *
 * @param name name of the specific list type
 * @param elem_type list's element type
 */
#define NH_LIST_DEFAULT_COMPARE_IMPL(name, elem_type)                          \
	int name##_compare(name* a, name* b)                                   \
	{                                                                      \
		int len_cmp = nh_util_compare_integers(a->length, b->length);  \
		if (len_cmp != 0)                                              \
			return len_cmp;                                        \
		return memcmp(name##_underlying(a), name##_underlying(b),      \
			      a->length * sizeof(elem_type));                  \
	}

/**
 * Declare structs and functions for a specific List<?>.
 * A list can add and remove elements from both ends in amortised constant time,
 * and reallocates memory as necessary to fit all elements.
 *
 * There is a left capacity and right capacity. Adding elements to a side
 * consumes capacity from that side; if there is no capacity remaining, new
 * memory is allocated to create more. The underlying storage is one contiguous
 * array, despite seeming to have two logical sides.
 *
 * @param name name to use for the type to be declared
 * @param elem_type element type
 */
#define NH_LIST_PROTO(name, elem_type)                                         \
	typedef struct {                                                       \
		elem_type* data;                                               \
		size_t head;                                                   \
		size_t length;                                                 \
		size_t size;                                                   \
		size_t size_left;                                              \
		size_t size_right;                                             \
	} name;                                                                \
                                                                               \
	name* name##_create_of_size(size_t initial_size_left,                  \
				    size_t initial_size_right);                \
                                                                               \
	name* name##_create(void);                                             \
                                                                               \
	void name##_destroy(name* list);                                       \
                                                                               \
	void name##_destroy_shallow(name* list);                               \
                                                                               \
	elem_type* name##_underlying(name* list);                              \
                                                                               \
	elem_type* name##_underlying_copy(name* list);                         \
                                                                               \
	bool name##_valid_index(name* list, size_t idx);                       \
                                                                               \
	elem_type name##_get(name* list, size_t idx);                          \
                                                                               \
	elem_type name##_first(name* list);                                    \
                                                                               \
	elem_type name##_last(name* list);                                     \
                                                                               \
	bool name##_is_empty(name* list);                                      \
                                                                               \
	void name##_set(name* list, size_t idx, elem_type c);                  \
                                                                               \
	void name##_clear(name* list);                                         \
                                                                               \
	void name##_size_ensure_left(name* list, size_t amount);               \
                                                                               \
	void name##_size_ensure_right(name* list, size_t amount);              \
                                                                               \
	void name##_add_right(name* list, elem_type tail);                     \
                                                                               \
	void name##_add_all_right_array(name* list, elem_type* ext,            \
					size_t ext_len);                       \
                                                                               \
	void name##_add_all_right_list(name* list, name* ext);                 \
                                                                               \
	elem_type name##_remove_left(name* list);                              \
                                                                               \
	void name##_add_left(name* list, elem_type head);                      \
                                                                               \
	elem_type name##_remove_right(name* list);                             \
                                                                               \
	int name##_compare(name* a, name* b);                                  \
                                                                               \
	bool name##_equal(name* a, name* b);

/**
 * Implement functions for a specific List<?>.
 *
 * This does not implement `{name}_compare`. {@link
 * NH_LIST_DEFAULT_COMPARE_IMPL} can be used to implement such a function that
 * uses `memcmp`.
 *
 * @param name name of the declared type
 * @param elem_type element type
 * @param invalid_value expression evaluated representing out of range indices
 */
#define NH_LIST_IMPL(name, elem_type, invalid_value)                           \
	name* name##_create_of_size(size_t initial_size_left,                  \
				    size_t initial_size_right)                 \
	{                                                                      \
		size_t initial_size = initial_size_left + initial_size_right;  \
		name* list = malloc(sizeof(name));                             \
		list->data = calloc(initial_size, sizeof(elem_type));          \
		list->head = initial_size_left;                                \
		list->length = 0;                                              \
		list->size = initial_size;                                     \
		list->size_left = initial_size_left;                           \
		list->size_right = initial_size_right;                         \
		return list;                                                   \
	}                                                                      \
                                                                               \
	name* name##_create(void)                                              \
	{                                                                      \
		return name##_create_of_size(_NH_LIST_INITIAL_SIDE_SIZE,       \
					     _NH_LIST_INITIAL_SIDE_SIZE);      \
	}                                                                      \
                                                                               \
	void name##_destroy(name* list)                                        \
	{                                                                      \
		free(list->data);                                              \
		free(list);                                                    \
	}                                                                      \
                                                                               \
	void name##_destroy_shallow(name* list)                                \
	{                                                                      \
		free(list);                                                    \
	}                                                                      \
                                                                               \
	elem_type* name##_underlying(name* list)                               \
	{                                                                      \
		return &list->data[list->head];                                \
	}                                                                      \
                                                                               \
	elem_type* name##_underlying_copy(name* list)                          \
	{                                                                      \
		elem_type* copy = calloc(list->length + 1, sizeof(elem_type)); \
		memcpy(copy, name##_underlying(list),                          \
		       list->length * sizeof(elem_type));                      \
		return copy;                                                   \
	}                                                                      \
                                                                               \
	bool name##_valid_index(name* list, size_t idx)                        \
	{                                                                      \
		return idx < list->length;                                     \
	}                                                                      \
                                                                               \
	elem_type name##_get(name* list, size_t idx)                           \
	{                                                                      \
		if (!name##_valid_index(list, idx)) {                          \
			return invalid_value;                                  \
		}                                                              \
                                                                               \
		return list->data[list->head + idx];                           \
	}                                                                      \
                                                                               \
	elem_type name##_first(name* list)                                     \
	{                                                                      \
                                                                               \
		return name##_get(list, 0);                                    \
	}                                                                      \
                                                                               \
	elem_type name##_last(name* list)                                      \
	{                                                                      \
                                                                               \
		return name##_get(list, list->length - 1);                     \
	}                                                                      \
                                                                               \
	bool name##_is_empty(name* list)                                       \
	{                                                                      \
                                                                               \
		return list->length == 0;                                      \
	}                                                                      \
                                                                               \
	void name##_set(name* list, size_t idx, elem_type c)                   \
	{                                                                      \
		if (!name##_valid_index(list, idx)) {                          \
			return;                                                \
		}                                                              \
                                                                               \
		list->data[list->head + idx] = c;                              \
	}                                                                      \
                                                                               \
	void name##_clear(name* list)                                          \
	{                                                                      \
		memset(name##_underlying(list), 0,                             \
		       list->length * sizeof(elem_type));                      \
		list->length = 0;                                              \
	}                                                                      \
                                                                               \
	static void _##name##_size_increase_left(name* list,                   \
						 size_t new_size_left)         \
	{                                                                      \
		size_t old_size_left = list->size_left;                        \
                                                                               \
		if (old_size_left >= new_size_left) {                          \
			return;                                                \
		}                                                              \
                                                                               \
		size_t diff_size_left = new_size_left - old_size_left;         \
                                                                               \
		size_t new_size = new_size_left + list->size_right;            \
                                                                               \
		elem_type* new_data = calloc(new_size, sizeof(elem_type));     \
		memcpy(&(new_data[diff_size_left]), list->data,                \
		       sizeof(elem_type) * list->length);                      \
		free(list->data);                                              \
                                                                               \
		list->data = new_data;                                         \
		list->head += diff_size_left;                                  \
		list->size = new_size;                                         \
		list->size_left = new_size_left;                               \
	}                                                                      \
                                                                               \
	static void _##name##_size_increase_right(name* list,                  \
						  size_t new_size_right)       \
	{                                                                      \
		size_t old_size = list->size;                                  \
		size_t old_size_right = list->size_right;                      \
                                                                               \
		if (old_size_right >= new_size_right) {                        \
			return;                                                \
		}                                                              \
                                                                               \
		size_t new_size = list->size_left + new_size_right;            \
                                                                               \
		elem_type* new_data =                                          \
			realloc(list->data, sizeof(elem_type) * new_size);     \
		memset(&new_data[old_size], 0,                                 \
		       sizeof(elem_type) * (new_size - old_size));             \
                                                                               \
		list->data = new_data;                                         \
		list->size = new_size;                                         \
		list->size_right = new_size_right;                             \
	}                                                                      \
                                                                               \
	void name##_size_ensure_left(name* list, size_t amount)                \
	{                                                                      \
		size_t desired_size = amount + 1;                              \
                                                                               \
		if (list->size_left < desired_size) {                          \
			_##name##_size_increase_left(list, desired_size);      \
		}                                                              \
	}                                                                      \
                                                                               \
	void name##_size_ensure_right(name* list, size_t amount)               \
	{                                                                      \
		size_t desired_size = amount + 1;                              \
                                                                               \
		if (list->size_right < desired_size) {                         \
			_##name##_size_increase_right(list, desired_size);     \
		}                                                              \
	}                                                                      \
                                                                               \
	void name##_add_right(name* list, elem_type tail)                      \
	{                                                                      \
		size_t next_idx = list->head + list->length;                   \
                                                                               \
		if (next_idx >= list->size - 1) {                              \
			size_t old_size = list->size_right;                    \
			/* +1 to guarantee an increase, +1 to guarantee '\0'   \
			 * terminator */                                       \
			size_t new_size = old_size * _NH_LIST_GROWTH_RATE + 2; \
                                                                               \
			_##name##_size_increase_right(list, new_size);         \
		}                                                              \
                                                                               \
		list->data[next_idx] = tail;                                   \
		list->length++;                                                \
	}                                                                      \
                                                                               \
	void name##_add_all_right_array(name* list, elem_type* ext,            \
					size_t ext_len)                        \
	{                                                                      \
		size_t free_space_right =                                      \
			list->size - list->head - list->length - 1;            \
		size_t required_space_right =                                  \
			ext_len + 1; /* For null terminator */                 \
                                                                               \
		if (required_space_right > free_space_right) {                 \
			name##_size_ensure_right(                              \
				list, list->size_right + required_space_right  \
					      - free_space_right);             \
		}                                                              \
                                                                               \
		memcpy(&list->data[list->head + list->length], ext,            \
		       sizeof(elem_type) * ext_len);                           \
		list->length += ext_len;                                       \
	}                                                                      \
                                                                               \
	void name##_add_all_right_list(name* list, name* ext)                  \
	{                                                                      \
		name##_add_all_right_array(list, name##_underlying(ext),       \
					   ext->length);                       \
	}                                                                      \
                                                                               \
	elem_type name##_remove_left(name* list)                               \
	{                                                                      \
		if (list->length == 0) {                                       \
			return invalid_value;                                  \
		}                                                              \
                                                                               \
		elem_type f = list->data[list->head];                          \
		list->data[list->head] = 0;                                    \
		list->head++;                                                  \
		list->length--;                                                \
                                                                               \
		return f;                                                      \
	}                                                                      \
                                                                               \
	void name##_add_left(name* list, elem_type head)                       \
	{                                                                      \
		if (list->head == 0) {                                         \
			size_t old_size = list->size_left;                     \
			size_t new_size =                                      \
				old_size * _NH_LIST_GROWTH_RATE                \
				+ 1; /* +1 to always guarantee an increase */  \
                                                                               \
			_##name##_size_increase_left(list, new_size);          \
		}                                                              \
                                                                               \
		list->head--;                                                  \
		list->data[list->head] = head;                                 \
		list->length++;                                                \
	}                                                                      \
                                                                               \
	elem_type name##_remove_right(name* list)                              \
	{                                                                      \
		if (list->length == 0) {                                       \
			return invalid_value;                                  \
		}                                                              \
                                                                               \
		size_t idx = list->head + list->length - 1;                    \
                                                                               \
		elem_type l = list->data[idx];                                 \
                                                                               \
		list->data[idx] = 0;                                           \
		list->length--;                                                \
                                                                               \
		return l;                                                      \
	}                                                                      \
                                                                               \
	bool name##_equal(name* a, name* b)                                    \
	{                                                                      \
		return a->length == b->length && name##_compare(a, b) == 0;    \
	}
