#pragma once

#include <stdlib.h>

void expect(int value, char const* message) {
  if (!value) {
    printf("Test failed: %s\n", message);
    exit(EXIT_FAILURE);
  }
}

void expect_false(int value, char const* message) {
  expect(!value, message);
}
