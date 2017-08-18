#include <cstdio>
#include "include/types.h"
#include "include/bom.h"

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

  if (utf8::contains_bom(pfile))
    printf("UTF8 with BOM\n");
  else
    printf("UTF8 without BOM\n");

  printf("Bytes:\n");
  utf8::u8 b;
  while (fread(&b, utf8::BYTE_SIZE, 1, pfile))
  {
    printf("%d ", b);
  }
  printf("\n");

  return 0;
}
