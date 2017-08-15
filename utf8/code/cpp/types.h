#ifndef _TYPES_H
#define _TYPES_H

#include <cstdint>
#include <vector>

#define Byte uint8_t
#define ByteStream std::vector<Byte>
#define Codepoint uint64_t
#define CodepointStream std::vector<Codepoint>

#define B10X 128
#define B110X 192
#define B1110X 224
#define B11110X 240
#define BYTE_SIZE sizeof(Byte)

#endif
