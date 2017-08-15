#include "types.h"
#include "decode.h"

int main(int argc, char **argv)
{
  FILE *pfile = fopen("utf8.txt", "rb");
  if (!pfile)
  {
    printf("File open failed.");
    return 1;
  }

  ByteStream bs;
  Byte b;
  while (fread(&b, BYTE_SIZE, 1, pfile))
  {
    bs.push_back(b);
  }

  auto cs = decode(bs);
  for (auto &p : *cs)
  {
    printf("dec: %09llu\thex: %06llx\n", p, p);
  }

  return 0;
}
