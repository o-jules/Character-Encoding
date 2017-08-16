#include "types.h"
#include "vars.h"
#include "encode.h"

/// 检测Unicode字符的区间
int detect_char(Codepoint cp)
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

/// 编码，将Unicode codepoint转换成字节流
ByteStream *encode(Codepoint point)
{
  int count = detect_char(point);
  if (count == 0)
    return nullptr;

  ByteStream *list = new ByteStream();

  if (count == 1)
  {
    list->push_back((Byte)point);
  }
  else
  {
    int i = count, s = count - 1, j = 0;
    Byte b;
    while (i-- > 0)
    {
      j = i * 6;
      b = point >> j;
      point &= ~(b << j);
      j = i == s ? 7 - i : 7;
      list->push_back(b |= ~0 >> j << j);
    }
  }

  return list;
}
