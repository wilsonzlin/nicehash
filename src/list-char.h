#pragma once

#include <stdint.h>
#include <string.h>
#include "./list.h"

NH_LIST(nh_list_char, uint8_t, sizeof(uint8_t), int16_t, -1)

int nh_list_char_compare(nh_list_char_t a, nh_list_char_t b) {
  return strcmp(nh_list_char_underlying(a), nh_list_char_underlying(b));
}
