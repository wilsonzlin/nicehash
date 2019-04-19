#pragma once

#include "./bitfield.h"

#define NH_BITFIELD_ASCII(name) NH_BITFIELD(name, char, 128)

NH_BITFIELD_ASCII(nh_bitfield_ascii)
