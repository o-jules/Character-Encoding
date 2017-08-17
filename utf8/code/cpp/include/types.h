#ifndef _UTF8_TYPES_H
#define _UTF8_TYPES_H

#include <cstdint>
#include <vector>

namespace utf8
{

typedef uint8_t u8;
typedef uint64_t u64;
typedef std::vector<u8> bytes;
typedef std::vector<u64> codepoints;

typedef uint32_t u32;

static const size_t BYTE_SIZE = sizeof(u8);

} // end of namespace

#endif
