#include <cstdio>
#include "include/types.h"

int print_file(const char *file_path) {
  utf8::u8 b;
  FILE *pfile;
  pfile = fopen(file_path, "rb");

  if (!pfile) {
    fprintf(stderr, "File open failed.\n");
    return 1;
  }

  while (fread(&b, utf8::BYTE_SIZE, 1, pfile)) {
    printf("%d ", b);
  }
  printf("\n");

  return 0;
}

void print_string(const char *str) {
  utf8::u8 *b;
  b = (utf8::u8 *)str;
  while (*b != '\0') {
    printf("%d ", *b);
    b++;
  }
  printf("\n");
}
