#ifndef _UTF8_IO_H
#define _UTF8_IO_H

#include <cstdio>
#include "types.h"
#include "decode.h"

namespace utf8
{
/// 函数声明
bytes *read_file(const char *);
codepoints *decode_file(const char *);
bytes *read_str(const char *str);

/**
 * 将文本文件读取成字节数组
 */
bytes *read_file(const char *filename)
{
  FILE *f;
  f = fopen(filename, "rb");
  if (!f)
  {
    fprintf(stderr, "Failed to open file `%s`.\n", filename);
    return nullptr;
  }

  u8 b;
  auto data = new bytes();
  while (fread(&b, utf8::BYTE_SIZE, 1, f))
    data->push_back(b);

  fclose(f);

  return data;
};

/**
 * 将utf8编码的文本文件解码成Unicode codepoint
 */
codepoints *decode_file(const char *filename)
{
  auto data = read_file(filename);
  if (!data)
  {
    return nullptr;
  }
  return decode(*data);
};

/**
 * 将字符串读取成字节数组
 */
bytes *read_str(const char *str)
{
  utf8::u8 *b;
  b = (utf8::u8 *)str;
  bytes *data = new bytes();

  while (*b != '\0')
  {
    data->push_back(*b);
    b++;
  }

  return data;
};

class FileBuffer {
  private:
    FILE *f = nullptr;

  public:
    FileBuffer() {}
    FileBuffer(const char *filename) {
      this->open(filename);
    }

    ~FileBuffer() {}

    bool open(const char *filename) {
      this->f = fopen(filename, "rb");
      if (!this->f)
      {
        fprintf(stderr, "Failed to open file `%s`.\n", filename);
        return false;
      }

      return true;
    }

    bool hasBuffer() {
      return this->f != nullptr;
    }

    u8 next() {
      u8 b;
      if (fread(&b, utf8::BYTE_SIZE, 1, this->f))
        return b;

      return 0;
      // throw FILE_END;
    }

    bytes *to_bytes() {
      // reset to header
      u8 b;
      auto data = new bytes();
      while (fread(&b, utf8::BYTE_SIZE, 1, f))
        data->push_back(b);

      return data;
    }

};

} // namespace utf8

#endif
