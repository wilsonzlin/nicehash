#include <stdio.h>
#include <view-str.h>
#include "./_common.h"

int main(void)
{
	char* alpha = "abcdefghijklmnopqrstuvwxyz";

	nh_view_str* view_whole = nh_view_str_of_whole_literal("bcde");
	nh_view_str* view_sub_bcde = nh_view_str_create(alpha, 1, 4);
	nh_view_str* view_sub_abcd = nh_view_str_create(alpha, 0, 3);
	nh_view_str* view_sub_bcdef = nh_view_str_create(alpha, 1, 5);

	expect(nh_view_str_equals(view_whole, view_sub_bcde), "views equal");
	expect(!nh_view_str_equals(view_whole, view_sub_abcd),
	       "views do not equal");
	expect(!nh_view_str_equals(view_whole, view_sub_bcdef),
	       "views do not equal");
}
