#include <cstdio>
#include <cstdlib>
#include <vector>

#define Byte unsigned char
#define ByteStream std::vector<Byte>
#define Codepoint unsigned long int
#define CodepointStream std::vector<Codepoint>

#define B10X 128
#define B110X 192
#define B1110X 224
#define B11110X 240
#define BYTE_SIZE sizeof(Byte)

unsigned int BASES[] = {B10X, B110X, B1110X, B11110X};

/**
 * 检测该字节属于哪一种
 */
int detect(Byte b)
{
  if (b < B10X)
  {
    return 1;
  }

  if (b >= B11110X)
  {
    return 4;
  }
  else if (b >= B1110X)
  {
    return 3;
  }
  else if (b >= B110X)
  {
    return 2;
  }

  return 0;
};

/**
 * 对字节流进行解码
 */
CodepointStream *decode(ByteStream &bs)
{
  CodepointStream *str = new CodepointStream();
  int state = 0, acc = 0;
  Codepoint cp = 0; // code point

  for (auto &b : bs)
  {
    int size = detect(b);

    if (size == 0)
    {
      if (acc + 1 > state)
      {
        printf("Encoding contains errors.");
        break;
      }
      else
      {
        acc++;
        cp += (b - B10X) * (1 << ((state - acc) * 6));
      }
    }
    else
    {
      // 编码中存在错误
      if (state - acc != 0)
      {
        printf("Encoding contains errors.");
        break;
      }
      else
      {
        if (state != 0)
          str->push_back(cp);
        cp = (size == 1) ? (Codepoint)b : (b - BASES[size - 1]) * (1 << ((size - 1) * 6));
        state = size;
        acc = 1;
      }
    }
  }

  if (state != 0)
  {
    str->push_back(cp);
  }

  return str;
}

int main()
{
  FILE *pfile = fopen("utf8.txt", "rb");
  if (!pfile)
  {
    printf("File open failed.");
    return 1;
  }

  ByteStream bs;
  Byte b;
  while (fread(&b, BYTE_SIZE, 1, pfile))
  {
    bs.push_back(b);
  }

  auto cs = decode(bs);
  for (auto &p : *cs)
  {
    printf("%lu\n", p);
  }

  return 0;
}
