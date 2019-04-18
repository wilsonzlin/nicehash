#include <stdio.h>
#include <set-view-str.h>
#include "./_common.h"

int main(void)
{
	nh_set_view_str* set = nh_set_view_str_create();

	nh_set_view_str_add_whole_literal(set, "existing");

	expect(nh_set_view_str_has_whole_literal(set, "existing"),
	       "Has 'existing' 1");
	expect_false(nh_set_view_str_has_whole_literal(set, "unknown"),
		     "Has 'unknown'");
	expect(nh_set_view_str_has_whole_literal(set, "existing"),
	       "Has 'existing' 2");
	expect_false(nh_set_view_str_has_whole_literal(set, "imaginary"),
		     "Has 'imaginary'");
	expect(nh_set_view_str_delete_whole_literal(set, "existing"),
	       "Deleted 'existing' 1");
	expect_false(nh_set_view_str_delete_whole_literal(set, "imaginary"),
		     "Deleted 'imaginary'");
	expect_false(nh_set_view_str_delete_whole_literal(set, "existing"),
		     "Deleted 'existing' 2");
	expect_false(nh_set_view_str_has_whole_literal(set, "existing"),
		     "Has 'existing' 3");

	nh_set_view_str_add_whole_literal(set, "existing");

	expect(nh_set_view_str_has_whole_literal(set, "existing"),
	       "Has 'existing' 4");

	nh_set_view_str_clear(set);

	expect_false(nh_set_view_str_has_whole_literal(set, "existing"),
		     "Has 'existing' 5");

	nh_set_view_str_add_whole_literal(set, "existing");

	expect(nh_set_view_str_has_whole_literal(set, "existing"),
	       "Has 'existing' 6");
}
