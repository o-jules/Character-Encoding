#include <cstdio>
#include "types.h"
#include "bom.h"

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    printf("File name missing.");
    return 1;
  }

  FILE *pfile = fopen(argv[1], "rb");
  if (!pfile)
  {
    printf("File open failed.");
    return 1;
  }

  if (isBOM(pfile))
    printf("UTF8 with BOM\n");
  else
    printf("UTF8 without BOM\n");

  printf("Bytes:\n");
  Byte b;
  while (fread(&b, BYTE_SIZE, 1, pfile))
  {
    printf("%d ", b);
  }

  return 0;
}
