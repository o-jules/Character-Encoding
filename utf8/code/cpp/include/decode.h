#ifndef _UTF8_DECODE_H
#define _UTF8_DECODE_H

#include <cstdio>
#include "types.h"
#include "vars.h"
#include "helper.h"

namespace utf8
{
codepoints *decode(bytes &);

/**
 * @param bs 字符流（类型为 std::vector<u8>）
 *
 * 对字节流进行解码，这里不对BOM进行检测和处理。
 */
codepoints *decode(bytes &bs)
{
  auto str = new codepoints();

  u64 cp = 0; // 当前的Unicode codepoint
  int s = 0,  // 之前/当前的状态，state
      a = 0,  // 当前的积累, accumulation
      i = 0;  // 临时数据

  for (auto const &b : bs)
  {
    i = detect_byte(b);

    if (i == 0)
    {
      if (a >= s)
      {
        // 编码存在错误，后续的字节多于所需
        printf("Errors: bytes overflow.");
        break;
      }
      else
      {
        a++;
        cp |= lpad(b ^ B10X, s - a);
        if (s == a)
          str->push_back(cp);
      }
    }
    else
    {
      if (s != a)
      {
        // 编码中存在错误，前一字符的编码不足
        printf("Errors: bytes not sufficient.");
        break;
      }
      else
      {
        s = i;
        a = 1;

        if (i == 1)
          str->push_back((u64)b);
        else
          cp = lpad(b ^ ldrop(i), i - 1);
      }
    }
  }

  return str;
};

} // end of namespace

#endif
