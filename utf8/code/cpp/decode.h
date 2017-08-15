#include <cstdio>
#include <cstdlib>
#include <vector>
#include "types.h"

Byte BOM[3] = {239, 187, 191};
unsigned int BASES[] = {B10X, B110X, B1110X, B11110X};

/**
 * 按位数向右(相当于乘以 2 ^ n)
 */
Codepoint lpad(unsigned int base, unsigned int power)
{
  return base * (1 << (power * 6));
}

/**
 * 检测该字节属于哪一种
 */
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

/**
 * 对字节流进行解码，这里不对BOM进行处理。
 */
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
        cp += lpad(b - B10X, state - acc);
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
        cp = size == 1 ? (Codepoint)b : lpad(b - BASES[size - 1], size - 1);
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
}

