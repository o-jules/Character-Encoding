#include <cstdio>
#include "types.h"
#include "decode.h"

/// 按位数向右(相当于乘以 2 ^ n)
#define LPAD(b, p) (b) * (1 << ((p)*6))

/// 移除字节二进制左侧的 n 个1
#define LDROP(b, n) b ^= (~0 >> (8 - n) << (8 - n))

int detect_byte(Byte b)
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

CodepointStream *decode(ByteStream &bs)
{
  CodepointStream *str = new CodepointStream();

  Codepoint cp = 0; // code point
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
        cp += LPAD(LDROP(b, 1), state - acc);
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
        cp = (Codepoint) (size == 1 ? b : LPAD(LDROP(b, size), size - 1));
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
