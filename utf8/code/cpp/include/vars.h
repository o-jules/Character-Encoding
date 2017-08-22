#ifndef _UTF8_VARS_H
#define _UTF8_VARS_H

#include "types.h"

namespace utf8
{
static const int ENCODE_ERROR = 1;

static const u8 B10X = 128u;    // 0b10000000u
static const u8 B110X = 192u;   // 0b11000000u
static const u8 B1110X = 224u;  // 0b11100000u
static const u8 B11110X = 240u; // 0b11110000u

// Unicode range
static const u32 U1_F = 0x0000u;
static const u32 U1_L = 0x007Fu;

static const u32 U2_F = 0x0080u;
static const u32 U2_L = 0x07FFu;

static const u32 U3_F = 0x0800u;
static const u32 U3_L = 0xFFFFu;

static const u32 U4_F = 0x10000u;
static const u32 U4_L = 0x10FFFFu;
} // namespace utf8

#endif
