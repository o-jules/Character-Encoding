#include <cstdio>
#include "types.h"
#include "decode.h"
#include "encode.h"

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
  // release dynamic memory
  delete cs;

  Codepoint cp = 19990L; //'世';
  ByteStream *dc;
  dc = encode(cp);
  printf("Decoding:\n");
  for (auto &p : *dc) {
    printf("%u\n", p);
  }

  return 0;
}
