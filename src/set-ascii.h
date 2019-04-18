#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * Internal macro. Declare variables for the index, mask, and existance of an
 * element in a set. Causes a `return false` if the element is out of range.
 *
 * @param set set
 * @param elem element
 */
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

typedef struct {
	uint64_t exists[2];
} nh_set_ascii;

/**
 * Allocate memory for and create a new Set<ASCII>.
 *
 * @return pointer to a heap-allocated Set<ASCII>
 */
nh_set_ascii* nh_set_ascii_create(void)
{
	nh_set_ascii* set = calloc(1, sizeof(nh_set_ascii));
	return set;
}

/**
 * Free memory of and destroy a Set<ASCII>.
 *
 * @param set set to destroy
 */
void nh_set_ascii_destroy(nh_set_ascii* set)
{
	free(set);
}

/**
 * Check the existence of an element in a set.
 *
 * @param set set
 * @param elem element to check for
 * @return `true` if the element exists, `false` otherwise
 */
bool nh_set_ascii_has(nh_set_ascii* set, char elem)
{
	_NH_SET_ASCII_ELEM_STATS(set, elem)
	return exists;
}

/**
 * Add an element to a set.
 *
 * @param set set
 * @param elem element to add
 * @return `true` if the element did not exist before adding, `false` otherwise
 */
bool nh_set_ascii_add(nh_set_ascii* set, char elem)
{
	_NH_SET_ASCII_ELEM_STATS(set, elem)
	set->exists[index] |= mask;
	return !exists;
}

/**
 * Delete an element from a set.
 *
 * @param set set
 * @param elem element to remove
 * @return `true` if the element existed before deleting, `false` otherwise
 */
bool nh_set_ascii_delete(nh_set_ascii* set, char elem)
{
	_NH_SET_ASCII_ELEM_STATS(set, elem)
	set->exists[index] &= ~mask;
	return exists;
}

/**
 * Remove all elements from a set.
 *
 * @param set set
 */
void nh_set_ascii_clear(nh_set_ascii* set)
{
	set->exists[0] = 0;
	set->exists[1] = 0;
}
