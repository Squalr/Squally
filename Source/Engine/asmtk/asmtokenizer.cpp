// [AsmTk]
// Assembler toolkit based on AsmJit.
//
// [License]
// Zlib - See LICENSE.md file in the package.

// [Dependencies]
#include "./asmtokenizer.h"

namespace asmtk {

// ============================================================================
// [asmtk::CharKind / CharMap]
// ============================================================================

enum CharKind {
  // Digit [0-9].
  kChar0x0, kChar0x1, kChar0x2, kChar0x3, kChar0x4, kChar0x5, kChar0x6, kChar0x7, kChar0x8, kChar0x9,
  // Hex [A-F].
  kChar0xA, kChar0xB, kChar0xC, kChar0xD, kChar0xE, kChar0xF,
  // Non-Hex ASCII letter and special chars [A-Z$@_].
  kCharSym,
  // Punctuation
  kCharPcn,
  // Space.
  kCharSpc,
  // Extended ASCII character (0x80 and above), acts as non-recognized.
  kCharExt,
  // Invalid (non-recognized) character.
  kCharInv
};

#define C(id) kChar##id
static const uint8_t CharMap[] = {
  C(Inv), C(Inv), C(Inv), C(Inv), C(Inv), C(Inv), C(Inv), C(Inv), // 000-007 ........ | All invalid.
  C(Inv), C(Spc), C(Spc), C(Spc), C(Spc), C(Spc), C(Inv), C(Inv), // 008-015 .     .. | Spaces 0x9-0xD.
  C(Inv), C(Inv), C(Inv), C(Inv), C(Inv), C(Inv), C(Inv), C(Inv), // 016-023 ........ | All invalid.
  C(Inv), C(Inv), C(Inv), C(Inv), C(Inv), C(Inv), C(Inv), C(Inv), // 024-031 ........ | All invalid.
  C(Spc), C(Pcn), C(Pcn), C(Pcn), C(Pcn), C(Pcn), C(Pcn), C(Pcn), // 032-039  !"#$%&' |
  C(Pcn), C(Pcn), C(Pcn), C(Pcn), C(Pcn), C(Pcn), C(Pcn), C(Pcn), // 040-047 ()*+,-./ |
  C(0x0), C(0x1), C(0x2), C(0x3), C(0x4), C(0x5), C(0x6), C(0x7), // 048-055 01234567 |
  C(0x8), C(0x9), C(Pcn), C(Pcn), C(Pcn), C(Pcn), C(Pcn), C(Pcn), // 056-063 89:;<=>? |
  C(Sym), C(0xA), C(0xB), C(0xC), C(0xD), C(0xE), C(0xF), C(Sym), // 064-071 @ABCDEFG |
  C(Sym), C(Sym), C(Sym), C(Sym), C(Sym), C(Sym), C(Sym), C(Sym), // 072-079 HIJKLMNO |
  C(Sym), C(Sym), C(Sym), C(Sym), C(Sym), C(Sym), C(Sym), C(Sym), // 080-087 PQRSTUVW |
  C(Sym), C(Sym), C(Sym), C(Pcn), C(Pcn), C(Pcn), C(Pcn), C(Sym), // 088-095 XYZ[\]^_ |
  C(Pcn), C(0xA), C(0xB), C(0xC), C(0xD), C(0xE), C(0xF), C(Sym), // 096-103 `abcdefg |
  C(Sym), C(Sym), C(Sym), C(Sym), C(Sym), C(Sym), C(Sym), C(Sym), // 104-111 hijklmno |
  C(Sym), C(Sym), C(Sym), C(Sym), C(Sym), C(Sym), C(Sym), C(Sym), // 112-119 pqrstuvw |
  C(Sym), C(Sym), C(Sym), C(Pcn), C(Pcn), C(Pcn), C(Pcn), C(Inv), // 120-127 xyz{|}~  |
  C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), // 128-135 ........ | Extended.
  C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), // 136-143 ........ |
  C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), // 144-151 ........ |
  C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), // 152-159 ........ |
  C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), // 160-167 ........ |
  C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), // 168-175 ........ |
  C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), // 176-183 ........ |
  C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), // 184-191 ........ |
  C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), // 192-199 ........ |
  C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), // 200-207 ........ |
  C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), // 208-215 ........ |
  C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), // 216-223 ........ |
  C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), // 224-231 ........ |
  C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), // 232-239 ........ |
  C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), // 240-247 ........ |
  C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext), C(Ext)  // 248-255 ........ |
};
#undef C

static inline uint32_t lower(uint32_t c) { return c | 0x20; }

// ============================================================================
// [asmtk::Tokenizer]
// ============================================================================

AsmTokenizer::AsmTokenizer()
  : _input(NULL),
    _end(NULL),
    _cur(NULL),
    _stodctx() {}

uint32_t AsmTokenizer::next(AsmToken* token) {
  const uint8_t* cur = _cur;
  const uint8_t* end = _end;

  // Skip spaces.
  const uint8_t* start = cur;
  if (cur == end)
    return token->setData(AsmToken::kEnd, start, cur);

  uint32_t c = cur[0];
  uint32_t m = CharMap[c];

  if (m == kCharSpc) {
    do {
      cur++;
      if (c == '\n') goto NL;
      if (cur == end) goto End;

      c = cur[0];
      m = CharMap[c];
    } while (m == kCharSpc);
  }
  start = cur;

  // Parse a number.
  if (m < kChar0xA) {
    uint64_t val = m;
    if (++cur == end) {
      _cur = cur;
      token->u64 = val;
      return token->setData(AsmToken::kU64, start, cur);
    }

    // Parse a binary or hexadecimal number.
    c = cur[0];
    if (val == 0) {
      uint32_t cl = lower(c);
      if (cl == 'x' || cl == 'b') {
        uint32_t base = 16;
        uint32_t shift = 4;
        uint32_t limit = 16;

        if (cl == 'b') {
          base = 2;
          shift = 1;
          limit = 64;
        }

        // There must be at least one digit.
        if (++cur == end) goto Invalid;

        c = cur[0];
        m = CharMap[c];
        if (m >= base) goto Invalid;

        do {
          val = (val << shift) | m;
          if (++cur == end) break;

          c = cur[0];
          m = CharMap[c];
        } while (m < base);

        _cur = cur;
        token->u64 = val;
        return token->setData(AsmToken::kU64, start, cur);
      }
    }

    // TODO: Not finished.
    // Parse a decimal number.
    while ((c -= '0') < 10) {
      val = val * 10 + c;
      if (++cur == end) break;
      c = cur[0];
    }

    // Support symbols that start with a number, like '0tox' inside {}.
    if (cur != end) {
      m = CharMap[cur[0]];
      if (m <= kCharSym) {
        do {
          if (++cur == end) break;
          c = cur[0];
          m = CharMap[c];
        } while (m <= kCharSym);

        _cur = cur;
        return token->setData(AsmToken::kNSym, start, cur);
      }
    }

    // Definitely a number.
    _cur = cur;
    token->u64 = val;
    return token->setData(AsmToken::kU64, start, cur);
  }

  // Parse a symbol.
  if (m <= kCharSym) {
    do {
      if (++cur == end) break;
      c = cur[0];
      m = CharMap[c];
    } while (m <= kCharSym);

    _cur = cur;
    return token->setData(AsmToken::kSym, start, cur);
  }

  // Parse punctuation.
  if (m == kCharPcn) {
    uint32_t type = AsmToken::kOther;
    switch (c) {
      case '{': type = AsmToken::kLCurl   ; break;
      case '}': type = AsmToken::kRCurl   ; break;
      case '[': type = AsmToken::kLBracket; break;
      case ']': type = AsmToken::kRBracket; break;
      case '(': type = AsmToken::kLParen  ; break;
      case ')': type = AsmToken::kRParen  ; break;
      case '+': type = AsmToken::kAdd     ; break;
      case '-': type = AsmToken::kSub     ; break;
      case '*': type = AsmToken::kMul     ; break;
      case '/': type = AsmToken::kDiv     ; break;
      case ',': type = AsmToken::kComma   ; break;
      case ':': type = AsmToken::kColon   ; break;
    }
    _cur = ++cur;
    return token->setData(type, start, cur);
  }

Invalid:
  _cur = cur;
  return token->setData(AsmToken::kInvalid, start, cur);

NL:
  _cur = cur;
  return token->setData(AsmToken::kNL, start, cur);

End:
  _cur = cur;
  return token->setData(AsmToken::kEnd, start, cur);
}

} // asmtk namespace
