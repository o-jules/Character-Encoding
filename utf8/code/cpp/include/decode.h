#ifndef _UTF8_DECODE_H
#define _UTF8_DECODE_H

#include <cstdio>
#include "vars.h"
#include "types.h"
#include "decode.h"

namespace utf8
{

/// 按位数向右(相当于乘以 2 ^ n)
inline u64 lpad(u8 b, int d)
{
  return ((u64)b) << (d * 6);
}

/// 移除字节二进制左侧的 n 个1
inline int ldrop(size_t i)
{
  return ~0u >> (8 - i) << (8 - i);
}

/**
 * 检测该字节属于哪一种
 */
int detect_byte(u8 b)
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

/**
 * 对字节流进行解码，这里不对BOM进行检测和处理。
 */
codepoints *decode(bytes &bs)
{
  auto str = new codepoints();
  u64 cp = 0; // code point
  int state = 0, acc = 0;
  int size = 0;

  for (auto &b : bs)
  {
    size = detect_byte(b);

    if (size == 0)
    {
      // 编码中存在错误
      if (acc + 1 > state)
      {
        printf("Encoding contains errors.");
        break;
      }
      else
      {
        acc++;
        cp += lpad(b ^ ldrop(1), state - acc);
      }
    }
    else
    {
      // 编码中存在错误
      if (state - acc != 0)
      {
        printf("Encoding contains errors.");
        break;
      }
      else
      {
        if (state != 0)
          str->push_back(cp);

        if (size == 1)
        {
          cp = (u64)b;
        }
        else
        {
          cp = lpad(b ^ ldrop(size), size - 1);
        }
        state = size;
        acc = 1;
      }
    }
  }

  if (state != 0)
  {
    str->push_back(cp);
  }

  return str;
};
};

#endif
