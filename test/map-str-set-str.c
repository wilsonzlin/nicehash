#include <stdio.h>
#include <stdint.h>
#include "set-str.h"
#include "map-str.h"
#include "./_common.h"

NH_MAP_STR(set_str, nh_set_str*, nh_set_str*, NULL)

int main(void)
{
	nh_map_str_set_str* map1 = nh_map_str_set_str_create();

	nh_set_str* setA = nh_set_str_create();
	nh_set_str_add(setA, "A.1");
	nh_set_str_add(setA, "A.2");
	nh_set_str_add(setA, "A.3");
	nh_map_str_set_str_set(map1, "A", setA);

	nh_set_str* setB = nh_set_str_create();
	nh_set_str_add(setB, "B.1");
	nh_set_str_add(setB, "B.2");
	nh_set_str_add(setB, "B.3");
	nh_map_str_set_str_set(map1, "B", setB);

	expect(nh_map_str_set_str_has(map1, "A"), "Has 'A'");
	expect(nh_map_str_set_str_has(map1, "B"), "Has 'B'");
	expect_false(nh_map_str_set_str_has(map1, "C"), "Has 'C'");

	expect(nh_set_str_has(nh_map_str_set_str_get(map1, "A"), "A.1"),
	       "Has 'A.1'");
}
