#include <cstdio>
#include "include/types.h"
#include "include/decode_buffer.h"

int main(int argc, char **argv)
{
  utf8::u8 b;

  FILE *pfile;
  pfile = fopen("samples/utf8.txt", "rb");

  if (!pfile)
  {
    printf("File open failed.");
    return 1;
  }

  auto bf = utf8::DecodeBuffer();
  while (fread(&b, utf8::BYTE_SIZE, 1, pfile)) {
    try {
      getchar();
      printf("%u ", b);
      if (bf.push(b)) {
        printf("character: %llu\n", bf.current());
      }
    } catch (int e) {
      break;
    }
  }

  return 0;
}
