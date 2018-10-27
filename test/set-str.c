#include <stdio.h>
#include "../src/set-str.h"
#include "./_common.c"

int main(void) {
  nh_set_str_t set = nh_set_str_create();

  nh_set_str_add(set, "existing");

  expect(nh_set_str_has(set, "existing"), "Has 'existing' 1");
  expect_false(nh_set_str_has(set, "unknown"), "Has 'unknown'");
  expect(nh_set_str_has(set, "existing"), "Has 'existing' 2");
  expect_false(nh_set_str_has(set, "imaginary"), "Has 'imaginary'");
  expect(nh_set_str_delete(set, "existing"), "Deleted 'existing' 1");
  expect_false(nh_set_str_delete(set, "imaginary"), "Deleted 'imaginary'");
  expect_false(nh_set_str_delete(set, "existing"), "Deleted 'existing' 2");
  expect_false(nh_set_str_has(set, "existing"), "Has 'existing' 3");

  nh_set_str_add(set, "existing");

  expect(nh_set_str_has(set, "existing"), "Has 'existing' 4");

  nh_set_str_clear(set);

  expect_false(nh_set_str_has(set, "existing"), "Has 'existing' 5");

  nh_set_str_add(set, "existing");

  expect(nh_set_str_has(set, "existing"), "Has 'existing' 6");
}
