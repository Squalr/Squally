// [AsmTk]
// Assembler toolkit based on AsmJit.
//
// [License]
// Zlib - See LICENSE.md file in the package.

// [Dependencies]
#include "./asmparser.h"

namespace asmtk {

using namespace asmjit;

// ============================================================================
// [asmtk::X86Alias]
// ============================================================================

enum X86Alias {
  kX86AliasStart = 0x00010000U,

  kX86AliasMovabs = kX86AliasStart,

  kX86AliasInsb,
  kX86AliasInsd,
  kX86AliasInsw,

  kX86AliasOutsb,
  kX86AliasOutsd,
  kX86AliasOutsw,

  kX86AliasCmpsb,
  kX86AliasCmpsd,
  kX86AliasCmpsq,
  kX86AliasCmpsw,

  kX86AliasMovsb,
  kX86AliasMovsd,
  kX86AliasMovsq,
  kX86AliasMovsw,

  kX86AliasLodsb,
  kX86AliasLodsd,
  kX86AliasLodsq,
  kX86AliasLodsw,

  kX86AliasScasb,
  kX86AliasScasd,
  kX86AliasScasq,
  kX86AliasScasw,

  kX86AliasStosb,
  kX86AliasStosd,
  kX86AliasStosq,
  kX86AliasStosw
};

// ============================================================================
// [asmtk::AsmParser]
// ============================================================================

AsmParser::AsmParser(CodeEmitter* emitter)
  : _emitter(emitter),
    _unknownSymbolHandler(NULL),
    _unknownSymbolHandlerData(NULL) {}
AsmParser::~AsmParser() {}

// ============================================================================
// [asmtk::AsmParser - Parse]
// ============================================================================

static void strToLower(uint8_t* dst, const uint8_t* src, size_t len) {
  for (size_t i = 0; i < len; i++)
    dst[i] = Utils::toLower<uint8_t>(static_cast<uint8_t>(src[i]));
}

#define COMB_CHAR_2(a, b) \
  ((uint32_t(a) << 8) | uint32_t(b))

#define COMB_CHAR_4(a, b, c, d) \
  ((uint32_t(a) << 24) | (uint32_t(b) << 16) | (uint32_t(c) << 8) | uint32_t(d))

static bool x86ParseRegister(Operand_& op, const uint8_t* s, size_t len) {
  enum {
    kMinRegLen = 2,
    kMaxRegLen = 5
  };

  if (len < kMinRegLen || len > kMaxRegLen) return false;
  const uint8_t* sEnd = s + len;

  uint32_t c0 = Utils::toLower<uint32_t>(s[0]);
  uint32_t c1 = Utils::toLower<uint32_t>(s[1]);
  uint32_t c2 = len > 2 ? Utils::toLower<uint32_t>(s[2]) : uint32_t(0);
  uint32_t cn = (c0 << 8) + c1;

  uint32_t rType = X86Reg::kRegNone;
  uint32_t rId = 0;

  static const uint8_t abcdTo0312[] = { 0, 3, 1, 2 };

  // [AL|BL|CL|DL]
  // [AH|BH|CH|DH]
  // [AX|BX|CX|DX]
  // [ES|CS|SS|DS|FS|GS]
  if (len == 2) {
    if (c0 >= 'a' && c0 <= 'd') {
      rId = abcdTo0312[c0 - 'a'];
      if (c1 == 'l') { rType = X86Reg::kRegGpbLo; goto Done; }
      if (c1 == 'h') { rType = X86Reg::kRegGpbHi; goto Done; }
      if (c1 == 'x') { rType = X86Reg::kRegGpw  ; goto Done; }
    }

    if (c1 == 's') {
      rType = X86Reg::kRegSeg;
      if (c0 == 'e') { rId = X86Seg::kIdEs; goto Done; }
      if (c0 == 'c') { rId = X86Seg::kIdCs; goto Done; }
      if (c0 == 's') { rId = X86Seg::kIdSs; goto Done; }
      if (c0 == 'd') { rId = X86Seg::kIdDs; goto Done; }
      if (c0 == 'f') { rId = X86Seg::kIdFs; goto Done; }
      if (c0 == 'g') { rId = X86Seg::kIdGs; goto Done; }
    }

    rType = X86Reg::kRegGpw;
    goto TrySpBpSiDi;
  }

  // [SP|BP|SI|DI]
  // [SPL|BPL|SIL|DIL]
  // [EAX|EBX|ECX|EDX|ESP|EBP|EDI|ESI]
  // [RAX|RBX|RCX|RDX|RSP|RBP|RDI|RSI]
  // [RIP]
  if (len == 3) {
    if (c2 == 'l') {
      rType = X86Reg::kRegGpbLo;
      goto TrySpBpSiDi;
    }

    if (c0 == 'e' || c0 == 'r') {
      cn = (c1 << 8) | c2;

      if (c0 == 'r' && cn == COMB_CHAR_2('i', 'p')) {
        rType = X86Reg::kRegRip;
        goto Done;
      }

      rType = (c0 == 'e') ? X86Reg::kRegGpd : X86Reg::kRegGpq;
      if (cn == COMB_CHAR_2('a', 'x')) { rId = X86Gp::kIdAx; goto Done; }
      if (cn == COMB_CHAR_2('d', 'x')) { rId = X86Gp::kIdDx; goto Done; }
      if (cn == COMB_CHAR_2('b', 'x')) { rId = X86Gp::kIdBx; goto Done; }
      if (cn == COMB_CHAR_2('c', 'x')) { rId = X86Gp::kIdCx; goto Done; }

TrySpBpSiDi:
      if (cn == COMB_CHAR_2('s', 'p')) { rId = X86Gp::kIdSp; goto Done; }
      if (cn == COMB_CHAR_2('b', 'p')) { rId = X86Gp::kIdBp; goto Done; }
      if (cn == COMB_CHAR_2('s', 'i')) { rId = X86Gp::kIdSi; goto Done; }
      if (cn == COMB_CHAR_2('d', 'i')) { rId = X86Gp::kIdDi; goto Done; }
    }
  }

  // [R?|R?B|R?W|R?D]
  if (c0 == 'r') {
    s++;
    rType = X86Reg::kRegGpq;

    // Handle 'b', 'w', and 'd' suffixes.
    c2 = Utils::toLower<uint32_t>(sEnd[-1]);
    if (c2 == 'b')
      rType = X86Reg::kRegGpbLo;
    else if (c2 == 'w')
      rType = X86Reg::kRegGpw;
    else if (c2 == 'd')
      rType = X86Reg::kRegGpd;
    sEnd -= (rType != X86Reg::kRegGpq);
  }
  // [XMM?|YMM?|ZMM?]
  else if (c0 >= 'x' && c0 <= 'z' && c1 == 'm' && c2 == 'm') {
    s += 3;
    rType = X86Reg::kRegXmm + (c0 - 'x');
  }
  // [K?]
  else if (c0 == 'k') {
    s++;
    rType = X86Reg::kRegK;
  }
  // [ST?|FP?]
  else if ((c0 == 's' && c1 == 't') | (c0 == 'f' && c1 == 'p')) {
    s += 2;
    rType = X86Reg::kRegFp;
  }
  // [MM?]
  else if (c0 == 'm' && c1 == 'm') {
    s += 2;
    rType = X86Reg::kRegMm;
  }
  // [BND?]
  else if (c0 == 'b' && c1 == 'n' && c2 == 'd') {
    s += 3;
    rType = X86Reg::kRegBnd;
  }
  // [CR?]
  else if (c0 == 'c' && c1 == 'r') {
    s += 2;
    rType = X86Reg::kRegCr;
  }
  // [DR?]
  else if (c0 == 'd' && c1 == 'r') {
    s += 2;
    rType = X86Reg::kRegDr;
  }
  else {
    return false;
  }

  // Parse the register index.
  rId = static_cast<uint32_t>(s[0]) - '0';
  if (rId >= 10) return false;

  if (++s < sEnd) {
    c0 = static_cast<uint32_t>(*s++) - '0';
    if (c0 >= 10) return false;
    rId = rId * 10 + c0;

    // Maximum register
    if (rId >= 32) return false;
  }

  // Fail if the whole input wasn't parsed.
  if (s != sEnd) return false;

  // Fail if the register index is greater than allowed.
  if (rId >= x86OpData.archRegs.regCount[rType]) return false;

Done:
  op._initReg(x86OpData.archRegs.regInfo[rType].getSignature(), rId);
  return true;
}

static uint32_t x86ParseSize(const uint8_t* s, size_t len) {
  enum {
    kMinSizeLen = 4,
    kMaxSizeLen = 7
  };

  if (len < kMinSizeLen || len > kMaxSizeLen)
    return 0;

  // Start from the end.
  uint32_t d = (Utils::toLower<uint32_t>(s[len - 4]) << 24) +
               (Utils::toLower<uint32_t>(s[len - 3]) << 16) +
               (Utils::toLower<uint32_t>(s[len - 2]) <<  8) +
               (Utils::toLower<uint32_t>(s[len - 1]) <<  0) ;

  if (d == COMB_CHAR_4('w', 'o', 'r', 'd')) {
    // Parsed 'word'.
    if (len == 4) return 2;

    // Sizes of length '5':
    d = (Utils::toLower<uint32_t>(s[0]) << 24);
    if (len == 5) {
      // Check the most common first.
      if (d == COMB_CHAR_4('d', 0, 0, 0)) return 4;
      if (d == COMB_CHAR_4('q', 0, 0, 0)) return 8;
      if (d == COMB_CHAR_4('o', 0, 0, 0)) return 16;

      // `fword` (aka far word, 16:32 m48 pointer) and `tword` (m80).
      if (d == COMB_CHAR_4('f', 0, 0, 0)) return 6;
      if (d == COMB_CHAR_4('t', 0, 0, 0)) return 10;
    }

    // Sizes of length '6':
    d += (Utils::toLower<uint32_t>(s[1]) << 16);
    if (len == 6) {
      if (d == COMB_CHAR_4('m', 'm', 0, 0)) return 8;
      if (d == COMB_CHAR_4('d', 'q', 0, 0)) return 16;
      if (d == COMB_CHAR_4('q', 'q', 0, 0)) return 32;
    }

    // Sizes of length '7':
    d += (Utils::toLower<uint32_t>(s[2]) << 8);
    if (len == 7) {
      if (d == COMB_CHAR_4('x', 'm', 'm', 0)) return 16;
      if (d == COMB_CHAR_4('y', 'm', 'm', 0)) return 32;
      if (d == COMB_CHAR_4('z', 'm', 'm', 0)) return 64;
    }
  }

  // Parsed 'byte'.
  if (d == COMB_CHAR_4('b', 'y', 't', 'e'))
    return len == 4 ? 1 : 0;
  else
    return 0;
}

static Error asmHandleSymbol(AsmParser& parser, Operand_& dst, const uint8_t* name, size_t len) {
  Label L = parser._emitter->getLabelByName(reinterpret_cast<const char*>(name), len);

  if (!L.isValid()) {
    if (parser.hasUnknownSymbolHandler()) {
      Error err = parser._unknownSymbolHandler(&parser,
        static_cast<Operand*>(&dst), reinterpret_cast<const char*>(name), len);

      if (err)
        return err;

      if (!dst.isNone())
        return kErrorOk;
    }

    L = parser._emitter->newNamedLabel(reinterpret_cast<const char*>(name), len);
    if (!L.isValid()) return DebugUtils::errored(kErrorNoHeapMemory);
  }

  dst = L;
  return kErrorOk;
}

static Error x86ParseOperand(AsmParser& parser, Operand_& dst, AsmToken* token) {
  uint32_t type = token->type;
  uint32_t memSize = 0;
  Operand seg;

  // Symbol, could be register, memory operand size, or label.
  if (type == AsmToken::kSym) {
    // Try register.
    if (x86ParseRegister(dst, token->data, token->len)) {
      if (!dst.as<X86Reg>().isSeg())
        return kErrorOk;

      // A segment register followed by a colon (':') describes a segment of a
      // memory operand - in such case we store the segment and jump to MemOp.
      AsmToken tTmp;
      if (parser._tokenizer.next(token) == AsmToken::kColon &&
          parser._tokenizer.next(&tTmp) == AsmToken::kLBracket) {
        seg = dst;
        goto MemOp;
      }
      parser._tokenizer.back(token);
      return kErrorOk;
    }

    // Try memory size specifier.
    memSize = x86ParseSize(token->data, token->len);
    if (memSize) {
      type = parser._tokenizer.next(token);

      // The specifier may be followed by 'ptr', skip it in such case.
      if (type == AsmToken::kSym &&
          token->len == 3 &&
          Utils::toLower<uint32_t>(token->data[0]) == 'p' &&
          Utils::toLower<uint32_t>(token->data[1]) == 't' &&
          Utils::toLower<uint32_t>(token->data[2]) == 'r') {
        type = parser._tokenizer.next(token);
      }

      // Jump to memory operand if we encountered '['.
      if (type == AsmToken::kLBracket)
        goto MemOp;

      // Parse segment prefix otherwise.
      if (type == AsmToken::kSym) {
        // Segment register.
        if (!x86ParseRegister(seg, token->data, token->len) || !seg.as<X86Reg>().isSeg())
          return DebugUtils::errored(kErrorInvalidAddress);

        type = parser._tokenizer.next(token);
        if (type != AsmToken::kColon)
          return DebugUtils::errored(kErrorInvalidAddress);

        type = parser._tokenizer.next(token);
        if (type == AsmToken::kLBracket)
          goto MemOp;
      }

      return DebugUtils::errored(kErrorInvalidAddress);
    }

    // Must be label/symbol.
    return asmHandleSymbol(parser, dst, token->data, token->len);
  }

  // Memory address - parse opening '['.
  if (type == AsmToken::kLBracket) {
MemOp:
    Operand base;
    Operand index;

    uint32_t shift = 0;
    uint32_t flags = 0;
    uint64_t offset = 0;

    // Parse address prefix - 'abs'.
    type = parser._tokenizer.next(token);
    if (type == AsmToken::kSym) {
      if (token->len == 3) {
        uint32_t chars = (Utils::toLower<uint32_t>(token->data[0]) << 24) |
                         (Utils::toLower<uint32_t>(token->data[1]) << 16) |
                         (Utils::toLower<uint32_t>(token->data[2]) <<  8) ;

        if (chars == COMB_CHAR_4('a', 'b', 's', 0)) {
          flags |= Mem::kSignatureMemAbs;
          type = parser._tokenizer.next(token);
        }
        else if (chars == COMB_CHAR_4('r', 'e', 'l', 0)) {
          flags |= Mem::kSignatureMemRel;
          type = parser._tokenizer.next(token);
        }
        else if (chars == COMB_CHAR_4('w', 'r', 't', 0)) {
          flags |= Mem::kSignatureMemWrt;
          type = parser._tokenizer.next(token);
        }
      }
    }

    // Parse "[base] + [index [* scale]] + [offset]" parts.
    uint32_t opType = AsmToken::kAdd;
    for (;;) {
      if (type == AsmToken::kSym) {
        if (opType != AsmToken::kAdd)
          return DebugUtils::errored(kErrorInvalidAddress);

        Operand reg;
        if (!x86ParseRegister(reg, token->data, token->len))
          return DebugUtils::errored(kErrorInvalidAddress);

        type = parser._tokenizer.next(token);
        opType = AsmToken::kInvalid;

        if (type != AsmToken::kMul) {
          // Prefer base, then index.
          if (base.isNone())
            base = reg;
          else if (index.isNone())
            index = reg;
          else
            return DebugUtils::errored(kErrorInvalidAddress);
          continue;
        }
        else {
          // Must be index.
          if (index.isNone())
            index = reg;
          else
            return DebugUtils::errored(kErrorInvalidAddress);

          type = parser._tokenizer.next(token);
          if (type != AsmToken::kU64)
            return DebugUtils::errored(kErrorInvalidAddressScale);

          switch (token->u64) {
            case 1: shift = 0; break;
            case 2: shift = 1; break;
            case 4: shift = 2; break;
            case 8: shift = 3; break;
            default:
              return DebugUtils::errored(kErrorInvalidAddressScale);
          }
        }
      }
      else if (type == AsmToken::kU64) {
        if (opType == AsmToken::kAdd) {
          offset += token->u64;
          opType = AsmToken::kInvalid;
        }
        else if (opType == AsmToken::kSub) {
          offset -= token->u64;
          opType = AsmToken::kInvalid;
        }
        else {
          return DebugUtils::errored(kErrorInvalidAddress);
        }
      }
      else if (type == AsmToken::kAdd) {
        if (opType == AsmToken::kInvalid)
          opType = type;
      }
      else if (type == AsmToken::kSub) {
        if (opType == AsmToken::kInvalid)
          opType = type;
        else
          opType = opType == AsmToken::kSub ? AsmToken::kAdd : AsmToken::kSub;
      }
      else if (type == AsmToken::kRBracket) {
        if (opType != AsmToken::kInvalid)
          return DebugUtils::errored(kErrorInvalidAddress);

        // Reverse base and index if base is a vector register.
        if (X86Reg::isVec(base)) {
          if (index.isReg())
            return DebugUtils::errored(kErrorInvalidAddress);
          std::swap(base, index);
        }

        if (base.isReg()) {
          if (!Utils::isInt32<int64_t>(static_cast<int64_t>(offset)) &&
              !Utils::isUInt32<int64_t>(static_cast<int64_t>(offset)))
            return DebugUtils::errored(kErrorInvalidAddress64Bit);

          int32_t disp32 = static_cast<int32_t>(offset & 0xFFFFFFFFU);
          if (!index.isReg())
            dst = x86::ptr(base.as<X86Gp>(), disp32);
          else
            dst = x86::ptr(base.as<X86Gp>(), index.as<X86Gp>(), shift, disp32);
        }
        else {
          if (!index.isReg())
            dst = x86::ptr(offset);
          else
            dst = x86::ptr(offset, index.as<X86Gp>(), shift);
        }

        dst.as<X86Mem>().setSize(memSize);
        dst._addSignatureData(flags);

        if (seg.isReg())
          dst.as<X86Mem>().setSegment(seg.as<X86Seg>());

        return kErrorOk;
        break;
      }
      else {
        return DebugUtils::errored(kErrorInvalidAddress);
      }

      type = parser._tokenizer.next(token);
    }
  }

  // Immediate.
  if (type == AsmToken::kU64 || type == AsmToken::kSub) {
    bool negative = (type == AsmToken::kSub);
    if (negative) {
      type = parser._tokenizer.next(token);
      if (type != AsmToken::kU64)
        return DebugUtils::errored(kErrorInvalidState);
    }

    dst = imm(negative ? -token->i64 : token->i64);
    return kErrorOk;
  }

  return DebugUtils::errored(kErrorInvalidState);
}

static uint32_t x86ParseOption(const uint8_t* s, size_t len) {
  enum {
    kMinOptionLen = 3,
    kMaxOptionLen = 8
  };

  if (len < kMinOptionLen || len > kMaxOptionLen)
    return 0;

  uint32_t d0 = (static_cast<uint32_t>(s[0]) << 24) +
                (static_cast<uint32_t>(s[1]) << 16) +
                (static_cast<uint32_t>(s[2]) <<  8) ;

  // Options of length '3':
  if (len == 3) {
    if (d0 == COMB_CHAR_4('r', 'e', 'p', 0)) return X86Inst::kOptionRep;
    if (d0 == COMB_CHAR_4('r', 'e', 'x', 0)) return X86Inst::kOptionRex;
    return 0;
  }

  // Options of length '4':
  d0 += static_cast<uint32_t>(s[3]);
  if (len == 4) {
    if (d0 == COMB_CHAR_4('l', 'o', 'c', 'k')) return X86Inst::kOptionLock;
    if (d0 == COMB_CHAR_4('r', 'e', 'p', 'z')) return X86Inst::kOptionRep;
    if (d0 == COMB_CHAR_4('r', 'e', 'p', 'e')) return X86Inst::kOptionRep;
    if (d0 == COMB_CHAR_4('l', 'o', 'n', 'g')) return X86Inst::kOptionLongForm;
    if (d0 == COMB_CHAR_4('v', 'e', 'x', '3')) return X86Inst::kOptionVex3;
    if (d0 == COMB_CHAR_4('e', 'v', 'e', 'x')) return X86Inst::kOptionEvex;
    return 0;
  }

  // Options of length '5':
  if (len == 5) {
    uint32_t d1 = static_cast<uint32_t>(s[4]) << 24;

    if (d0 == COMB_CHAR_4('r', 'e', 'p', 'n') && d1 == COMB_CHAR_4('e', 0, 0, 0)) return X86Inst::kOptionRepnz;
    if (d0 == COMB_CHAR_4('r', 'e', 'p', 'n') && d1 == COMB_CHAR_4('z', 0, 0, 0)) return X86Inst::kOptionRepnz;
    if (d0 == COMB_CHAR_4('s', 'h', 'o', 'r') && d1 == COMB_CHAR_4('t', 0, 0, 0)) return X86Inst::kOptionShortForm;
    if (d0 == COMB_CHAR_4('m', 'o', 'd', 'm') && d1 == COMB_CHAR_4('r', 0, 0, 0)) return X86Inst::kOptionModMR;
    return 0;
  }

  // Options of length '8':
  if (len == 8) {
    uint32_t d1 = (static_cast<uint32_t>(s[4]) << 24) |
                  (static_cast<uint32_t>(s[5]) << 16) |
                  (static_cast<uint32_t>(s[6]) <<  8) |
                  (static_cast<uint32_t>(s[7]) <<  0) ;

    if (d0 == COMB_CHAR_4('x', 'a', 'c', 'q') && d1 == COMB_CHAR_4('u', 'i', 'r', 'e')) return X86Inst::kOptionXAcquire;
    if (d0 == COMB_CHAR_4('x', 'r', 'e', 'l') && d1 == COMB_CHAR_4('e', 'a', 's', 'e')) return X86Inst::kOptionXRelease;
  }

  // Should be unreachable.
  return 0;
}

static uint32_t x86ParseAlias(const uint8_t* s, size_t len) {
  if (len < 3)
    return Inst::kIdNone;

  uint32_t d0 = (static_cast<uint32_t>(s[0]) << 24) +
                (static_cast<uint32_t>(s[1]) << 16) +
                (static_cast<uint32_t>(s[2]) <<  8) ;
  if (len == 3) {
    if (d0 == COMB_CHAR_4('s', 'a', 'l', 0)) return X86Inst::kIdShl;
    return Inst::kIdNone;
  }

  d0 += (static_cast<uint32_t>(s[3]) << 0);
  if (len == 4) {
    if (d0 == COMB_CHAR_4('i', 'n', 's', 'b')) return kX86AliasInsb;
    if (d0 == COMB_CHAR_4('i', 'n', 's', 'd')) return kX86AliasInsd;
    if (d0 == COMB_CHAR_4('i', 'n', 's', 'w')) return kX86AliasInsw;
    return Inst::kIdNone;
  }

  uint32_t d1 = (static_cast<uint32_t>(s[4]) << 24);
  if (len == 5) {
    uint32_t base = 0;

    if (d0 == COMB_CHAR_4('c', 'm', 'p', 's')) {
      base = kX86AliasCmpsb;
    }
    else if (d0 == COMB_CHAR_4('l', 'o', 'd', 's')) {
      base = kX86AliasLodsb;
    }
    else if (d0 == COMB_CHAR_4('m', 'o', 'v', 's')) {
      base = kX86AliasMovsb;
    }
    else if (d0 == COMB_CHAR_4('s', 'c', 'a', 's')) {
      base = kX86AliasScasb;
    }
    else if (d0 == COMB_CHAR_4('s', 't', 'o', 's')) {
      base = kX86AliasStosb;
    }
    else if (d0 == COMB_CHAR_4('o', 'u', 't', 's')) {
      if (d1 == COMB_CHAR_4('b', 0, 0, 0)) return kX86AliasOutsb;
      if (d1 == COMB_CHAR_4('d', 0, 0, 0)) return kX86AliasOutsd;
      if (d1 == COMB_CHAR_4('w', 0, 0, 0)) return kX86AliasOutsw;
      return Inst::kIdNone;
    }
    else {
      return Inst::kIdNone;
    }

    if (d1 == COMB_CHAR_4('b', 0, 0, 0)) return base + 0;
    if (d1 == COMB_CHAR_4('d', 0, 0, 0)) return base + 1;
    if (d1 == COMB_CHAR_4('q', 0, 0, 0)) return base + 2;
    if (d1 == COMB_CHAR_4('w', 0, 0, 0)) return base + 3;

    return Inst::kIdNone;
  }

  d1 += static_cast<uint32_t>(s[5]) << 16;
  if (len == 6) {
    if (d0 == COMB_CHAR_4('m', 'o', 'v', 'a') && d1 == COMB_CHAR_4('b', 's', 0, 0)) return kX86AliasMovabs;
  }

  return Inst::kIdNone;
}

static Error x86ParseInstruction(AsmParser& parser, uint32_t& instId, uint32_t& options, AsmToken* token) {
  for (;;) {
    size_t len = token->len;
    uint8_t lower[32];

    if (len > ASMJIT_ARRAY_SIZE(lower))
      return DebugUtils::errored(kErrorInvalidInstruction);

    strToLower(lower, token->data, len);

    // Try to match instruction alias, as there are some tricky ones.
    instId = x86ParseAlias(lower, len);
    if (instId == Inst::kIdNone) {
      // If that didn't work out, try to match instruction as defined by AsmJit.
      instId = X86Inst::getIdByName(reinterpret_cast<char*>(lower), len);
    }

    if (instId == Inst::kIdNone) {
      // Maybe it's an option / prefix?
      uint32_t option = x86ParseOption(lower, len);
      if (!(option))
        return DebugUtils::errored(kErrorInvalidInstruction);

      // Refuse to parse the same option specified multiple times.
      if (ASMJIT_UNLIKELY(options & option))
        return DebugUtils::errored(kErrorInvalidInstruction);
      options |= option;

      if (parser._tokenizer.next(token) != AsmToken::kSym)
        return DebugUtils::errored(kErrorInvalidInstruction);
    }
    else {
      // Ok, we have an instruction. Now let's parse the next token and decide if
      // it belongs to the instruction or not. This is required to parse things
      // such "jmp short" although we prefer "short jmp" (but the former is valid
      // in other assemblers).
      if (parser._tokenizer.next(token) == AsmToken::kSym) {
        len = token->len;
        if (len <= ASMJIT_ARRAY_SIZE(lower)) {
          strToLower(lower, token->data, len);
          uint32_t option = x86ParseOption(lower, len);
          if (option == X86Inst::kOptionShortForm) {
            options |= option;
            return kErrorOk;
          }
        }
      }

      parser._tokenizer.back(token);
      return kErrorOk;
    }
  }
}

static Error x86FixupInstruction(AsmParser& parser, Inst::Detail& detail, Operand_* opArray, uint32_t& opCount) {
  uint32_t i;

  uint32_t& instId = detail.instId;
  uint32_t& options = detail.options;

  if (instId >= kX86AliasStart) {
    X86Emitter* emitter = static_cast<X86Emitter*>(parser._emitter);
    uint32_t memSize = 0;
    bool isStr = false;

    switch (instId) {
      case kX86AliasMovabs:
        // 'movabs' is basically the longest 'mov'.
        instId = X86Inst::kIdMov;
        options |= X86Inst::kOptionLongForm;
        break;

      case kX86AliasInsb: memSize = 1; instId = X86Inst::kIdIns; isStr = true; break;
      case kX86AliasInsd: memSize = 4; instId = X86Inst::kIdIns; isStr = true; break;
      case kX86AliasInsw: memSize = 2; instId = X86Inst::kIdIns; isStr = true; break;

      case kX86AliasOutsb: memSize = 1; instId = X86Inst::kIdOuts; isStr = true; break;
      case kX86AliasOutsd: memSize = 4; instId = X86Inst::kIdOuts; isStr = true; break;
      case kX86AliasOutsw: memSize = 2; instId = X86Inst::kIdOuts; isStr = true; break;

      case kX86AliasCmpsb: memSize = 1; instId = X86Inst::kIdCmps; isStr = true; break;
      case kX86AliasCmpsd: memSize = 4;
        isStr = opCount == 0 || (opCount == 2 && opArray[0].isMem() && opArray[1].isMem());
        instId = isStr ? X86Inst::kIdCmps : X86Inst::kIdCmpsd;
        break;
      case kX86AliasCmpsq: memSize = 8; instId = X86Inst::kIdCmps; isStr = true; break;
      case kX86AliasCmpsw: memSize = 2; instId = X86Inst::kIdCmps; isStr = true; break;

      case kX86AliasMovsb: memSize = 1; instId = X86Inst::kIdMovs; isStr = true; break;
      case kX86AliasMovsd: memSize = 4;
        isStr = opCount == 0 || (opCount == 2 && opArray[0].isMem() && opArray[1].isMem());
        instId = isStr ? X86Inst::kIdMovs : X86Inst::kIdMovsd;
        break;
      case kX86AliasMovsq: memSize = 8; instId = X86Inst::kIdMovs; isStr = true; break;
      case kX86AliasMovsw: memSize = 2; instId = X86Inst::kIdMovs; isStr = true; break;

      case kX86AliasLodsb: memSize = 1; instId = X86Inst::kIdLods; isStr = true; break;
      case kX86AliasLodsd: memSize = 4; instId = X86Inst::kIdLods; isStr = true; break;
      case kX86AliasLodsq: memSize = 8; instId = X86Inst::kIdLods; isStr = true; break;
      case kX86AliasLodsw: memSize = 2; instId = X86Inst::kIdLods; isStr = true; break;

      case kX86AliasScasb: memSize = 1; instId = X86Inst::kIdScas; isStr = true; break;
      case kX86AliasScasd: memSize = 4; instId = X86Inst::kIdScas; isStr = true; break;
      case kX86AliasScasq: memSize = 8; instId = X86Inst::kIdScas; isStr = true; break;
      case kX86AliasScasw: memSize = 2; instId = X86Inst::kIdScas; isStr = true; break;

      case kX86AliasStosb: memSize = 1; instId = X86Inst::kIdStos; isStr = true; break;
      case kX86AliasStosd: memSize = 4; instId = X86Inst::kIdStos; isStr = true; break;
      case kX86AliasStosq: memSize = 8; instId = X86Inst::kIdStos; isStr = true; break;
      case kX86AliasStosw: memSize = 2; instId = X86Inst::kIdStos; isStr = true; break;
        break;
    }

    if (isStr) {
      if (opCount == 0) {
        uint32_t sign = memSize == 1 ? X86Reg::signatureOfT<X86Reg::kRegGpbLo>() :
                        memSize == 2 ? X86Reg::signatureOfT<X86Reg::kRegGpw>() :
                        memSize == 4 ? X86Reg::signatureOfT<X86Reg::kRegGpd>() :
                                       X86Reg::signatureOfT<X86Reg::kRegGpq>() ;

        // String instructions aliases.
        opCount = 2;
        switch (instId) {
          case X86Inst::kIdCmps: opArray[0] = emitter->ptr_zsi(); opArray[1] = emitter->ptr_zdi(); break;
          case X86Inst::kIdMovs: opArray[0] = emitter->ptr_zdi(); opArray[1] = emitter->ptr_zsi(); break;
          case X86Inst::kIdLods:
          case X86Inst::kIdScas: opArray[0] = Reg::fromSignature(sign, X86Gp::kIdAx); opArray[1] = emitter->ptr_zdi(); break;
          case X86Inst::kIdStos: opArray[0] = emitter->ptr_zdi(); opArray[1] = Reg::fromSignature(sign, X86Gp::kIdAx); break;
        }
      }

      for (i = 0; i < opCount; i++) {
        if (opArray[i].isMem()) {
          X86Mem& mem = opArray[i].as<X86Mem>();

          if (mem.getSize() == 0)
            mem.setSize(memSize);

          if (mem.getBaseId() == X86Gp::kIdDi && mem.getSegmentId() == X86Seg::kIdEs)
            mem.resetSegment();
        }
      }
    }
  }

  for (i = 0; i < opCount; i++) {
    Operand_& op = opArray[i];

    // If the parsed memory segment is the default one, remove it. AsmJit
    // always emits segment-override if the segment is specified, this is
    // good on AsmJit side, but causes problems here as it's not necessary
    // to emit 'ds:' everywhere if the input contains it (and it's common).
    if (op.isMem() && op.as<X86Mem>().hasSegment()) {
      X86Mem& mem = op.as<X86Mem>();

      // Default to `ds` segment for most instructions.
      uint32_t defaultSeg = X86Seg::kIdDs;

      // Default to `ss` segment if the operand has esp|rsp or ebp|rbp base.
      if (mem.hasBaseReg()) {
        if (mem.getBaseId() == X86Gp::kIdSp || mem.getBaseId() == X86Gp::kIdBp)
          defaultSeg = X86Seg::kIdSs;
      }

      if (mem.getSegmentId() == defaultSeg)
        mem.resetSegment();
    }
  }

  return kErrorOk;
}

Error AsmParser::parse(const char* input, size_t len) {
  if (len == Globals::kInvalidIndex) len = ::strlen(input);
  if (len == 0) return kErrorOk;

  uint32_t archType = _emitter->getArchType();
  _tokenizer.setInput(reinterpret_cast<const uint8_t*>(input), len);

  for (;;) {
    AsmToken token;
    uint32_t tType = _tokenizer.next(&token);

    if (tType == AsmToken::kSym) {
      AsmToken tmp;

      tType = _tokenizer.next(&tmp);
      if (tType == AsmToken::kColon) {
        // Parse label.
        Label dst;
        ASMJIT_PROPAGATE(asmHandleSymbol(*this, dst, token.data, token.len));
        ASMJIT_PROPAGATE(_emitter->bind(dst));
        continue;
      }
      else {
        // Parse instruction.
        _tokenizer.back(&tmp);

        Inst::Detail detail;
        ASMJIT_PROPAGATE(x86ParseInstruction(*this, detail.instId, detail.options, &token));

        // Parse operands.
        Operand_ opArray[6];
        uint32_t opCount = 0;

        for (;;) {
          tType = _tokenizer.next(&token);

          // Instruction without operands...
          if ((tType == AsmToken::kNL || tType == AsmToken::kEnd) && opCount == 0)
            break;

          // Parse operand.
          ASMJIT_PROPAGATE(x86ParseOperand(*this, opArray[opCount], &token));

          // Parse {} options introduced by AVX-512.
          tType = _tokenizer.next(&token);
          if (tType == AsmToken::kLCurl) {
            do {
              tType = _tokenizer.next(&token);
              if (tType == AsmToken::kSym || tType == AsmToken::kNSym) {
                uint32_t& options = detail.options;

                // TODO: Only accepts lowercase, must be fixed.
                if (token.len == 2 && token.data[0] == 'k' && (uint8_t)(token.data[1] - '0') < 8) {
                  RegOnly& extraReg = detail.extraReg;
                  if (opCount != 0 || !extraReg.isNone())
                    return DebugUtils::errored(kErrorInvalidState);
                  extraReg.init(X86KReg(token.data[1] - '0'));
                }
                else if (token.is('z')) {
                  if (opCount != 0 || (options & X86Inst::kOptionZMask))
                    return DebugUtils::errored(kErrorInvalidState);
                  options |= X86Inst::kOptionZMask;
                }
                else if (token.is('1', 't', 'o', 'x')) {
                  if (!opArray[opCount].isMem() || (options & X86Inst::kOption1ToX))
                    return DebugUtils::errored(kErrorInvalidState);
                  options |= X86Inst::kOption1ToX;
                }
                else if (token.is('s', 'a', 'e')) {
                  if (opCount != 0 || (options & X86Inst::kOptionSAE))
                    return DebugUtils::errored(kErrorInvalidState);
                  options |= X86Inst::kOptionSAE;
                }
                else if (token.is('r', 'n')) {
                  if (opCount != 0 || (options & X86Inst::kOptionER))
                    return DebugUtils::errored(kErrorInvalidState);
                  options |= X86Inst::kOptionER | X86Inst::kOptionRN_SAE;
                }
                else if (token.is('r', 'd')) {
                  if (opCount != 0 || (options & X86Inst::kOptionER))
                    return DebugUtils::errored(kErrorInvalidState);
                  options |= X86Inst::kOptionER | X86Inst::kOptionRD_SAE;
                }
                else if (token.is('r', 'u')) {
                  if (opCount != 0 || (options & X86Inst::kOptionER))
                    return DebugUtils::errored(kErrorInvalidState);
                  options |= X86Inst::kOptionER | X86Inst::kOptionRU_SAE;
                }
                else if (token.is('r', 'z')) {
                  if (opCount != 0 || (options & X86Inst::kOptionER))
                    return DebugUtils::errored(kErrorInvalidState);
                  options |= X86Inst::kOptionER | X86Inst::kOptionRZ_SAE;
                }
              }
              else {
                return DebugUtils::errored(kErrorInvalidState);
              }

              tType = _tokenizer.next(&token);
              if (tType != AsmToken::kRCurl)
                return DebugUtils::errored(kErrorInvalidState);

              tType = _tokenizer.next(&token);
            } while (tType == AsmToken::kLCurl);
          }

          opCount++;
          if (tType == AsmToken::kComma) {
            if (opCount == ASMJIT_ARRAY_SIZE(opArray))
              return DebugUtils::errored(kErrorInvalidState);
            continue;
          }

          if (tType == AsmToken::kNL || tType == AsmToken::kEnd)
            break;

          return DebugUtils::errored(kErrorInvalidState);
        }

        ASMJIT_PROPAGATE(x86FixupInstruction(*this, detail, opArray, opCount));
        ASMJIT_PROPAGATE(Inst::validate(archType, detail, opArray, opCount));

        _emitter->setOptions(detail.options);
        _emitter->setExtraReg(detail.extraReg);
        ASMJIT_PROPAGATE(_emitter->emitOpArray(detail.instId, opArray, opCount));
      }
    }

    if (tType == AsmToken::kNL)
      continue;

    if (tType == AsmToken::kEnd)
      break;

    return DebugUtils::errored(kErrorInvalidState);
  }

  return kErrorOk;
}

} // asmtk namespace
