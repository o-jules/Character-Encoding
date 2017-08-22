#ifndef _UTF8_TYPES_H
#define _UTF8_TYPES_H

#include <cstdint>
#include <vector>

namespace utf8
{

typedef uint8_t u8;
typedef uint32_t u32;
typedef std::vector<u8> bytes;
typedef std::vector<u32> codepoints;

static const size_t BYTE_SIZE = sizeof(u8);
static const size_t CODEPOINT_SIZE = sizeof(u32);

} // namespace utf8

#endif
