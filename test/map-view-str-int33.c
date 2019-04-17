#include <stdio.h>
#include <stdint.h>
#include <map-view-str.h>
#include "./_common.h"

NH_MAP_VIEW_STR_CUSTOM_NAMES_DEFAULT_VALUE(view_str, int32_t, int32, -1)

int main(void)
{
	char* alpha = "abcdefghijklmnopqrstuvwxyz";

	nh_view_str* view_whole_bcde = nh_view_str_of_whole_literal("bcde");
	nh_view_str* view_sub_bcde = nh_view_str_create(alpha, 1, 4);
	nh_view_str* view_sub_abcd = nh_view_str_create(alpha, 0, 3);

	nh_map_view_str_int32* map1 = nh_map_view_str_int32_create();

	nh_map_view_str_int32_set(map1, view_whole_bcde, 100);

	expect(nh_map_view_str_int32_has(map1, view_whole_bcde),
	       "Has existing");
	expect(nh_map_view_str_int32_has(map1, view_sub_bcde),
	       "Has existing but different view");
	expect(nh_map_view_str_int32_get(map1, view_sub_bcde) == 100,
	       "Get existing but different view");
	expect(!nh_map_view_str_int32_has(map1, view_sub_abcd),
	       "Does not have view with same underlying array but different indices");
}
