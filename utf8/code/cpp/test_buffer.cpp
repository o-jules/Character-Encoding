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
      // getchar();
      printf("dec = %u, hex = %x\n", b, b);
      if (bf.push(b)) {
        printf("character: dec = %llu, hex = %llx\n\n", bf.current(), bf.current());
      }
    } catch (int e) {
      break;
    }
  }

  return 0;
}
