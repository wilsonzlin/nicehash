#pragma once

/**
 * Helper macro to provide a string literal and its length as parameter
 * arguments.
 *
 * @param str string literal
 */
#define nh_litarr(str) str, sizeof(str) - 1

/**
 * Helper macro to compare the value of an integer to another.
 *
 * @param a integer to compare against
 * @param b integer to compare to
 * @return -1 if `a < b`, 0 if `a == b`, 1, if `a > b`
 */
#define nh_util_compare_integers(a, b) ((a > b) - (a < b))

/**
 * Helper macro to get the lowercase version of an ASCII character, if
 * available.
 *
 * @param c character to lowercase
 * @return corresponding lowercase character, if `c` is an uppercase alphabet
 * character `[A-Z]`
 */
#define nh_util_lowercase(c) (c < 'A' || c > 'Z' ? c : c + 32)
