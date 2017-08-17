#ifndef _UTF8_DECODE_H
#define _UTF8_DECODE_H

#include <cstdio>
#include "types.h"
#include "vars.h"
#include "helper.h"

namespace utf8
{
int detect_byte(u8 const &);
codepoints *decode(bytes &);

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

/**
 * @param bs 字符流（类型为 std::vector<u8>）
 *
 * 对字节流进行解码，这里不对BOM进行检测和处理。
 */
codepoints *decode(bytes &bs)
{
  auto str = new codepoints();

  u64 cp = 0; // 当前的Unicode codepoint
  int state = 0, // 当前的状态
      acc = 0; // 当前的积累
  int size = 0;

  for (auto const &b : bs)
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
        cp |= lpad(b ^ B10X, state - acc);
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

        cp = size == 1 ? (u64)b : lpad(b ^ ldrop(size), size - 1);
        state = size;
        acc = 1;
      }
    }
  }

  if (state != 0)
    str->push_back(cp);

  return str;
};

} // end of namespace

#endif
