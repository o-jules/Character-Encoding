## V8处理UTF8

超过BMP的字符不能正确处理，如：

```js
let x = '𠀳'
// 131123, 20033

x.length = 2
x[0] // 55360, d840
x[1] // 56371, dc33
x[2] // undefined
```

即，最后以
  1101 1000 0100 0000 1101 1100 0011 0011
储存起来。
而该字符转换成UTF8格式，应以(f0a0 80b3)
  1111 0000 1010 0000 1000 0000 1011 0011
储存。

V8内部以16位整型（`uint_16_t`）存储字符串，见V8源代码/include/v8.h

```cpp
// class V8_EXPORT String 的内部类
  class V8_EXPORT ExternalStringResourceBase {
    virtual const uint16_t* data() const = 0;
  };
```
