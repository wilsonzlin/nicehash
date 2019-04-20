#pragma once

#include "./list.h"
#include <stdint.h>
#include <string.h>

#define _NH_LIST_CHAR_ADD_UTF_8_IMPL(list, adder, code_point)                  \
	if (code_point <= 0x7F) {                                              \
		/* Plain ASCII */                                              \
		(adder)(list, (char) code_point);                              \
		return 1;                                                      \
	}                                                                      \
                                                                               \
	if (code_point <= 0x07FF) {                                            \
		(adder)(list, (char) (((code_point >> 6) & 0x1F) | 0xC0));     \
		(adder)(list, (char) (((code_point >> 0) & 0x3F) | 0x80));     \
		return 2;                                                      \
	}                                                                      \
                                                                               \
	if (code_point <= 0xFFFF) {                                            \
		(adder)(list, (char) (((code_point >> 12) & 0x0F) | 0xE0));    \
		(adder)(list, (char) (((code_point >> 6) & 0x3F) | 0x80));     \
		(adder)(list, (char) (((code_point >> 0) & 0x3F) | 0x80));     \
		return 3;                                                      \
	}                                                                      \
                                                                               \
	if (code_point <= 0x10FFFF) {                                          \
		(adder)(list, (char) (((code_point >> 18) & 0x07) | 0xF0));    \
		(adder)(list, (char) (((code_point >> 12) & 0x3F) | 0x80));    \
		(adder)(list, (char) (((code_point >> 6) & 0x3F) | 0x80));     \
		(adder)(list, (char) (((code_point >> 0) & 0x3F) | 0x80));     \
		return 4;                                                      \
	}                                                                      \
                                                                               \
	return 0;

#define NH_LIST_CHAR_PROTO(name)                                               \
	NH_LIST_PROTO(name, char)                                              \
                                                                               \
	int name##_compare_array(name* a, char* b);                            \
                                                                               \
	bool name##_equal_array(name* a, char* b);                             \
                                                                               \
	size_t name##_add_left_utf_8(name* list, uint32_t code_point);         \
                                                                               \
	size_t name##_add_right_utf_8(name* list, uint32_t code_point);

#define NH_LIST_CHAR_IMPL(name)                                                \
	NH_LIST_IMPL(name, char, '\0')                                         \
                                                                               \
	NH_LIST_DEFAULT_COMPARE_IMPL(name, char)                               \
                                                                               \
	int name##_compare_array(name* a, char* b)                             \
	{                                                                      \
		return strcmp(name##_underlying(a), b);                        \
	}                                                                      \
                                                                               \
	bool name##_equal_array(name* a, char* b)                              \
	{                                                                      \
		return name##_compare_array(a, b) == 0;                        \
	}                                                                      \
                                                                               \
	size_t name##_add_left_utf_8(name* list, uint32_t code_point)          \
	{                                                                      \
		_NH_LIST_CHAR_ADD_UTF_8_IMPL(list, name##_add_left,            \
					     code_point);                      \
	}                                                                      \
                                                                               \
	size_t name##_add_right_utf_8(name* list, uint32_t code_point)         \
	{                                                                      \
		_NH_LIST_CHAR_ADD_UTF_8_IMPL(list, name##_add_right,           \
					     code_point);                      \
	}

NH_LIST_CHAR_PROTO(nh_list_char)
