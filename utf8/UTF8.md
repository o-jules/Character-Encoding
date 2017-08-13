# UTF8

## UTF8编码的细节：

| bytes count | bits | range               | byte                                  |
|-------------|------|---------------------|---------------------------------------|
|      1      |  7   | U+0000 - U+007F     | 0xxxxxxx                              |
|      2      |  11  | U+0080 - U+07FF     | 110xxxxx 10xxxxxx                     |
|      3      |  16  | U+0800	- U+FFFF     | 1110xxxx 10xxxxxx 10xxxxxx            |
|      4      |  21  | U+10000 - U+10FFFF  | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx   |

## Unicode编码为UTF8的方法

  已知一个字符的Unicode Codepoint是 n，求其UTF8储存的字节。
  二进制转换基本表格：

   - 10xxxxxx = 2^7 + ... = 128 + n (n >= 0 && n <= 63)

   - 110xxxxx = 2^7 + 2^6 + ... = 192 + n (n >= 0 && n <= 31)

   - 1110xxxx = 2^7 + 2^6 + 2^5 + ... = 224 + n (n >= 0 && n <= 15)

   - 11110xxx = 2^7 + 2^6 + 2^5 + 2^4 + ... = 240 + n (n >= 0 && n <= 7)

  具体的算法参照源代码：[convert.ts](./code/convert.ts)

## UTF8解碼
  已知一序列的UTF8二进制码，将其解码为Unicode codepoint。
  具体算法参照源代码：[decode.cpp](./code/decode.cpp)

## 附录/Appendix

  - [Wikipedia - UTF8](https://en.wikipedia.org/wiki/UTF-8)
