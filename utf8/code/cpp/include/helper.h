#ifndef _UTF8_HELPER_H
#define _UTF8_HELPER_H

#include "types.h"
#include "vars.h"

namespace utf8
{
/// 函数声明
u32 lpad(u8 const &, size_t const &);
int ldrop(size_t);
int detect_byte(u8 const &);
int detect_char(u32 const &);

static const u8 FULL_BYTE = ~(u8)0u;

/// 内部函数，不作为提供给外部的API使用
/// 按位数的六倍向右(相当于乘以 2 ^ (6 * n))
inline u32 lpad(u8 const &b, size_t const &d)
{
  return ((u32)b) << (d * 6);
};

/// 内部函数，不作为提供给外部的API使用
/// 移除字节二进制左侧的 n 个 1
inline int ldrop(size_t i)
{
  i = 8 - i;
  return FULL_BYTE >> i << i;
};


/**
 * 检测该字节属于哪一种
 */
int detect_byte(u8 const &b)
{
  if (b < B10X)
    return 1;
  if (b >= B11110X)
    return 4;
  if (b >= B1110X)
    return 3;
  if (b >= B110X)
    return 2;

  return 0;
};


/// 检测Unicode字符的区间
int detect_char(u32 const &cp)
{
  if (cp <= U1_L)
    return 1;
  if (cp <= U2_L)
    return 2;
  if (cp <= U3_L)
    return 3;
  if (cp <= U4_L)
    return 4;

  return 0;
};

} // namespace utf8

#endif
