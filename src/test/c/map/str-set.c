#include <stdio.h>
#include <stdint.h>
#include "../../../main/c/set/str.h"
#include "../../../main/c/map/str.h"

NICEHASH_MAP_STR(strset, nh_set_str_t)

int main(void) {
  nh_map_str_strset_t map1 = nh_map_str_strset_create();

  nh_set_str_t setA = nh_set_str_create();
  nh_set_str_add(setA, "A.1");
  nh_set_str_add(setA, "A.2");
  nh_set_str_add(setA, "A.3");
  nh_map_str_strset_set(map1, "A", setA);

  nh_set_str_t setB = nh_set_str_create();
  nh_set_str_add(setB, "B.1");
  nh_set_str_add(setB, "B.2");
  nh_set_str_add(setB, "B.3");
  nh_map_str_strset_set(map1, "B", setB);

  printf("Has 'A': %d\n", nh_map_str_strset_has(map1, "A"));
  printf("Has 'B': %d\n", nh_map_str_strset_has(map1, "B"));
  printf("Has 'C': %d\n", nh_map_str_strset_has(map1, "C"));

  printf("Has 'A.1': %d\n", nh_set_str_has(nh_map_str_strset_get(map1, "A", NULL), "A.1"));
}
