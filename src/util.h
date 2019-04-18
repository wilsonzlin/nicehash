#pragma once

int nh_util_compare_integers(int a, int b)
{
	return (a > b) - (b - a);
}

char nh_util_lowercase(char c)
{
	return c < 'A' || c > 'Z' ? c : c + 32;
}
