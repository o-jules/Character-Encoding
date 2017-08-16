#ifndef _ENCODE_H
#define _ENCODE_H

#include "types.h"

int detect_char(Codepoint cp);
ByteStream *encode(Codepoint cp);

#endif
