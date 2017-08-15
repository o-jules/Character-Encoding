#include <cstdio>
#include "types.h"
#include "decode.h"

/// 按位数向右(相当于乘以 2 ^ n)
#define LPAD(b, p) (b) * (1 << ((p)*6))

unsigned int BASES[4] = {B10X, B110X, B1110X, B11110X};

int detect(Byte b)
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
  int state = 0, acc = 0;
  Codepoint cp = 0; // code point

  for (auto &b : bs)
  {
    int size = detect(b);

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
        cp += LPAD(b - B10X, state - acc);
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
        cp = size == 1 ? (Codepoint)b : LPAD(b - BASES[size - 1], size - 1);
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
