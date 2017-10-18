#ifndef _UTF8_VALIDATE_H
#define _UTF8_VALIDATE_H

#include "types.h"
#include "decode.h"

namespace utf8
{

bool is_valid_string(const char *);
bool is_valid_stream(bytes &);

/**
 * \brief 检测字符串是否为合法的UTF8编码
 */
bool is_valid_string(const char *str)
{
  auto l = read_str(str);
  bool s = is_valid_stream(*l);
  delete l;

  return s;
};

/**
 * \brief 检测字节流是否为合法的UTF8编码
 */
bool is_valid_stream(bytes &bs)
{
  int state = 0, acc = 0;
  int size = 0;

  for (auto const &b : bs)
  {
    size = detect_byte(b);

    if (size == -1) {
      return false;
    }

    if (size == 0)
    {
      // 编码中存在错误
      if (acc >= state)
        return false;

      acc++;
    }
    else
    {
      // 编码中存在错误
      if (acc != state)
        return false;

      state = size;
      acc = 1;
    }
  }

  return true;
};

} // namespace utf8

#endif
