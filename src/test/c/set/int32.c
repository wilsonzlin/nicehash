#include <stdio.h>
#include "../../../main/c/set/int32.h"

int main(void) {
  nh_id_t set1 = nh_set_int32_create();
  printf("Created set 1 with ID: %ld\n", set1);

  nh_id_t set2 = nh_set_int32_create();
  printf("Created set 2 with ID: %ld\n", set2);

  nh_set_int32_add(set1, 42);
  printf("Added 42\n");

  printf("Has 42: %d\n", nh_set_int32_has(set1, 42));
  printf("Has 33: %d\n", nh_set_int32_has(set1, 33));
  printf("Has 42: %d\n", nh_set_int32_has(set1, 42));
  printf("Has 15: %d\n", nh_set_int32_has(set1, 15));
  printf("Deleted 42: %d\n", nh_set_int32_delete(set1, 42));
  printf("Deleted 15: %d\n", nh_set_int32_delete(set1, 15));
  printf("Deleted 42: %d\n", nh_set_int32_delete(set1, 42));
  printf("Has 42: %d\n", nh_set_int32_has(set1, 42));

  nh_set_int32_add(set1, 42);
  printf("Added 42\n");

  printf("Has 42: %d\n", nh_set_int32_has(set1, 42));

  nh_set_int32_clear(set1);
  printf("Cleared set 1\n");

  printf("Has 42: %d\n", nh_set_int32_has(set1, 42));

  nh_set_int32_add(set1, 42);
  printf("Added 42\n");

  printf("Has 42: %d\n", nh_set_int32_has(set1, 42));
}
