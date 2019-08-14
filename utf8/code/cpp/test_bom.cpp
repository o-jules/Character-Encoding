#include <cstdio>
#include "include/types.h"
#include "include/bom.h"

int main(int argc, char **argv) {
  const char *files[4] = {
    "samples/utf8.txt",
    "samples/utf8bom.txt",
    "samples/utf8bom-only.txt",
    "samples/utf8bom-efbb.txt"
  };

  for (int i = 0; i < 4; i++) {
    FILE *pfile = fopen(files[i], "rb");
    if (!pfile) {
      fprintf(stderr, "File open failed: %s\n", files[i]);
      return 1;
    }

    if (utf8::has_bom(pfile))
      printf("Has BOM ");
    else
      printf("No  BOM ");

    printf("=> %s\n", files[i]);
  }

  return 0;
}
