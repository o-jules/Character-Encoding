#include "types.h"
#include "encode.h"

/// 检测Unicode字符的区间
int detect_char(Codepoint cp)
{
  if (cp <= 0x007f)
    return 1;
  if (cp <= 0x07ff)
    return 2;
  if (cp <= 0xffff)
    return 3;
  if (cp <= 0x10ffff)
    return 4;

  return 0;
}

/// 编码，将Unicode codepoint转换成字节流
ByteStream *encode(Codepoint cp)
{
  int count = detect_char(cp);
  if (count == 0)
    return nullptr;

  ByteStream *list = new ByteStream();

  if (count == 1)
  {
    list->push_back((Byte)cp);
  }
  else
  {
    int order = count - 1, pad = 0;
    Byte byte;
    while (order >= 0)
    {
      int pad = order * 6;
      byte = cp >> pad;
      cp &= ~(byte << pad);
      pad = order == count - 1 ? 7 - order : 7;
      byte |= ~0 >> pad << pad;
      list->push_back(byte);
      order--;
    }
  }

  return list;
}
