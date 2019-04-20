#pragma once

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define _NH_BITFIELD_DEFAULT_CELL_TYPE uint64_t

#define _NH_BITFIELD_CALC_SIZE(cell_type, max_value)                           \
	((max_value) / (_NH_BITFIELD_CALC_CELL_BITS(cell_type))                \
	 + ((max_value) % (_NH_BITFIELD_CALC_CELL_BITS(cell_type)) != 0))

#define _NH_BITFIELD_CALC_CELL_BITS(cell_type) (sizeof(cell_type) * CHAR_BIT)

#define _NH_BITFIELD_PROTO(name, cell_type, size, elem_type)                   \
	typedef struct {                                                       \
		cell_type exists[size];                                        \
	} name;                                                                \
                                                                               \
	/**                                                                    \
	 * Allocate memory for and create a new bit field.                     \
	 *                                                                     \
	 * @return pointer to a heap-allocated bit field                       \
	 */                                                                    \
	name* name##_create(void);                                             \
                                                                               \
	/**                                                                    \
	 * Free memory of and destroy a bit field.                             \
	 *                                                                     \
	 * @param bf bit field to destroy                                      \
	 */                                                                    \
	void name##_destroy(name* bf);                                         \
                                                                               \
	/**                                                                    \
	 * Check the existence of an element in a bit field.                   \
	 *                                                                     \
	 * @param bf bit field                                                 \
	 * @param elem element to check for                                    \
	 * @return `true` if the element exists, `false` otherwise             \
	 */                                                                    \
	bool name##_has(name* bf, elem_type elem);                             \
                                                                               \
	/**                                                                    \
	 * Add an element to a bit field.                                      \
	 *                                                                     \
	 * @param bf bit field                                                 \
	 * @param elem element to add                                          \
	 * @return `true` if the element is valid and did not exist before     \
	 * adding, `false` otherwise                                           \
	 */                                                                    \
	bool name##_add(name* bf, elem_type elem);                             \
                                                                               \
	/**                                                                    \
	 * Delete an element from a bit field.                                 \
	 *                                                                     \
	 * @param bf bit field                                                 \
	 * @param elem element to remove                                       \
	 * @return `true` if the element existed before deleting, `false`      \
	 * otherwise                                                           \
	 */                                                                    \
	bool name##_delete(name* bf, elem_type elem);                          \
                                                                               \
	/**                                                                    \
	 * Remove all elements from a bit field.                               \
	 *                                                                     \
	 * @param bf bit field                                                 \
	 */                                                                    \
	void name##_clear(name* bf);

#define NH_BITFIELD_PROTO_CUSTOM_CELL(name, cell_type, elem_type, max_value)   \
	_NH_BITFIELD_PROTO(name, cell_type,                                    \
			   _NH_BITFIELD_CALC_SIZE(cell_type, max_value),       \
			   elem_type)

#define NH_BITFIELD_PROTO(name, elem_type, max_value)                          \
	NH_BITFIELD_PROTO_CUSTOM_CELL(name, _NH_BITFIELD_DEFAULT_CELL_TYPE,    \
				      elem_type, max_value)

/**
 * Internal macro. Declare variables for the index, mask, and existance of an
 * element in a bit field. Causes a `return false` if the element is out of
 * range.
 *
 * @param bf bit field
 * @param elem element
 */
#define _NH_BITFIELD_ELEM_STATS(bf, cell_type, cell_bits, elem, max_value)     \
	if (elem < 0 || elem > max_value) {                                    \
		return false;                                                  \
	}                                                                      \
	int index = elem / (cell_bits);                                        \
	cell_type mask = 1 << (elem % (cell_bits));                            \
	bool exists = (bf->exists[index] & mask) != 0;

#define _NH_BITFIELD_IMPL(name, cell_type, cell_bits, size, elem_type,         \
			  max_value)                                           \
	name* name##_create(void)                                              \
	{                                                                      \
		name* bf = calloc(1, sizeof(name));                            \
		return bf;                                                     \
	}                                                                      \
                                                                               \
	void name##_destroy(name* bf)                                          \
	{                                                                      \
		free(bf);                                                      \
	}                                                                      \
                                                                               \
	bool name##_has(name* bf, elem_type elem)                              \
	{                                                                      \
		_NH_BITFIELD_ELEM_STATS(bf, cell_type, cell_bits, elem,        \
					max_value)                             \
		return exists;                                                 \
	}                                                                      \
                                                                               \
	bool name##_add(name* bf, elem_type elem)                              \
	{                                                                      \
		_NH_BITFIELD_ELEM_STATS(bf, cell_type, cell_bits, elem,        \
					max_value)                             \
		bf->exists[index] |= mask;                                     \
		return !exists;                                                \
	}                                                                      \
                                                                               \
	bool name##_delete(name* bf, elem_type elem)                           \
	{                                                                      \
		_NH_BITFIELD_ELEM_STATS(bf, cell_type, cell_bits, elem,        \
					max_value)                             \
		bf->exists[index] &= ~mask;                                    \
		return exists;                                                 \
	}                                                                      \
                                                                               \
	void name##_clear(name* bf)                                            \
	{                                                                      \
		memset(bf->exists, 0, (size) * sizeof(cell_type));             \
	}

#define NH_BITFIELD_IMPL_CUSTOM_CELL(name, cell_type, elem_type, max_value)    \
	_NH_BITFIELD_IMPL(name, cell_type,                                     \
			  _NH_BITFIELD_CALC_CELL_BITS(cell_type),              \
			  _NH_BITFIELD_CALC_SIZE(cell_type, max_value),        \
			  elem_type, max_value)

#define NH_BITFIELD_IMPL(name, elem_type, max_value)                           \
	NH_BITFIELD_IMPL_CUSTOM_CELL(name, _NH_BITFIELD_DEFAULT_CELL_TYPE,     \
				     elem_type, max_value)
