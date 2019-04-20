#pragma once

#include "./bitfield.h"

#define NH_BITFIELD_ASCII_PROTO(name) NH_BITFIELD_PROTO(name, char, 128)

#define NH_BITFIELD_ASCII_IMPL(name) NH_BITFIELD_IMPL(name, char, 128)

NH_BITFIELD_ASCII_PROTO(nh_bitfield_ascii)
