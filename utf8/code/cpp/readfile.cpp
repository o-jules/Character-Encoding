#include <cstdio>
#include "types.h"

Byte BOM[3] = {239, 187, 191};

bool isBom(FILE *pfile)
{
  Byte b;
  int i = 0;
  while (fread(&b, BYTE_SIZE, 1, pfile))
  {
    if (b != BOM[i] || i >= 3)
      break;
    i++;
  }

  return i == 3;
}

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    return 1;
  }

  FILE *pfile = fopen(argv[1], "rb");
  if (!pfile)
  {
    printf("File open failed.");
    return 1;
  }

  if (isBom(pfile))
    printf("UTF8 with BOM\n");
  else
    printf("UTF8 without BOM\n");

  return 0;
}
