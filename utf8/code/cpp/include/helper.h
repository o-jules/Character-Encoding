#ifndef _UTF8_HELPER
#define _UTF8_HELPER

namespace utf8
{
/// 函数声明
u64 lpad(u8 const &, size_t const &);
int ldrop(size_t);

static const u8 FULL_BYTE = ~(u8)0u;

/// 内部函数，不作为提供给外部的API使用
/// 按位数的六倍向右(相当于乘以 2 ^ (6 * n))
inline u64 lpad(u8 const &b, size_t const &d)
{
  return ((u64)b) << (d * 6);
};

/// 内部函数，不作为提供给外部的API使用
/// 移除字节二进制左侧的 n 个 1
inline int ldrop(size_t i)
{
  i = 8 - i;
  return FULL_BYTE >> i << i;
};

} // end of namespace

#endif
