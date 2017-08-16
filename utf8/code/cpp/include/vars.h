#ifndef _UTF8_VARS_H
#define _UTF8_VARS_H

#include "types.h"

namespace utf8 {
  static const u8 B10X = 128;
  static const u8 B110X = 192;
  static const u8 B1110X = 224;
  static const u8 B11110X = 240;

  // Unicode range
  static const u64 U1_F = 0x0000;
  static const u64 U1_L = 0x007f;

  static const u64 U2_F = 0x0080;
  static const u64 U2_L = 0x07ff;

  static const u64 U3_F = 0x0800;
  static const u64 U3_L = 0xffff;

  static const u64 U4_F = 0x10000;
  static const u64 U4_L = 0x10ffff;
}

#endif
