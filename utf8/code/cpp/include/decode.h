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

  bool fatal = false;
  u64 cp = 0; // 当前的Unicode codepoint
  int s = 0,  // 之前/当前的状态，state
      a = 0,  // 当前的积累, accumulation
      i = 0;  // 临时数据

  for (auto const &b : bs)
  {
    i = detect_byte(b);

    if (i == 0)
    {
      // 编码存在错误，后续的字节多于所需
      if (a + 1 > s)
      {
        printf("Encoding contains errors.");
        break;
      }
      else
      {
        a++;
        cp |= lpad(b ^ B10X, s - a);
      }
    }
    else
    {
      // 编码中存在错误，已存储的字节无效
      if (s - a != 0)
      {
        printf("Encoding contains errors.");
        fatal = true;
        break;
      }
      else
      {
        if (s != 0)
          str->push_back(cp);

        cp = i == 1 ? (u64)b : lpad(b ^ ldrop(i), i - 1);
        s = i;
        a = 1;
      }
    }
  }

  if (s != 0 && !fatal)
    str->push_back(cp);

  return str;
};

} // end of namespace

#endif
