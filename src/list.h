#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INITIAL_LIST_SIDE_SIZE 10
#define LIST_GROWTH_RATE 1.5

#define NH_LIST(name, elem_t, elem_size, invsafe_elem_t, invalid_value)        \
	typedef struct name {                                                  \
		elem_t* data;                                                  \
		size_t head;                                                   \
		size_t length;                                                 \
		size_t size;                                                   \
		size_t size_left;                                              \
		size_t size_right;                                             \
	} name;                                                                \
                                                                               \
	name* name##_create_of_size(size_t initial_size_left,                  \
				    size_t initial_size_right)                 \
	{                                                                      \
		size_t initial_size = initial_size_left + initial_size_right;  \
		name* buf = malloc(sizeof(name));                              \
		buf->data = calloc(initial_size, elem_size);                   \
		buf->head = initial_size_left;                                 \
		buf->length = 0;                                               \
		buf->size = initial_size;                                      \
		buf->size_left = initial_size_left;                            \
		buf->size_right = initial_size_right;                          \
		return buf;                                                    \
	}                                                                      \
                                                                               \
	name* name##_create(void)                                              \
	{                                                                      \
		return name##_create_of_size(INITIAL_LIST_SIDE_SIZE,           \
					     INITIAL_LIST_SIDE_SIZE);          \
	}                                                                      \
                                                                               \
	void name##_destroy(name* buf)                                         \
	{                                                                      \
		free(buf->data);                                               \
		free(buf);                                                     \
	}                                                                      \
                                                                               \
	void name##_destroy_shallow(name* buf)                                 \
	{                                                                      \
		free(buf);                                                     \
	}                                                                      \
                                                                               \
	elem_t* name##_underlying(name* buf)                                   \
	{                                                                      \
		return &((buf->data)[buf->head]);                              \
	}                                                                      \
                                                                               \
	elem_t* name##_underlying_copy(name* buf)                              \
	{                                                                      \
		elem_t* copy = calloc(buf->length + 1, elem_size);             \
		memcpy(copy, name##_underlying(buf), buf->length* elem_size);  \
		return copy;                                                   \
	}                                                                      \
                                                                               \
	bool name##_valid_index(name* buf, size_t idx)                         \
	{                                                                      \
		return idx < buf->length;                                      \
	}                                                                      \
                                                                               \
	invsafe_elem_t name##_get(name* buf, size_t idx)                       \
	{                                                                      \
		if (!name##_valid_index(buf, idx)) {                           \
			return invalid_value;                                  \
		}                                                              \
                                                                               \
		return buf->data[buf->head + idx];                             \
	}                                                                      \
                                                                               \
	invsafe_elem_t name##_first(name* buf)                                 \
	{                                                                      \
                                                                               \
		return name##_get(buf, 0);                                     \
	}                                                                      \
                                                                               \
	invsafe_elem_t name##_last(name* buf)                                  \
	{                                                                      \
                                                                               \
		return name##_get(buf, buf->length);                           \
	}                                                                      \
                                                                               \
	bool name##_is_empty(name* buf)                                        \
	{                                                                      \
                                                                               \
		return buf->length == 0;                                       \
	}                                                                      \
                                                                               \
	void name##_set(name* buf, size_t idx, elem_t c)                       \
	{                                                                      \
		if (!name##_valid_index(buf, idx)) {                           \
			return;                                                \
		}                                                              \
                                                                               \
		buf->data[buf->head + idx] = c;                                \
	}                                                                      \
                                                                               \
	void name##_clear(name* buf)                                           \
	{                                                                      \
		for (size_t i = 0; i < buf->length; i++) {                     \
			buf->data[buf->head + i] = 0;                          \
		}                                                              \
		buf->length = 0;                                               \
	}                                                                      \
                                                                               \
	static void name##_size_increase_left(name* buf, size_t new_size_left) \
	{                                                                      \
		size_t old_size_left = buf->size_left;                         \
                                                                               \
		if (old_size_left >= new_size_left) {                          \
			return;                                                \
		}                                                              \
                                                                               \
		size_t diff_size_left = new_size_left - old_size_left;         \
                                                                               \
		size_t new_size = new_size_left + buf->size_right;             \
                                                                               \
		elem_t* new_data = calloc(new_size, elem_size);                \
		memcpy(&(new_data[diff_size_left]), buf->data,                 \
		       elem_size * buf->length);                               \
		free(buf->data);                                               \
                                                                               \
		buf->data = new_data;                                          \
		buf->head += old_size_left;                                    \
		buf->size = new_size;                                          \
		buf->size_left = new_size_left;                                \
	}                                                                      \
                                                                               \
	static void name##_size_increase_right(name* buf,                      \
					       size_t new_size_right)          \
	{                                                                      \
		size_t old_size = buf->size;                                   \
		size_t old_size_right = buf->size_right;                       \
                                                                               \
		if (old_size_right >= new_size_right) {                        \
			return;                                                \
		}                                                              \
                                                                               \
		size_t new_size = buf->size_left + new_size_right;             \
                                                                               \
		elem_t* new_data = realloc(buf->data, elem_size * new_size);   \
		for (size_t i = old_size; i < new_size; i++) {                 \
			new_data[i] = 0;                                       \
		}                                                              \
                                                                               \
		buf->data = new_data;                                          \
		buf->size = new_size;                                          \
		buf->size_right = new_size_right;                              \
	}                                                                      \
                                                                               \
	void name##_size_ensure_left(name* buf, size_t amount)                 \
	{                                                                      \
		size_t desired_size = amount + 1;                              \
                                                                               \
		if (buf->size_left < desired_size) {                           \
			name##_size_increase_left(buf, desired_size);          \
		}                                                              \
	}                                                                      \
                                                                               \
	void name##_size_ensure_right(name* buf, size_t amount)                \
	{                                                                      \
		size_t desired_size = amount + 1;                              \
                                                                               \
		if (buf->size_right < desired_size) {                          \
			name##_size_increase_right(buf, desired_size);         \
		}                                                              \
	}                                                                      \
                                                                               \
	void name##_add_right(name* buf, elem_t tail)                          \
	{                                                                      \
		size_t next_idx = buf->head + buf->length;                     \
                                                                               \
		if (next_idx >= buf->size - 1) {                               \
			size_t old_size = buf->size_right;                     \
			size_t new_size =                                      \
				old_size * LIST_GROWTH_RATE                    \
				+ 1; /* +1 to always guarantee an increase */  \
                                                                               \
			name##_size_increase_right(buf, new_size);             \
		}                                                              \
                                                                               \
		buf->data[next_idx] = tail;                                    \
		buf->length++;                                                 \
	}                                                                      \
                                                                               \
	void name##_add_all_right_arr(name* buf, elem_t* ext, size_t ext_len)  \
	{                                                                      \
		name##_size_ensure_right(buf, buf->length + ext_len);          \
		for (size_t i = 0; i < ext_len; i++) {                         \
			name##_add_right(buf, ext[i]);                         \
		}                                                              \
	}                                                                      \
                                                                               \
	void name##_add_all_right_buf(name* buf, name* ext)                    \
	{                                                                      \
		name##_size_ensure_right(buf, buf->length + ext->length);      \
		for (size_t i = 0; i < buf->length; i++) {                     \
			name##_add_right(buf, buf->data[i]);                   \
		}                                                              \
	}                                                                      \
                                                                               \
	invsafe_elem_t name##_remove_left(name* buf)                           \
	{                                                                      \
		if (buf->length == 0) {                                        \
			return invalid_value;                                  \
		}                                                              \
                                                                               \
		elem_t f = buf->data[buf->head];                               \
		buf->data[buf->head] = 0;                                      \
		buf->head++;                                                   \
		buf->length--;                                                 \
                                                                               \
		return f;                                                      \
	}                                                                      \
                                                                               \
	void name##_add_left(name* buf, elem_t head)                           \
	{                                                                      \
		if (buf->head == 0) {                                          \
			size_t old_size = buf->size_left;                      \
			size_t new_size =                                      \
				old_size * LIST_GROWTH_RATE                    \
				+ 1; /* +1 to always guarantee an increase */  \
                                                                               \
			name##_size_increase_left(buf, new_size);              \
		}                                                              \
                                                                               \
		buf->head--;                                                   \
		buf->data[buf->head] = head;                                   \
		buf->length++;                                                 \
	}                                                                      \
                                                                               \
	invsafe_elem_t name##_remove_right(name* buf)                          \
	{                                                                      \
		if (buf->length == 0) {                                        \
			return invalid_value;                                  \
		}                                                              \
                                                                               \
		size_t idx = buf->head + buf->length - 1;                      \
                                                                               \
		elem_t l = buf->data[idx];                                     \
                                                                               \
		buf->data[idx] = 0;                                            \
		buf->length--;                                                 \
                                                                               \
		return l;                                                      \
	}                                                                      \
                                                                               \
	int name##_compare(name* a, name* b);                                  \
                                                                               \
	bool name##_equal(name* a, name* b)                                    \
	{                                                                      \
		return a->length == b->length && name##_compare(a, b) == 0;    \
	}
