#pragma once

/**
 * Helper macro to provide a string literal and its length as parameter
 * arguments.
 *
 * @param str string literal
 */
#define nh_litarr(str) str, sizeof(str) - 1

/**
 * Compare the value of an integer to another.
 *
 * @param a integer to compare against
 * @param b integer to compare to
 * @return -1 if `a < b`, 0 if `a == b`, 1, if `a > b`
 */
int nh_util_compare_integers(int a, int b)
{
	return (a > b) - (a < b);
}

/**
 * Compare the value of a size_t value to another.
 *
 * @param a size_t to compare against
 * @param b size_t to compare to
 * @return -1 if `a < b`, 0 if `a == b`, 1, if `a > b`
 */
int nh_util_compare_sizes(size_t a, size_t b)
{
	return (a > b) - (a < b);
}

/**
 * Get the lowercase version of an ASCII character, if available.
 *
 * @param c character to lowercase
 * @return corresponding lowercase character, if `c` is an uppercase alphabet
 * character `[A-Z]`
 */
char nh_util_lowercase(char c)
{
	return c < 'A' || c > 'Z' ? c : c + 32;
}
