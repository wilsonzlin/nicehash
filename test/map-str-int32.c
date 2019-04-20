#include "./_common.h"
#include <map-str.h>
#include <stdint.h>
#include <stdio.h>

NH_MAP_STR_PROTO(nh_map_str_int32, int32_t)
NH_MAP_STR_IMPL(nh_map_str_int32, int32_t, -1)

int main(void)
{
	nh_map_str_int32* map1 = nh_map_str_int32_create();

	nh_map_str_int32_set(map1, "existing", 100);

	expect(nh_map_str_int32_has(map1, "existing"), "Has 'existing'");
	expect_false(nh_map_str_int32_has(map1, "unknown"), "Has 'unknown'");
	expect(nh_map_str_int32_get(map1, "existing") == 100, "Get 'existing'");
	expect(nh_map_str_int32_get(map1, "unknown") == -1, "Get 'unknown'");

	nh_map_str_int32_set(map1, "existing", 420);

	expect(nh_map_str_int32_get(map1, "existing") == 420, "Get 'existing'");
	expect(nh_map_str_int32_delete(map1, "existing"), "Delete 'existing'");
	expect_false(nh_map_str_int32_delete(map1, "existing"),
		     "Delete 'existing'");
	expect(nh_map_str_int32_get(map1, "existing") == -1, "Get 'existing'");
}
