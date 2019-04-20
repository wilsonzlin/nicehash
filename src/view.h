#pragma once

#include "./util.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/**
 * Helper macro for iterating a view using a for loop.
 * Generates a for loop statement declaring variables representing the index,
 * offset, and length during iteration.
 *
 * @param view view to iterate
 * @param var_index name for the variable representing the index, which is the
 * position within the view
 * @param var_offset name for the variable representing the offset, which is the
 * position within the underlying array
 * @param var_length name for the variable representing the length of the view
 */
#define nh_view_for(view, var_index, var_offset, var_length)                   \
	for (size_t var_index = 0, var_offset = (view)->start,                 \
		    var_length = (view)->length;                               \
	     var_index < var_length; var_index++, var_offset++)

/**
 * Declare structs and functions for a specific View<?>.
 * A view represents the subarray [`start`, `start` + `length`) of `array`.
 * The subarray is a pointer and not a copy, so changes to elements in the
 * subarray will affect the original array and vice versa.
 *
 * @param name name to use for the type to be declared
 * @param elem_type array element type
 */
#define NH_VIEW_PROTO(name, elem_type)                                         \
	typedef struct {                                                       \
		size_t start;                                                  \
		size_t length;                                                 \
		elem_type* array;                                              \
	} name;                                                                \
                                                                               \
	/**                                                                    \
	 * Set the values of a view structure.                                 \
	 *                                                                     \
	 * @param view view                                                    \
	 * @param array pointer to the underlying array to use                 \
	 * @param start starting offset to use                                 \
	 * @param length length to use                                         \
	 */                                                                    \
	void name##_init(name* view, elem_type* array, size_t start,           \
			 size_t length);                                       \
                                                                               \
	/**                                                                    \
	 * Allocate memory for and create a new view.                          \
	 *                                                                     \
	 * @param array pointer to the underlying array                        \
	 * @param start starting offset                                        \
	 * @param length length                                                \
	 * @return pointer to a heap-allocated view                            \
	 */                                                                    \
	name* name##_create(elem_type* array, size_t start, size_t length);    \
                                                                               \
	/**                                                                    \
	 * Allocate memory for and create a new view of the entirety of an     \
	 * array.                                                              \
	 *                                                                     \
	 * @param array pointer to the array                                   \
	 * @param length length of the array                                   \
	 * @return pointer to a heap-allocated view                            \
	 */                                                                    \
	name* name##_of_whole_array(elem_type* array, size_t length);          \
                                                                               \
	/**                                                                    \
	 * Free memory of and destroy a view.                                  \
	 *                                                                     \
	 * @param view view to destroy                                         \
	 */                                                                    \
	void name##_destroy(name* view);                                       \
                                                                               \
	/**                                                                    \
	 * Check if an index is not out of range.                              \
	 *                                                                     \
	 * @param view view                                                    \
	 * @param index index to check                                         \
	 * @return `true` if the index is less than the length, `false`        \
	 * otherwise                                                           \
	 */                                                                    \
	bool name##_valid_index(name* view, size_t index);                     \
                                                                               \
	/**                                                                    \
	 * Get the starting offset, which is the position in the underlying    \
	 * array where this view starts.                                       \
	 *                                                                     \
	 * @param view view                                                    \
	 * @return an unsigned integer representing an index in the underlying \
	 * array                                                               \
	 */                                                                    \
	size_t name##_start(name* view);                                       \
                                                                               \
	/**                                                                    \
	 * Get the length.                                                     \
	 *                                                                     \
	 * @param view view                                                    \
	 * @return an unsigned integer                                         \
	 */                                                                    \
	size_t name##_length(name* view);                                      \
                                                                               \
	/**                                                                    \
	 * Get the pointer to the underlying array.                            \
	 *                                                                     \
	 * @param view view                                                    \
	 * @return pointer to underlying array                                 \
	 */                                                                    \
	elem_type* name##_underlying_array(name* view);                        \
                                                                               \
	/**                                                                    \
	 * Get a pointer to the underlying array offset by the starting        \
	 * offset.                                                             \
	 *                                                                     \
	 * @param view view                                                    \
	 * @return pointer to somewhere in the underlying array                \
	 */                                                                    \
	elem_type* name##_underlying_array_from_start(name* view);             \
                                                                               \
	/**                                                                    \
	 * Get the element at a specific index in a view.                      \
	 * Valid indices are in the range [0, length).                         \
	 * If the index is out of range, an invalid value will be returned.    \
	 *                                                                     \
	 * @param view view                                                    \
	 * @param index index                                                  \
	 * @return value at index or an invalid value                          \
	 */                                                                    \
	elem_type name##_get(name* view, size_t index);                        \
                                                                               \
	/**                                                                    \
	 * Set the starting offset of a view.                                  \
	 * The starting offset is the index of the first element of a view in  \
	 * the underlying array.                                               \
	 *                                                                     \
	 * @param view view                                                    \
	 * @param start starting offset                                        \
	 */                                                                    \
	void name##_set_start(name* view, size_t start);                       \
                                                                               \
	/**                                                                    \
	 * Set the length of a view.                                           \
	 * The view represents `length` contiguous element(s) of the           \
	 * underlying array.                                                   \
	 *                                                                     \
	 * @param view view                                                    \
	 * @param length length                                                \
	 */                                                                    \
	void name##_set_length(name* view, size_t length);                     \
                                                                               \
	/**                                                                    \
	 * Compare a view's elements with another array.                       \
	 *                                                                     \
	 * @param view view                                                    \
	 * @param other array to compare to                                    \
	 * @param other_length length of the array to compare to               \
	 * @return an integer less than, equal to, or greater than zero if the \
	 * first *n* elements of the view is found, respectively, to be less   \
	 * than, equal to, or greater than the first *n* elements of the other \
	 * array                                                               \
	 */                                                                    \
	int name##_compare_array(name* view, elem_type* other,                 \
				 size_t other_length);                         \
                                                                               \
	/**                                                                    \
	 * Compare a view's elements with another view.                        \
	 *                                                                     \
	 * @param view view                                                    \
	 * @param other view to compare to                                     \
	 * @return an integer less than, equal to, or greater than zero if the \
	 * first *n* elements of the view is found, respectively, to be less   \
	 * than, equal to, or greater than the first *n* elements of the other \
	 * view                                                                \
	 */                                                                    \
	int name##_compare(name* view, name* other);                           \
                                                                               \
	/**                                                                    \
	 * Check if the length and elements of the view is/are equal to an     \
	 * array's.                                                            \
	 *                                                                     \
	 * @param view view                                                    \
	 * @param other array to compare to                                    \
	 * @param other_length length of the array to compare to               \
	 * @return `true` if they are equal, `false` otherwise                 \
	 */                                                                    \
	bool name##_equals_array(name* view, elem_type* other,                 \
				 size_t other_length);                         \
                                                                               \
	/**                                                                    \
	 * Check if the length and elements of the view is/are equal to        \
	 * another view's.                                                     \
	 *                                                                     \
	 * @param view view                                                    \
	 * @param other view to compare to                                     \
	 * @return `true` if they are equal, `false` otherwise                 \
	 */                                                                    \
	bool name##_equals(name* view, name* other);

/**
 * Implement functions for a specific View<?>.
 *
 * @param name name to use for the type to be declared
 * @param elem_type array element type
 * @param invalid_value expression evaluated representing out of range indices
 */
#define NH_VIEW_IMPL(name, elem_type, invalid_value)                           \
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
	bool name##_valid_index(name* view, size_t index)                      \
	{                                                                      \
		return index < view->length;                                   \
	}                                                                      \
                                                                               \
	size_t name##_start(name* view)                                        \
	{                                                                      \
		return view->start;                                            \
	}                                                                      \
                                                                               \
	size_t name##_length(name* view)                                       \
	{                                                                      \
		return view->length;                                           \
	}                                                                      \
                                                                               \
	elem_type* name##_underlying_array(name* view)                         \
	{                                                                      \
		return view->array;                                            \
	}                                                                      \
                                                                               \
	elem_type* name##_underlying_array_from_start(name* view)              \
	{                                                                      \
		return &view->array[view->start];                              \
	}                                                                      \
                                                                               \
	elem_type name##_get(name* view, size_t index)                         \
	{                                                                      \
		if (!name##_valid_index(view, index)) {                        \
			return invalid_value;                                  \
		}                                                              \
                                                                               \
		return view->array[view->start + index];                       \
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
			nh_util_compare_integers(view->length, other_length);  \
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
