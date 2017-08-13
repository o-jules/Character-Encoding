#include <cstdlib>
#include <vector>

#define BYTE unsigned char
#define CODE_POINT long int
#define CODE_SERIES std::vector<CODE_POINT>

#define B10X 128
#define B110X 192
#define B1110X 224
#define B11110X 240

int detectByte(BYTE b)
{
  if (b <= 127)
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
}

int main()
{

  CODE_SERIES str = new CODE_SERIES();

  BYTE b;

  FILE *pfile;
  pfile = fopen("utf8.txt", "rb");

  if (!pfile)
  {
    printf("File open failed.");
    return 1;
  }

  size_t ByteSize = sizeof(BYTE);

  int state;
  while (fread(&b, ByteSize, 1, pfile))
  {
    int size = detectByte(b);
    switch (size)
    {
    case 1:
      state = 1;
      break;
    case 2:
      state = 2;
      break;
    case 3:
      state = 3;
      break;
    case 4:
      state = 4;
      break;
    default:
      // general byte:
      break;
    }
  }
  printf("\n");

  return 0;
}
