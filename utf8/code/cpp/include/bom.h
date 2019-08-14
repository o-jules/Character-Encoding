#ifndef _UTF8_BOM_H
#define _UTF8_BOM_H

#include <cstdio>
#include "types.h"

namespace utf8
{
/// 函数声明
bool has_bom(FILE *);

/**
 * @const BOM UTF8-BOM编码的BOM字节(byte order mark)
 */
static const u8 BOM[3] = {239, 187, 191};

/**
 * @param f 文件IO指针
 *
 * \brief 检测一个文件是否文件头带BOM
 *
 * 如果是，返回true，并将文件读取指针置于BOM之后；
 * 如果不是，返回false；文件读取指针置于文件头。
 */
bool has_bom(FILE *f)
{
  u8 b;
  int i = 0;
  while (i <= 2)
    if (!fread(&b, BYTE_SIZE, 1, f) || b != BOM[i++])
      break;

  bool s = i == 3;
  if (!s)
    fseek(f, 0, SEEK_SET);
  return s;
};

} // namespace utf8

#endif
