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

	nh_set_ascii_add(set, 'x');

	expect(nh_set_ascii_has(set, 'x'), "Has 'x' fifthly");
}
