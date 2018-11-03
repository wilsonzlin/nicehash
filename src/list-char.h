#pragma once

#include <stdint.h>
#include <string.h>
#include "./list.h"

NH_LIST(nh_list_char, char, sizeof(char), char, '\0')

int nh_list_char_compare(nh_list_char_t a, nh_list_char_t b)
{
  return strcmp(nh_list_char_underlying(a), nh_list_char_underlying(b));
}

int hbu_list_char_compare_lit(nh_list_char_t a, char *const b)
{
  return strcmp(nh_list_char_underlying(a), b);
}
