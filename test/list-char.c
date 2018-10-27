#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../src/list-char.h"
#include "./_common.c"

int main(void) {
  nh_list_char_t list = nh_list_char_create();
  nh_list_char_append(list, 'b');
  nh_list_char_prepend(list, 'a');
  expect(list->length == 2, "List of length 2");

  nh_list_char_extend_arr(list, "cdefghijkl", 3);
  expect(strcmp(nh_list_char_underlying(list), "abcde") == 0, "List contains 'abcde'");
}
