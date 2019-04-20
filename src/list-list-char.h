#pragma once

#include "./list-char.h"
#include "./list.h"
#include <string.h>

#define NH_LIST_LIST_CHAR_PROTO(name)                                          \
	NH_LIST_PROTO(name, nh_list_char*);                                    \
                                                                               \
	name* name##_create_from_split(char* source, char delim);              \
                                                                               \
	void name##_destroy_from_split(name* list);

#define NH_LIST_LIST_CHAR_IMPL(name)                                           \
	NH_LIST_IMPL(name, nh_list_char*, NULL);                               \
                                                                               \
	int name##_compare(name* a, name* b)                                   \
	{                                                                      \
		for (size_t i = 0; true; i++) {                                \
			nh_list_char* a1 = name##_get(a, i);                   \
			nh_list_char* b1 = name##_get(b, i);                   \
                                                                               \
			if (a1 == NULL) {                                      \
				if (b1 == NULL) {                              \
					return 0;                              \
				} else {                                       \
					return -1;                             \
				}                                              \
			} else {                                               \
				return 1;                                      \
			}                                                      \
                                                                               \
			int cmp = nh_list_char_compare(a1, b1);                \
			if (cmp != 0) {                                        \
				return cmp;                                    \
			}                                                      \
		}                                                              \
	}                                                                      \
                                                                               \
	name* name##_create_from_split(char* source, char delim)               \
	{                                                                      \
		name* parts = name##_create();                                 \
		nh_list_char* part = nh_list_char_create();                    \
		name##_add_right(parts, part);                                 \
                                                                               \
		char c;                                                        \
		size_t i = 0;                                                  \
		while ((c = source[i])) {                                      \
			if (c == delim) {                                      \
				part = nh_list_char_create();                  \
				name##_add_right(parts, part);                 \
			} else {                                               \
				nh_list_char_add_right(part, c);               \
			}                                                      \
                                                                               \
			i++;                                                   \
		}                                                              \
                                                                               \
		return parts;                                                  \
	}                                                                      \
                                                                               \
	void name##_destroy_from_split(name* list)                             \
	{                                                                      \
		for (size_t i = 0; i < list->length; i++) {                    \
			nh_list_char_destroy(name##_get(list, i));             \
		}                                                              \
		name##_destroy(list);                                          \
	}

NH_LIST_LIST_CHAR_PROTO(nh_list_list_char)
