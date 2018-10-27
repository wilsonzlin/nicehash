#include <stdio.h>
#include "../../../main/c/set/str.h"

int main(void) {
  nh_set_str_t set1 = nh_set_str_create();

  nh_set_str_add(set1, "existing");
  printf("Added 'existing'\n");

  printf("Has 'existing': %d\n", nh_set_str_has(set1, "existing"));
  printf("Has 'unknown': %d\n", nh_set_str_has(set1, "unknown"));
  printf("Has 'existing': %d\n", nh_set_str_has(set1, "existing"));
  printf("Has 'imaginary': %d\n", nh_set_str_has(set1, "imaginary"));
  printf("Deleted 'existing': %d\n", nh_set_str_delete(set1, "existing"));
  printf("Deleted 'imaginary': %d\n", nh_set_str_delete(set1, "imaginary"));
  printf("Deleted 'existing': %d\n", nh_set_str_delete(set1, "existing"));
  printf("Has 'existing': %d\n", nh_set_str_has(set1, "existing"));

  nh_set_str_add(set1, "existing");
  printf("Added 'existing'\n");

  printf("Has 'existing': %d\n", nh_set_str_has(set1, "existing"));

  nh_set_str_clear(set1);
  printf("Cleared set 1\n");

  printf("Has 'existing': %d\n", nh_set_str_has(set1, "existing"));

  nh_set_str_add(set1, "existing");
  printf("Added 'existing'\n");

  printf("Has 'existing': %d\n", nh_set_str_has(set1, "existing"));
}
