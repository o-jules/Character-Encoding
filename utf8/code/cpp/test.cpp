#include <cstdio>
#include "include/types.h"
#include "include/decode.h"
#include "include/encode.h"

int main(int argc, char **argv)
{
  FILE *pfile = fopen("utf8.txt", "rb");
  if (!pfile)
  {
    printf("File open failed.");
    return 1;
  }

  utf8::bytes bs;
  utf8::u8 b;
  while (fread(&b, utf8::BYTE_SIZE, 1, pfile))
  {
    bs.push_back(b);
    printf("%d ", b);
  }
  printf("\n");

  auto cs = utf8::decode(bs);
  printf("Decoding:\n");
  for (auto &p : *cs)
  {
    printf("dec: %09llu\thex: %06llx\n", p, p);
  }
  // release dynamic memory
  delete cs;

  /*
  utf8::u64 cp = 19990L; //'世';
  utf8::bytes *dc;
  dc = utf8::encode(cp);
  printf("Encoding:\n");
  for (auto &p : *dc) {
    printf("%u\n", p);
  }
  */

  return 0;
}
