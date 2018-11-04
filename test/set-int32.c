#include <stdio.h>
#include "set-int32.h"
#include "./_common.h"

int main(void) {
  nh_set_int32* set = nh_set_int32_create();

  nh_set_int32_add(set, 42);

  expect(nh_set_int32_has(set, 42), "Has 42 initially");
  expect_false(nh_set_int32_has(set, 33), "Has 33");
  expect(nh_set_int32_has(set, 42), "Has 42 secondly");
  expect_false(nh_set_int32_has(set, 15), "Has 15");
  expect(nh_set_int32_delete(set, 42), "Deleted 42");
  expect_false(nh_set_int32_delete(set, 15), "Deleted 15");
  expect_false(nh_set_int32_delete(set, 42), "Deleted 42 secondly");
  expect_false(nh_set_int32_has(set, 42), "Has 42 thirdly");

  nh_set_int32_add(set, 42);

  expect(nh_set_int32_has(set, 42), "Has 42 fourthly");

  nh_set_int32_clear(set);

  expect_false(nh_set_int32_has(set, 42), "Has 42 after clearing");

  nh_set_int32_add(set, 42);

  expect(nh_set_int32_has(set, 42), "Has 42 fifthly");
}
