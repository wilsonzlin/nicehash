#pragma once

#include <stdbool.h>
#include "../lib/khash.h"

#define _NH_HASH_BASE_IMPL(name, key_type)                                     \
	typedef khash_t(name) name;                                            \
                                                                               \
	name* name##_create(void)                                              \
	{                                                                      \
		name* t = kh_init(name);                                       \
		return t;                                                      \
	}                                                                      \
                                                                               \
	void name##_destroy(name* t)                                           \
	{                                                                      \
		kh_destroy(name, t);                                           \
	}                                                                      \
                                                                               \
	/**                                                                    \
	 * Check whether an element or key exists.                             \
	 *                                                                     \
	 * @param t map or set                                                 \
	 * @param k element/key to check for                                   \
	 * @return `true` if element/key exists, `false` otherwise             \
	 */                                                                    \
	bool name##_has(name* t, key_type k)                                   \
	{                                                                      \
		khint_t bucket = kh_get(name, t, k);                           \
		return bucket != kh_end(t);                                    \
	}                                                                      \
                                                                               \
	/**                                                                    \
	 * Delete an element or entry associated with a key.                   \
	 *                                                                     \
	 * @param t map or set                                                 \
	 * @param k element/key to remove                                      \
	 * @return `true` if the element/key existed before deleting, `false`  \
	 * otherwise                                                           \
	 */                                                                    \
	bool name##_delete(name* t, key_type k)                                \
	{                                                                      \
		khint_t bucket = kh_get(name, t, k);                           \
		if (bucket != kh_end(t)) {                                     \
			kh_del(name, t, bucket);                               \
			return true;                                           \
		}                                                              \
		return false;                                                  \
	}                                                                      \
                                                                               \
	/**                                                                    \
	 * Remove all elements or entries.                                     \
	 *                                                                     \
	 * @param t map or set                                                 \
	 */                                                                    \
	void name##_clear(name* t)                                             \
	{                                                                      \
		for (khint_t bucket = kh_begin(t); bucket != kh_end(t);        \
		     ++bucket) {                                               \
			if (kh_exist(t, bucket)) {                             \
				kh_del(name, t, bucket);                       \
			}                                                      \
		}                                                              \
	}
