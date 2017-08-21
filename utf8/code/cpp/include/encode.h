#ifndef _UTF8_ENCODE_H
#define _UTF8_ENCODE_H

#include "types.h"
#include "vars.h"
#include "helper.h"

namespace utf8
{
/// 函数声明
bytes *encode(codepoints &);
bytes *encode_char(u32 &);

/**
 * 编码，将Unicode codepoint转换成字节流
 */
bytes *encode(codepoints &cplist)
{
  auto list = new bytes();

  u32 p = 0ul;
  u8 b = 0u;
  int i = 0, // 字节数
      s = 0,
      j = 0; // 临时变量

  for (auto const &cp : cplist)
  {
    i = detect_char(cp);
    if (!i)
      continue;

    if (i == 1)
    {
      list->push_back((u8)cp);
    }
    else
    {
      p = cp;
      s = i - 1;
      while (i-- > 0)
      {
        j = i * 6;
        b = p >> j;
        p &= ~(b << j);
        b |= (i == s) ? ldrop(i + 1) : B10X;
        list->push_back(b);
      }
    }
  }

  return list;
};

/**
 * 将单个 codepoint 编码
 */
bytes *encode_char(u32 &c)
{
  auto list = codepoints();
  list.push_back(c);
  return encode(list);
};

} // end of namespace

#endif
