# UTF8

UTF8 是一种兼容 ASCII 编码的变长编码。

## UTF8编码的细节：

| Bytes count | Bits | Range               | Bytes                                 |
|-------------|------|---------------------|---------------------------------------|
|      1      |  7   | U+0000 - U+007F     | 0xxxxxxx                              |
|      2      |  11  | U+0080 - U+07FF     | 110xxxxx 10xxxxxx                     |
|      3      |  16  | U+0800	- U+FFFF     | 1110xxxx 10xxxxxx 10xxxxxx            |
|      4      |  21  | U+10000 - U+10FFFF  | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx   |

### 样例

| Character	| Octal   |	Binary code point             | Binary UTF-8                               |
|-----------|---------|-------------------------------|--------------------------------------------|
| $ U+0024  | 044     | 010 0100                      | 0-0100100                                  |
| ¢ U+00A2  | 0242    | 000 10-10 0010                | 110-00010 10-100010                        |
| € U+20AC  | 020254  | 0010 -0000 10-10 1100         | 1110-0010 10-000010 10-101100              |
| 𐍈 U+10348 | 0201510 | 0 00-01 0000 -0011 01-00 1000 | 11110-000 10-010000 10-001101 10-001000    |

## 编码

  即将 Unicode codepoint 转换为符合 UTF8 编码的字节。

  已知一个字符的Unicode Codepoint是 n，求其UTF8储存的字节。

  ```rust
  fn encode(codepoint: u32) -> Vec<u8>
  ```

  二进制转换基本表格：

|  字节类型   |                         编码                               |
|-----------|-----------------------------------------------------------|
| 10xxxxxx  | 2^7 + ... = 128 + n (n >= 0 && n <= 63)                   |
| 110xxxxx  | 2^7 + 2^6 + ... = 192 + n (n >= 0 && n <= 31)             |
| 1110xxxx  | 2^7 + 2^6 + 2^5 + ... = 224 + n (n >= 0 && n <= 15)       |
| 11110xxx  | 2^7 + 2^6 + 2^5 + 2^4 + ... = 240 + n (n >= 0 && n <= 7)  |

  具体的算法参照源代码：[encode.ts](./code/typescript/encode.ts) 或 [encode.cpp](./code/cpp/include/encode.h)。

## 解码

  已知一序列的UTF8二进制码，将其解码为Unicode codepoint。

  ```rust
  fn decode(stream: Vec<u8>) -> Vec<u32>
  ```

  具体算法参照源代码：[decode.cpp](./code/cpp/include/decode.h)


### 字符索引的时间复杂度

对于长度为 N 的UTF8字符串，查找到第n个字符，其时间复杂度为 O(n)。

由于UTF8是变长编码，所以索引字符不是数组索引的时间复杂度 O(1)，而是和解码的时间复杂度相等同。

（Mozilla的Rust就因为这个问题，在 charAt类 方法上龃龉不前，时有反覆。）

## 附录/Appendix

  - [Wikipedia - UTF8](https://en.wikipedia.org/wiki/UTF-8)
