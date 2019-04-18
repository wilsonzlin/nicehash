#include <stdio.h>
#include <set-ascii.h>
#include "./_common.h"

int main(void)
{
	nh_set_ascii* set = nh_set_ascii_create();

	nh_set_ascii_add(set, 'x');

	expect(nh_set_ascii_has(set, 'x'), "Has 'x' initially");
	expect_false(nh_set_ascii_has(set, 'z'), "Has 'z'");
	expect(nh_set_ascii_has(set, 'x'), "Has 'x' secondly");
	expect_false(nh_set_ascii_has(set, 'y'), "Has 'y'");
	expect(nh_set_ascii_delete(set, 'x'), "Deleted 'x'");
	expect_false(nh_set_ascii_delete(set, 'y'), "Deleted 'y'");
	expect_false(nh_set_ascii_delete(set, 'x'), "Deleted 'x' secondly");
	expect_false(nh_set_ascii_has(set, 'x'), "Has 'x' thirdly");

	nh_set_ascii_add(set, 'x');

	expect(nh_set_ascii_has(set, 'x'), "Has 'x' fourthly");

	nh_set_ascii_clear(set);

	expect_false(nh_set_ascii_has(set, 'x'), "Has 'x' after clearing");

	expect(nh_set_ascii_add(set, '\0'), "Add NUL");
	expect(nh_set_ascii_has(set, '\0'), "Has NUL");
	expect_false(nh_set_ascii_add(set, '\0'), "Add NUL again");
	expect(nh_set_ascii_has(set, '\0'), "Has NUL secondly");
	expect(nh_set_ascii_delete(set, '\0'), "Delete NUL");
	expect_false(nh_set_ascii_has(set, '\0'), "Has NUL thirdly");
	expect_false(nh_set_ascii_delete(set, '\0'), "Delete NUL again");

	nh_set_ascii_add(set, 'x');

	expect(nh_set_ascii_has(set, 'x'), "Has 'x' fifthly");

	expect_false(nh_set_ascii_add(set, '\x80'), "Add non-ASCII U+0080");
	expect_false(nh_set_ascii_add(set, '\x81'), "Add non-ASCII U+0081");
	expect_false(nh_set_ascii_add(set, '\xFF'), "Add non-ASCII U+00FF");

	expect_false(nh_set_ascii_has(set, '\x80'), "Has non-ASCII U+0080");
	expect_false(nh_set_ascii_has(set, '\x81'), "Has non-ASCII U+0081");
	expect_false(nh_set_ascii_has(set, '\xFF'), "Has non-ASCII U+00FF");

	expect_false(nh_set_ascii_delete(set, '\x80'),
		     "Delete non-ASCII U+0080");
	expect_false(nh_set_ascii_delete(set, '\x81'),
		     "Delete non-ASCII U+0081");
	expect_false(nh_set_ascii_delete(set, '\xFF'),
		     "Delete non-ASCII U+00FF");
}
