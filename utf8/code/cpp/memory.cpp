#include <stdio.h>
#include "types.h"

// C/C++程序的字符串常量
// 在*nix平台，默认是以UTF8储存的

int main(int argc, char **argv)
{
  const char *hello = "Hello, 世界！";

  Byte *b;
  b = (Byte *)hello;

  while (*b != '\0')
  {
    printf("%d\n", *b);
    b++;
  }

  // sizeof 的结果是 8
  printf("Size of `hello`: %lu\n", sizeof(hello));
  // 如何知道 hello 的内容占了多少个byte？

  return 0;
}
