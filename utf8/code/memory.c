#include <stdio.h>

// C/C++程序的字符串常量
// 在*nix平台，默认是以UTF8储存的

#define BYTE unsigned char

int main()
{
  char *hello = "Hello, 世界！";

  BYTE *b;
  b = (BYTE *)hello;

  while (*b != '\0')
  {
    printf("%d\n", *b);
    b++;
  }

  // sizeof 的结果是 8
  printf("Size of `hello`: %lu\n", sizeof(hello));
  // 如何知道 hello 的内容占了多少个byte？
}
