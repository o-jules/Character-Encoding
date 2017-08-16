const BASES: ReadonlyArray<number> = [
  64, // Math.pow(2, 6),
  4096, // Math.pow(2, 12),
  262144, // Math.pow(2, 18),
]

const LEADINGS: number[] = [
  128, 192,
  224, 240,
]

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
  let order = count - 1
  let byte: number
  while (order >= 0) {
    byte = codepoint >> (order * 6)
    codepoint &= ~(byte << (order * 6))
    list.push(byte += LEADINGS[order === count - 1 ? order : 0])

    order--
  }

  return list
}
