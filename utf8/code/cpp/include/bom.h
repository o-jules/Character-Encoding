#ifndef _UTF8_BOM_H
#define _UTF8_BOM_H

#include <cstdio>
#include "types.h"

namespace utf8
{

static const u8 BOM[3] = {239, 187, 191};

bool is_bom(FILE *f)
{
  u8 b;
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
};

} // end of namespace

#endif
