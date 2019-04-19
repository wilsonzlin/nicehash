#include <stdio.h>
#include <stdint.h>
#include <map-view-str.h>
#include "./_common.h"

NH_MAP_VIEW_ISTR(nh_map_view_istr_int32, int32_t, -1)

int main(void)
{
	char* alpha = "abcdefghijklmnopqrstuvwxyz";

	nh_view_str* view_whole_bCDe = nh_view_str_of_whole_literal("bCDe");
	nh_view_str* view_sub_bcde = nh_view_str_create(alpha, 1, 4);
	nh_view_str* view_sub_abcd = nh_view_str_create(alpha, 0, 3);

	nh_map_view_istr_int32* map1 = nh_map_view_istr_int32_create();

	nh_map_view_istr_int32_set(map1, view_whole_bCDe, 100);

	expect(nh_map_view_istr_int32_has(map1, view_whole_bCDe),
	       "Has existing");

	expect(nh_map_view_istr_int32_has(map1, view_sub_bcde),
	       "Has existing but different view");

	expect(nh_map_view_istr_int32_get(map1, view_sub_bcde) == 100,
	       "Get existing but different view");

	expect_false(
		nh_map_view_istr_int32_has(map1, view_sub_abcd),
		"Does not have view with same underlying array but different indices");

	expect(nh_map_view_istr_int32_get_whole_array(map1, nh_litarr("bcde"))
		       == 100,
	       "Get existing whole literal");

	expect_false(
		nh_map_view_istr_int32_has_whole_array(map1, nh_litarr("bcd")),
		"Does not have non-existent whole literal");

	expect(nh_map_view_istr_int32_delete_whole_array(map1,
							 nh_litarr("bcde")),
	       "Delete existing whole literal");

	expect_false(
		nh_map_view_istr_int32_has_whole_array(map1, nh_litarr("bcde")),
		"Does not have deleted whole literal");
}
