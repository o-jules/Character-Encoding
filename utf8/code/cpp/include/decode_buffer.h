#ifndef _UTF8_DECODE_BUFFER_H
#define _UTF8_DECODE_BUFFER_H

#include <cstdio>
#include "types.h"
#include "vars.h"
#include "helper.h"

namespace utf8
{

class DecodeBuffer
{
private:
  bool error = false;
  u64 cp; // 当前的Unicode codepoint
  int s;  // 之前/当前的状态，state
  int a;  // 当前的积累, accumulation
  int i;  // 临时数据

public:
  DecodeBuffer()
  {
    reset();
  };

  void reset()
  {
    error = false;
    cp = 0;
    s = 0;
    a = 0;
    i = 0;
  }

  bool push(u8 &b)
  {
    i = detect_byte(b);

    if (i == -1) {
      // encoding error
      break;
    }

    if (i == 0)
    {
      if (a >= s)
      {
        printf("Errors: bytes overflow.");
        error = true;
        throw ENCODE_ERROR;
      }
      else
      {
        a++;
        cp |= lpad(b ^ B10X, s - a);
        if (a == s)
          return true;
      }
    }
    else
    {
      if (s != a)
      {
        printf("Errors: bytes not sufficient.");
        error = true;
        throw ENCODE_ERROR;
      }
      else
      {
        s = i;
        a = 1;
        if (i == 1)
        {
          cp = (u64)b;
          return true;
        }

        cp = lpad(b ^ ldrop(i), i - 1);
      }
    }

    return false;
  };

  u64 current()
  {
    return cp;
  };
};

} // end of namespace

#endif
