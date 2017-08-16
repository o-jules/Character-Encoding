#ifndef _BOM_H
#define _BOM_H

#include "types.h"

Byte BOM[3] = {239, 187, 191};

bool isBOM(FILE *f)
{
  Byte b;
  int i = 0;
  while (i <= 2)
  {
    if (!fread(&b, BYTE_SIZE, 1, f) || b != BOM[i])
      break;
    i++;
  }

  bool s = i == 3;
  if (!s)
    fseek(f, 0, SEEK_SET);
  return s;
}

#endif
