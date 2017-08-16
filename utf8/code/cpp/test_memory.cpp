#include <cstdio>
#include "include/types.h"

// C/C++程序的字符串常量
// 在*nix平台，默认是以UTF8储存的

int main(int argc, char **argv)
{
  const char *hello = "Hello, 世界！";

  utf8::u8 *b;
  b = (utf8::u8 *)hello;

  while (*b != '\0')
  {
    printf("%d\n", *b);
    b++;
  }

  return 0;
}
