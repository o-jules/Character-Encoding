#ifndef _UTF8_ENCODE_H
#define _UTF8_ENCODE_H
#include "types.h"
#include "vars.h"

namespace utf8
{

int detect_char(u64 const &);
bytes *encode(codepoints &);
bytes *encode_char(u64 &);

/// 检测Unicode字符的区间
int detect_char(u64 const &cp)
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
}

/**
 * 编码，将Unicode codepoint转换成字节流
 */
bytes *encode(codepoints &cplist)
{
  auto list = new bytes();

  u64 point = 0;
  for (auto &p : cplist)
  {
    int count = detect_char(p);
    if (count == 0)
      continue;

    point = p;
    if (count == 1)
    {
      list->push_back((u8)point);
    }
    else
    {
      int i = count, s = count - 1, j = 0;
      u8 b;
      while (i-- > 0)
      {
        j = i * 6;
        b = point >> j;
        point &= ~(b << j);
        j = i == s ? 7 - i : 7;
        list->push_back(b |= ~0ul >> j << j);
      }
    }
  }

  return list;
};

/**
 * 将单个 codepoint 编码
 */
bytes *encode_char(u64 &c)
{
  auto list = codepoints();
  list.push_back(c);
  return encode(list);
};

} // end of namespace

#endif
