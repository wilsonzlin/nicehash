#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define _NH_SET_ASCII_ELEM_STATS(set, elem)                                    \
	if (elem != 0 && (elem & 0x80) != 0) {                                 \
		return false;                                                  \
	}                                                                      \
	int index;                                                             \
	uint64_t mask;                                                         \
	if (elem < 64) {                                                       \
		index = 0;                                                     \
		mask = 1 << elem;                                              \
	} else {                                                               \
		index = 1;                                                     \
		mask = 1 << (elem - 64);                                       \
	}                                                                      \
	bool exists = (set->exists[index] & mask) != 0;

#define _NH_SET_ASCII_IMPL(name)                                               \
	typedef struct {                                                       \
		uint64_t exists[2];                                            \
	} name;                                                                \
                                                                               \
	name* name##_create(void)                                              \
	{                                                                      \
		name* set = calloc(1, sizeof(name));                           \
		return set;                                                    \
	}                                                                      \
                                                                               \
	void name##_destroy(name* set)                                         \
	{                                                                      \
		free(set);                                                     \
	}                                                                      \
                                                                               \
	bool name##_has(name* set, char elem)                                  \
	{                                                                      \
		_NH_SET_ASCII_ELEM_STATS(set, elem)                            \
		return exists;                                                 \
	}                                                                      \
                                                                               \
	bool name##_add(name* set, char elem)                                  \
	{                                                                      \
		_NH_SET_ASCII_ELEM_STATS(set, elem)                            \
		set->exists[index] |= mask;                                    \
		return !exists;                                                \
	}                                                                      \
                                                                               \
	bool name##_delete(name* set, char elem)                               \
	{                                                                      \
		_NH_SET_ASCII_ELEM_STATS(set, elem)                            \
		set->exists[index] &= ~mask;                                   \
		return exists;                                                 \
	}                                                                      \
                                                                               \
	void name##_clear(name* set)                                           \
	{                                                                      \
		set->exists[0] = 0;                                            \
		set->exists[1] = 0;                                            \
	}

#define NH_SET_ASCII_CUSTOM_NAME(key_name) _NH_SET_ASCII_IMPL(nh_set_##key_name)

NH_SET_ASCII_CUSTOM_NAME(ascii)
