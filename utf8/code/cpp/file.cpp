#include <stdio.h>
#include "types.h"

int main(int argc, char **argv)
{
  Byte b;

  FILE *pfile;
  pfile = fopen("utf8.txt", "rb");

  if (!pfile)
  {
    printf("File open failed.");
    return 1;
  }

  while (fread(&b, BYTE_SIZE, 1, pfile))
  {
    printf("%d ", b);
  }
  printf("\n");

  return 0;
}

// 结果分析：

// UTF8 without BOM
// 72 101 108 108 111 44 32      228 184 150 231 149 140 239 188 129 10
// H  e   l   l   o   ,  [空格]   世          界          ！

// UTF8 with BOM
// 239 187 191
// 72 101 108 108 111 44 32 228 184 150 231 149 140 239 188 129 10

// BOM:
// 239 187 191
// UTF8 编码的 BOM 是 0xEF,0xBB,0xBF 的字节流。

// 中文字符：

// 世
// utf8: 228 184 150, E4-B8-96
// Unicode code point: 19990，\u4E16

// 界
// utf8: 231 149 140, E7-95-8C
// Unicode code point: 30028, \u754C

// ！
// utf8: 239 188 129, EF-BC-81
// Unicode code point: 65281, \uFF01

// \r\n
// utf8: 13, 10
