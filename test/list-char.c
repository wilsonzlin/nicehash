#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "list-char.h"
#include "./_common.h"

int main(void) {
  nh_list_char* list = nh_list_char_create();
  nh_list_char_add_right(list, 'b');
  nh_list_char_add_left(list, 'a');
  expect(list->length == 2, "List of length 2");

  nh_list_char_add_all_right_arr(list, "cdefghijkl", 3);
  expect(strcmp(nh_list_char_underlying(list), "abcde") == 0, "List contains 'abcde'");
}
