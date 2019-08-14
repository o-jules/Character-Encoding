#include "test_utils.h"

// C/C++程序的字符串常量
// 在*nix平台，默认是以UTF8储存的

int main(int argc, char **argv) {
  const char *hello = "Hello, 世界！";

  print_string(hello);
  return 0;
}
