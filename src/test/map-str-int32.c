#include <stdio.h>
#include <stdint.h>
#include "../../../main/c/map/str.h"

NICEHASH_MAP_STR(int32, int32_t)

int main(void) {
  nh_map_str_int32_t map1 = nh_map_str_int32_create();

  nh_map_str_int32_set(map1, "existing", 100);
  printf("Set 'existing' to 100\n");

  printf("Has 'existing': %d\n", nh_map_str_int32_has(map1, "existing"));
  printf("Has 'unknown': %d\n", nh_map_str_int32_has(map1, "unknown"));
  printf("Get 'existing': %d\n", nh_map_str_int32_get(map1, "existing", -1));
  printf("Get 'unknown': %d\n", nh_map_str_int32_get(map1, "unknown", -1));

  nh_map_str_int32_set(map1, "existing", 420);
  printf("Set 'existing' to 420\n");

  printf("Get 'existing': %d\n", nh_map_str_int32_get(map1, "existing", -1));
  printf("Delete 'existing': %d\n", nh_map_str_int32_delete(map1, "existing"));
  printf("Delete 'existing': %d\n", nh_map_str_int32_delete(map1, "existing"));
  printf("Get 'existing': %d\n", nh_map_str_int32_get(map1, "existing", -1));
}
