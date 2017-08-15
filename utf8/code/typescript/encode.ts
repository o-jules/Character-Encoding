/*
位运算：
	右移补零，
	左移补零， * 2 ^ n
*/

const BASE6 = Math.pow(2, 6)
const BASE12 = Math.pow(2, 12)
const BASE18 = Math.pow(2, 18)

function convert(codepoint: number): number[] {
  var binaryArray: number[] = new Array()
  if (codepoint >= 0 && codepoint <= 0x007f) {
    binaryArray.push(codepoint)
  }
  else if (codepoint <= 0x07ff) {
    let remain = codepoint
    let first = remain >> 6
    remain -= first * BASE6
    let second = remain

    first += 192
    second += 128
    binaryArray.push(first)
    binaryArray.push(second)
  }
  else if (codepoint <= 0xffff) {
    let remain = codepoint
    let first = remain >> 12
    remain -= first * BASE12
    let second = remain >> 6
    remain -= second * BASE6
    let third = remain

    first += 224
    second += 128
    third += 128
    binaryArray.push(first)
    binaryArray.push(second)
    binaryArray.push(third)
  }
  else if (codepoint <= 0x10ffff) {
    let remain = codepoint
    let first = remain >> 18
    remain -= first * BASE18
    let second = remain >> 12
    remain -= second * BASE12
    let third = remain >> 6
    remain -= third * BASE6
    let forth = remain

    first += 240
    second += 128
    third += 128
    forth += 128
    binaryArray.push(first)
    binaryArray.push(second)
    binaryArray.push(third)
    binaryArray.push(forth)
  } else {
    throw RangeError('Code point is out of range')
  }

  return binaryArray
}

function toHex(n: number): string {
  return n.toString(16)
}

function stringToUTF8Hex(s: string): string {
  const len = s.length
  const list: string[] = new Array()
  for (let i = 0; i < len; i++) {
    list.push(
      convert(s.charCodeAt(i)).
        map(i => toHex(i)).
        join('-')
    )
  }
  return list.join(' ')
}

// test:
console.log(stringToUTF8Hex('Hello, 世界！'))
