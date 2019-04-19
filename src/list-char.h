#pragma once

#include "./list.h"
#include <stdint.h>
#include <string.h>

NH_LIST(nh_list_char, char, '\0')

NH_LIST_DEFAULT_COMPARE(nh_list_char, char)

int nh_list_char_compare_array(nh_list_char* a, char* b)
{
	return strcmp(nh_list_char_underlying(a), b);
}

bool nh_list_char_equal_array(nh_list_char* a, char* b)
{
	return nh_list_char_compare_array(a, b) == 0;
}

#define _NH_LIST_CHAR_ADD_UTF8_IMPL(list, adder, code_point)                   \
	{                                                                      \
		if (code_point <= 0x7F) {                                      \
			/* Plain ASCII */                                      \
			(adder)(list, (char) code_point);                      \
			return 1;                                              \
		}                                                              \
                                                                               \
		if (code_point <= 0x07FF) {                                    \
			(adder)(list,                                          \
				(char) (((code_point >> 6) & 0x1F) | 0xC0));   \
			(adder)(list,                                          \
				(char) (((code_point >> 0) & 0x3F) | 0x80));   \
			return 2;                                              \
		}                                                              \
                                                                               \
		if (code_point <= 0xFFFF) {                                    \
			(adder)(list,                                          \
				(char) (((code_point >> 12) & 0x0F) | 0xE0));  \
			(adder)(list,                                          \
				(char) (((code_point >> 6) & 0x3F) | 0x80));   \
			(adder)(list,                                          \
				(char) (((code_point >> 0) & 0x3F) | 0x80));   \
			return 3;                                              \
		}                                                              \
                                                                               \
		if (code_point <= 0x10FFFF) {                                  \
			(adder)(list,                                          \
				(char) (((code_point >> 18) & 0x07) | 0xF0));  \
			(adder)(list,                                          \
				(char) (((code_point >> 12) & 0x3F) | 0x80));  \
			(adder)(list,                                          \
				(char) (((code_point >> 6) & 0x3F) | 0x80));   \
			(adder)(list,                                          \
				(char) (((code_point >> 0) & 0x3F) | 0x80));   \
			return 4;                                              \
		}                                                              \
                                                                               \
		return 0;                                                      \
	}

size_t nh_list_char_add_left_utf_8(nh_list_char* list, uint32_t code_point)
{
	_NH_LIST_CHAR_ADD_UTF8_IMPL(list, nh_list_char_add_left, code_point);
}

size_t nh_list_char_add_right_utf_8(nh_list_char* list, uint32_t code_point)
{
	_NH_LIST_CHAR_ADD_UTF8_IMPL(list, nh_list_char_add_right, code_point);
}
