#include <cstdio>
#include "include/types.h"
#include "include/decode.h"
#include "include/encode.h"
#include "include/io.h"
#include "include/validate.h"

int main(int argc, char **argv)
{
  FILE *fw;

  auto cs = utf8::decode_file("utf8.txt");
  printf("Decoding:\n");
  fw = fopen("write.utf32.tmp", "wb");
  for (auto &p : *cs)
  {
    printf("dec: %08u\thex: %06x\n", p, p);
    fwrite(&p, utf8::CODEPOINT_SIZE, 1, fw);
  }
  // release dynamic memory
  fclose(fw);
  delete cs;

  utf8::codepoints cp = { 72L, 19990L, 30028L, 131123L }; //'H', 世', '界', '𠀳';
  auto dc = utf8::encode(cp);
  printf("\nEncoding:\n");

  fw = fopen("write.utf8.tmp", "wb");
  for (auto &p : *dc) {
    printf("%x-%u ", p, p);
    fwrite(&p, utf8::BYTE_SIZE, 1, fw);
  }
  printf("\n");
  fclose(fw);

  return 0;
}
