#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <sys/random.h>

#include <list-char.h>
#include "./_common.h"

static char* generate_random_data(size_t bytes)
{
	char* data = malloc(bytes);
	getrandom(data, bytes, 0);
	for (size_t i = 0; i < bytes; i++) {
		// Ensure no null terminators mid-data
		data[i] |= 1;
	}
	return data;
}

int main(void)
{
	nh_list_char* list = nh_list_char_create();
	nh_list_char_add_right(list, 'b');
	nh_list_char_add_left(list, 'a');
	expect(list->length == 2, "List of length 2");

	nh_list_char_add_all_right_array(list, "cdefghijkl", 3);
	expect(strcmp(nh_list_char_underlying(list), "abcde") == 0,
	       "List contains 'abcde'");

	char const* prefix = "0123456789012345678901234567890123456789";
	for (int i = strlen(prefix) - 1; i >= 0; i--) {
		nh_list_char_add_left(list, prefix[i]);
	}
	expect(nh_list_char_equal_array(
		       list, "0123456789012345678901234567890123456789abcde"),
	       "List contains expected prefix data");

	char const* suffix = "fghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
	for (size_t i = 0; i < strlen(suffix); i++) {
		nh_list_char_add_right(list, suffix[i]);
	}
	expect(nh_list_char_equal_array(
		       list,
		       "0123456789012345678901234567890123456789abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"),
	       "List contains expected suffix data");

	size_t utf_8_bytes_added = nh_list_char_add_right_utf_8(list, 0x10348);
	expect(utf_8_bytes_added == 4, "Add UTF-8");
	expect((unsigned char) nh_list_char_get(list, -1) == 0x88,
	       "Fourth byte of UTF-8");
	expect((unsigned char) nh_list_char_get(list, -2) == 0x8D,
	       "Third byte of UTF-8");
	expect((unsigned char) nh_list_char_get(list, -3) == 0x90,
	       "Second byte of UTF-8");
	expect((unsigned char) nh_list_char_get(list, -4) == 0xF0,
	       "First byte of UTF-8");
	expect(nh_list_char_get(list, -5) == 'z',
	       "List contains expected post-UTF-8 data");

	nh_list_char_clear(list);
	for (size_t i = 0; i < list->size; i++) {
		expect(list->data[i] == 0, "Cleared list");
	}

	char* random_suffix = generate_random_data(1024);
	nh_list_char* random_suffix_list = nh_list_char_create_of_size(0, 1);
	nh_list_char_add_all_right_array(random_suffix_list, random_suffix,
					 1024);
	expect(nh_list_char_equal_array(random_suffix_list, random_suffix),
	       "List contains random data");

	nh_list_char_add_all_right_list(list, random_suffix_list);
	expect(nh_list_char_equal_array(list, random_suffix),
	       "List contains random suffix data");
}
