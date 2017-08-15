#ifndef _DECODE_H
#define _DECODE_H

#include "types.h"

/**
 * 检测该字节属于哪一种
 */
int detect(Byte b);

/**
 * 对字节流进行解码，这里不对BOM进行处理。
 */
CodepointStream *decode(ByteStream &bs);

#endif
