#ifndef _ENCODE_H
#define _ENCODE_H

#include "types.h"

Codepoint POW_BASES[] = {
    64,     // Math.pow(2, 6),
    4096,   // Math.pow(2, 12),
    262144, // Math.pow(2, 18),
};

Codepoint LEADINGS[] = {
    128, 192,
    224, 240,
};

ByteStream *encode(Codepoint cp)
{
  ByteStream *list = new ByteStream();
  if (cp <= 0x007f)
  {
    list->push_back((Byte)cp);
    return list;
  }

  int count = 0;
  if (cp <= 0x07ff)
  {
    count = 2;
  }
  else if (cp <= 0xffff)
  {
    count = 3;
  }
  else if (cp <= 0x10ffff)
  {
    count = 4;
  }
  else
  {
    // throw RangeError('Code point is out of range.');
  }

  int order = count - 1;
  Byte byte;
  while (order >= 0)
  {
    byte = cp >> (order * 6);
    cp -= byte * POW_BASES[order - 1];
    byte += LEADINGS[order == count - 1 ? order : 0];
    list->push_back(byte);
    order--;
  }

  return list;
}

#endif
