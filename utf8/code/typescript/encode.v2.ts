
function convert(codepoint: number): number[] {
  if (codepoint >= 0 && codepoint <= 0x007f) {
    return [codepoint]
  }

  let count: number
  if (codepoint <= 0x07ff) {
    count = 2
  } else if (codepoint <= 0xffff) {
    count = 3
  } else if (codepoint <= 0x10ffff) {
    count = 4
  } else {
    throw RangeError('Code point is out of range.')
  }

  var list = new Array<number>()
  let order = count, pad = 0
  let byte: number
  while (order-- > 0) {
    pad = order * 6
    byte = codepoint >> pad
    codepoint &= ~(byte << pad)

    pad = order == count - 1 ? 7 - order : 7;
    while (pad < 8) {
      byte |= 1 << pad++
    }
    list.push(byte)
  }

  return list
}
