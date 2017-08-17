#ifndef _UTF8_VARS_H
#define _UTF8_VARS_H

#include "types.h"

namespace utf8
{
static const u8 B10X = 128u;
static const u8 B110X = 192u;
static const u8 B1110X = 224u;
static const u8 B11110X = 240u;

// Unicode range
static const u64 U1_F = 0x0000ul;
static const u64 U1_L = 0x007ful;

static const u64 U2_F = 0x0080ul;
static const u64 U2_L = 0x07fful;

static const u64 U3_F = 0x0800ul;
static const u64 U3_L = 0xfffful;

static const u64 U4_F = 0x10000ul;
static const u64 U4_L = 0x10fffful;
} // end of namespace

#endif
