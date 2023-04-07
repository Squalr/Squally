// [AsmTk]
// Assembler toolkit based on AsmJit.
//
// [License]
// Zlib - See LICENSE.md file in the package.

#define ASMTK_EXPORTS

#include "Engine/External/asmjit/x86.h"

#include "./asmparser.h"
#include "./parserutils.h"

namespace asmtk {

using namespace asmjit;

// ============================================================================
// [asmtk::X86Directive]
// ============================================================================

enum X86Directive : uint32_t {
  kX86DirectiveNone  = 0,
  kX86DirectiveAlign,
  kX86DirectiveDB,
  kX86DirectiveDW,
  kX86DirectiveDD,
  kX86DirectiveDQ
};

// ============================================================================
// [asmtk::X86Alias]
// ============================================================================

enum X86Alias : uint32_t {
  kX86AliasStart = 0x00010000u,

  kX86AliasInsb = kX86AliasStart,
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

AsmParser::AsmParser(BaseEmitter* emitter) noexcept
  : _emitter(emitter),
    _currentCommandOffset(0),
    _currentGlobalLabelId(Globals::kInvalidId),
    _unknownSymbolHandler(nullptr),
    _unknownSymbolHandlerData(nullptr) {}
AsmParser::~AsmParser() noexcept {}

// ============================================================================
// [asmtk::AsmParser - Input]
// ============================================================================

AsmTokenType AsmParser::nextToken(AsmToken* token, ParseFlags flags) noexcept {
  return _tokenizer.next(token, flags);
}

void AsmParser::putTokenBack(AsmToken* token) noexcept {
  _tokenizer.putBack(token);
}

// ============================================================================
// [asmtk::AsmParser - Parse]
// ============================================================================

static void strToLower(uint8_t* dst, const uint8_t* src, size_t size) noexcept{
  for (size_t i = 0; i < size; i++)
    dst[i] = Support::asciiToLower<uint8_t>(uint8_t(src[i]));
}

#define COMB_CHAR_2(a, b) \
  ((uint32_t(a) << 8) | uint32_t(b))

#define COMB_CHAR_4(a, b, c, d) \
  ((uint32_t(a) << 24) | (uint32_t(b) << 16) | (uint32_t(c) << 8) | uint32_t(d))

static uint32_t x86RegisterCount(Arch arch, RegType regType) noexcept {
  if (arch == Arch::kX86)
    return 8;

  if (regType == RegType::kX86_St || regType == RegType::kX86_Mm || regType == RegType::kX86_KReg || regType == RegType::kX86_Tmm)
    return 8;

  if (regType == RegType::kX86_Xmm || regType == RegType::kX86_Ymm || regType == RegType::kX86_Zmm)
    return 32;

  return 16;
}

static bool x86ParseRegister(AsmParser& parser, Operand_& op, const uint8_t* s, size_t size) noexcept {
  constexpr uint32_t kMinSize = 2;
  constexpr uint32_t kMaxSize = 5;

  if (size < kMinSize || size > kMaxSize)
    return false;

  const uint8_t* sEnd = s + size;

  uint32_t c0 = Support::asciiToLower<uint32_t>(s[0]);
  uint32_t c1 = Support::asciiToLower<uint32_t>(s[1]);
  uint32_t c2 = size > 2 ? Support::asciiToLower<uint32_t>(s[2]) : uint32_t(0);
  uint32_t cn = (c0 << 8) + c1;

  RegType rType = RegType::kNone;
  uint32_t rId = 0;

  static const uint8_t gpLetterToRegIndex[] = {
    uint8_t(x86::Gp::kIdAx), // a
    uint8_t(x86::Gp::kIdBx), // b
    uint8_t(x86::Gp::kIdCx), // c
    uint8_t(x86::Gp::kIdDx)  // d
  };

  static const uint8_t srLetterToRegIndex[] = {
    uint8_t(x86::Reg::kIdBad), // a
    uint8_t(x86::Reg::kIdBad), // b
    uint8_t(x86::SReg::kIdCs), // c
    uint8_t(x86::SReg::kIdDs), // d
    uint8_t(x86::SReg::kIdEs), // e
    uint8_t(x86::SReg::kIdFs), // f
    uint8_t(x86::SReg::kIdGs), // g
    uint8_t(x86::Reg::kIdBad), // h
    uint8_t(x86::Reg::kIdBad), // i
    uint8_t(x86::Reg::kIdBad), // j
    uint8_t(x86::Reg::kIdBad), // k
    uint8_t(x86::Reg::kIdBad), // l
    uint8_t(x86::Reg::kIdBad), // m
    uint8_t(x86::Reg::kIdBad), // n
    uint8_t(x86::Reg::kIdBad), // o
    uint8_t(x86::Reg::kIdBad), // p
    uint8_t(x86::Reg::kIdBad), // q
    uint8_t(x86::Reg::kIdBad), // r
    uint8_t(x86::SReg::kIdSs)  // s
  };

  // [AL|BL|CL|DL]
  // [AH|BH|CH|DH]
  // [AX|BX|CX|DX]
  // [ES|CS|SS|DS|FS|GS]
  if (size == 2 && Support::isBetween<uint32_t>(c0, 'a', 's')) {
    if (c0 <= 'd') {
      rId = gpLetterToRegIndex[c0 - 'a'];

      rType = RegType::kX86_GpbLo;
      if (c1 == 'l') goto Done;

      rType = RegType::kX86_GpbHi;
      if (c1 == 'h') goto Done;

      rType = RegType::kX86_Gpw;
      if (c1 == 'x') goto Done;
    }

    if (c1 == 's') {
      rId = srLetterToRegIndex[c0 - 'a'];
      rType = RegType::kX86_SReg;

      if (rId != x86::Reg::kIdBad)
        goto Done;
    }

    rType = RegType::kX86_Gpw;
    goto TrySpBpSiDi;
  }

  // [SP|BP|SI|DI]
  // [SPL|BPL|SIL|DIL]
  // [EAX|EBX|ECX|EDX|ESP|EBP|EDI|ESI]
  // [RAX|RBX|RCX|RDX|RSP|RBP|RDI|RSI]
  // [RIP]
  if (size == 3) {
    if (c2 == 'l') {
      rType = RegType::kX86_GpbLo;
      goto TrySpBpSiDi;
    }

    if (c0 == 'e' || c0 == 'r') {
      cn = (c1 << 8) | c2;
      rType = (c0 == 'e') ? RegType::kX86_Gpd : RegType::kX86_Gpq;

      if (c0 == 'r' && cn == COMB_CHAR_2('i', 'p')) {
        rType = RegType::kX86_Rip;
        goto Done;
      }

      if (cn == COMB_CHAR_2('a', 'x')) { rId = x86::Gp::kIdAx; goto Done; }
      if (cn == COMB_CHAR_2('d', 'x')) { rId = x86::Gp::kIdDx; goto Done; }
      if (cn == COMB_CHAR_2('b', 'x')) { rId = x86::Gp::kIdBx; goto Done; }
      if (cn == COMB_CHAR_2('c', 'x')) { rId = x86::Gp::kIdCx; goto Done; }

TrySpBpSiDi:
      if (cn == COMB_CHAR_2('s', 'p')) { rId = x86::Gp::kIdSp; goto Done; }
      if (cn == COMB_CHAR_2('b', 'p')) { rId = x86::Gp::kIdBp; goto Done; }
      if (cn == COMB_CHAR_2('s', 'i')) { rId = x86::Gp::kIdSi; goto Done; }
      if (cn == COMB_CHAR_2('d', 'i')) { rId = x86::Gp::kIdDi; goto Done; }
    }
  }

  // [R?|R?B|R?W|R?D]
  if (c0 == 'r') {
    s++;
    rType = RegType::kX86_Gpq;

    // Handle 'b', 'w', and 'd' suffixes.
    c2 = Support::asciiToLower<uint32_t>(sEnd[-1]);
    if (c2 == 'b')
      rType = RegType::kX86_GpbLo;
    else if (c2 == 'w')
      rType = RegType::kX86_Gpw;
    else if (c2 == 'd')
      rType = RegType::kX86_Gpd;
    sEnd -= (rType != RegType::kX86_Gpq);
  }
  // [XMM?|YMM?|ZMM?]
  else if (c0 >= 'x' && c0 <= 'z' && c1 == 'm' && c2 == 'm') {
    s += 3;
    rType = RegType(uint32_t(RegType::kX86_Xmm) + uint32_t(c0 - 'x'));
  }
  // [K?]
  else if (c0 == 'k') {
    s++;
    rType = RegType::kX86_KReg;
  }
  // [ST?|FP?]
  else if ((c0 == 's' && c1 == 't') | (c0 == 'f' && c1 == 'p')) {
    s += 2;
    rType = RegType::kX86_St;
  }
  // [MM?]
  else if (c0 == 'm' && c1 == 'm') {
    s += 2;
    rType = RegType::kX86_Mm;
  }
  // [BND?]
  else if (c0 == 'b' && c1 == 'n' && c2 == 'd') {
    s += 3;
    rType = RegType::kX86_Bnd;
  }
  // [TMM?]
  else if (c0 == 't' && c1 == 'm' && c2 == 'm') {
    s += 3;
    rType = RegType::kX86_Tmm;
  }
  // [CR?]
  else if (c0 == 'c' && c1 == 'r') {
    s += 2;
    rType = RegType::kX86_CReg;
  }
  // [DR?]
  else if (c0 == 'd' && c1 == 'r') {
    s += 2;
    rType = RegType::kX86_DReg;
  }
  else {
    return false;
  }

  // Parse the register index.
  rId = uint32_t(s[0]) - '0';
  if (rId >= 10)
    return false;

  if (++s < sEnd) {
    c0 = uint32_t(*s++) - '0';
    if (c0 >= 10)
      return false;
    rId = rId * 10 + c0;

    // Maximum register
    if (rId >= x86RegisterCount(parser.emitter()->arch(), rType))
      return false;
  }

  // Fail if the whole input wasn't parsed.
  if (s != sEnd)
    return false;

  // Fail if the register index is greater than allowed.
  if (rId >= 32)
    return false;

Done:
  op._initReg(ArchTraits::byArch(Arch::kX64).regTypeToSignature(rType), rId);
  return true;
}

static uint32_t x86ParseSize(const uint8_t* s, size_t size) noexcept {
  constexpr uint32_t kMinSize = 4;
  constexpr uint32_t kMaxSize = 7;

  if (size < kMinSize || size > kMaxSize)
    return 0;

  // Start from the end.
  ParserUtils::WordParser suffix;
  suffix.addLowercasedChar(s + size - 4, 0);
  suffix.addLowercasedChar(s + size - 4, 1);
  suffix.addLowercasedChar(s + size - 4, 2);
  suffix.addLowercasedChar(s + size - 4, 3);

  if (suffix.test('w', 'o', 'r', 'd')) {
    // Parsed 'word'.
    if (size == 4)
      return 2;

    // Sizes of length '5':
    ParserUtils::WordParser wordSize;
    wordSize.addLowercasedChar(s, 0);

    if (size == 5) {
      // Check the most common first.
      if (wordSize.test('d')) return 4;
      if (wordSize.test('q')) return 8;
      if (wordSize.test('o')) return 16;
      if (wordSize.test('x')) return 16;
      if (wordSize.test('y')) return 32;
      if (wordSize.test('z')) return 64;

      // `fword` (aka far word, 16:32 m48 pointer) and `tword` (m80).
      if (wordSize.test('f')) return 6;
      if (wordSize.test('t')) return 10;
    }

    // Sizes of length '6':
    wordSize.addLowercasedChar(s, 1);
    if (size == 6) {
      if (wordSize.test('m', 'm')) return 8;
      if (wordSize.test('d', 'q')) return 16;
      if (wordSize.test('q', 'q')) return 32;
    }

    // Sizes of length '7':
    wordSize.addLowercasedChar(s, 2);
    if (size == 7) {
      if (wordSize.test('x', 'm', 'm')) return 16;
      if (wordSize.test('y', 'm', 'm')) return 32;
      if (wordSize.test('z', 'm', 'm')) return 64;
    }
  }

  // Parsed 'byte'.
  if (suffix.test('b', 'y', 't', 'e')) {
    if (size == 4)
      return 1;

    // Sizes of length '5':
    ParserUtils::WordParser wordSize;
    wordSize.addLowercasedChar(s, 0);

    if (size == 5) {
      if (wordSize.test('t')) return 10;
    }
  }

  return 0;
}

static Error asmHandleSymbol(AsmParser& parser, Operand_& dst, const uint8_t* name, size_t nameSize) noexcept {
  // Resolve global/local label.
  BaseEmitter* emitter = parser._emitter;

  const uint8_t* localName = nullptr;
  size_t localNameSize = 0;
  size_t parentNameSize = nameSize;

  // Don't do anything if the name starts with "..".
  if (!(nameSize >= 2 && name[0] == '.' && name[1] == '.')) {
    localName = static_cast<const uint8_t*>(memchr(name, '.', nameSize));
    if (localName) {
      parentNameSize = (size_t)(localName - name);
      localName++;
      localNameSize = (size_t)((name + nameSize) - localName);
    }
  }

  Label parent;
  Label label;

  if (localName) {
    if (name[0] == '.')
      parent.setId(parser._currentGlobalLabelId);
    else
      parent = emitter->labelByName(reinterpret_cast<const char*>(name), parentNameSize);

    if (parent.isValid())
      label = emitter->labelByName(reinterpret_cast<const char*>(localName), localNameSize, parent.id());
  }
  else {
    label = emitter->labelByName(reinterpret_cast<const char*>(name), nameSize, parent.id());
  }

  if (!label.isValid()) {
    if (parser._unknownSymbolHandler) {
      dst.reset();
      ASMJIT_PROPAGATE(parser._unknownSymbolHandler(&parser, static_cast<Operand*>(&dst), reinterpret_cast<const char*>(name), nameSize));
      if (!dst.isNone())
        return kErrorOk;
    }

    if (localName) {
      if (!parent.isValid()) {
        if (!parentNameSize)
          return DebugUtils::errored(kErrorInvalidParentLabel);

        parent = emitter->newNamedLabel(reinterpret_cast<const char*>(name), parentNameSize, LabelType::kGlobal);
        if (!parent.isValid())
          return DebugUtils::errored(kErrorOutOfMemory);
      }
      label = emitter->newNamedLabel(reinterpret_cast<const char*>(localName), localNameSize, LabelType::kLocal, parent.id());
      if (!label.isValid())
        return DebugUtils::errored(kErrorOutOfMemory);
    }
    else {
      label = emitter->newNamedLabel(reinterpret_cast<const char*>(name), nameSize, LabelType::kGlobal);
      if (!label.isValid())
        return DebugUtils::errored(kErrorOutOfMemory);
    }
  }

  dst = label;
  return kErrorOk;
}

static Error x86ParseOperand(AsmParser& parser, Operand_& dst, AsmToken* token) noexcept {
  AsmTokenType type = token->type();
  uint32_t memSize = 0;
  Operand seg;

  // Symbol, could be register, memory operand size, or label.
  if (type == AsmTokenType::kSym) {
    // Try register.
    if (x86ParseRegister(parser, dst, token->data(), token->size())) {
      if (!dst.as<x86::Reg>().isSReg())
        return kErrorOk;

      // A segment register followed by a colon (':') describes a segment of a
      // memory operand - in such case we store the segment and jump to MemOp.
      AsmToken tTmp;
      if (parser.nextToken(token) == AsmTokenType::kColon &&
          parser.nextToken(&tTmp) == AsmTokenType::kLBracket) {
        seg = dst;
        goto MemOp;
      }
      parser.putTokenBack(token);
      return kErrorOk;
    }

    // Try memory size specifier.
    memSize = x86ParseSize(token->data(), token->size());
    if (memSize) {
      type = parser.nextToken(token);

      // The specifier may be followed by 'ptr', skip it in such case.
      if (type == AsmTokenType::kSym &&
          token->size() == 3 &&
          Support::asciiToLower<uint32_t>(token->dataAt(0)) == 'p' &&
          Support::asciiToLower<uint32_t>(token->dataAt(1)) == 't' &&
          Support::asciiToLower<uint32_t>(token->dataAt(2)) == 'r') {
        type = parser.nextToken(token);
      }

      // Jump to memory operand if we encountered '['.
      if (type == AsmTokenType::kLBracket)
        goto MemOp;

      // Parse segment prefix otherwise.
      if (type == AsmTokenType::kSym) {
        // Segment register.
        if (!x86ParseRegister(parser, seg, token->data(), token->size()) || !seg.as<x86::Reg>().isSReg())
          return DebugUtils::errored(kErrorInvalidAddress);

        type = parser.nextToken(token);
        if (type != AsmTokenType::kColon)
          return DebugUtils::errored(kErrorInvalidAddress);

        type = parser.nextToken(token);
        if (type == AsmTokenType::kLBracket)
          goto MemOp;
      }

      return DebugUtils::errored(kErrorInvalidAddress);
    }

    // Must be label/symbol.
    return asmHandleSymbol(parser, dst, token->data(), token->size());
  }

  // Memory address - parse opening '['.
  if (type == AsmTokenType::kLBracket) {
MemOp:
    Operand base;
    Operand index;

    uint32_t shift = 0;
    uint64_t offset = 0;
    OperandSignature signature{0};

    // Parse address prefix - 'abs'.
    type = parser.nextToken(token);
    if (type == AsmTokenType::kSym) {
      if (token->size() == 3) {
        ParserUtils::WordParser addrMode;
        addrMode.addLowercasedChar(token->data(), 0);
        addrMode.addLowercasedChar(token->data(), 1);
        addrMode.addLowercasedChar(token->data(), 2);

        if (addrMode.test('a', 'b', 's')) {
          signature |= OperandSignature::fromValue<x86::Mem::kSignatureMemAddrTypeMask>(x86::Mem::AddrType::kAbs);
          type = parser.nextToken(token);
        }
        else if (addrMode.test('r', 'e', 'l')) {
          signature |= OperandSignature::fromValue<x86::Mem::kSignatureMemAddrTypeMask>(x86::Mem::AddrType::kRel);
          type = parser.nextToken(token);
        }
      }
    }

    // Parse "[base] + [index [* scale]] + [offset]" or "[base + [offset]], [index [* scale]]".
    bool commaSeparated = false;
    AsmTokenType opType = AsmTokenType::kAdd;

    for (;;) {
      if (type == AsmTokenType::kSym) {
        if (opType != AsmTokenType::kAdd)
          return DebugUtils::errored(kErrorInvalidAddress);

        Operand op;
        if (!x86ParseRegister(parser, op, token->data(), token->size())) {
          // No label after 'base' is allowed.
          if (!base.isNone())
            return DebugUtils::errored(kErrorInvalidAddress);

          ASMJIT_PROPAGATE(asmHandleSymbol(parser, op, token->data(), token->size()));
        }

        type = parser.nextToken(token);
        opType = AsmTokenType::kInvalid;

        if (type != AsmTokenType::kMul) {
          // Prefer base, then index.
          if (base.isNone() && !commaSeparated)
            base = op;
          else if (index.isNone())
            index = op;
          else
            return DebugUtils::errored(kErrorInvalidAddress);
          continue;
        }
        else {
          // Must be index.
          if (base.isLabel() || !index.isNone())
            return DebugUtils::errored(kErrorInvalidAddress);

          index = op;
          type = parser.nextToken(token);
          if (type != AsmTokenType::kU64)
            return DebugUtils::errored(kErrorInvalidAddressScale);

          switch (token->u64Value()) {
            case 1: shift = 0; break;
            case 2: shift = 1; break;
            case 4: shift = 2; break;
            case 8: shift = 3; break;
            default:
              return DebugUtils::errored(kErrorInvalidAddressScale);
          }
        }
      }
      else if (type == AsmTokenType::kU64) {
        if (opType == AsmTokenType::kAdd) {
          offset += token->u64Value();
          opType = AsmTokenType::kInvalid;
        }
        else if (opType == AsmTokenType::kSub) {
          offset -= token->u64Value();
          opType = AsmTokenType::kInvalid;
        }
        else {
          return DebugUtils::errored(kErrorInvalidAddress);
        }
      }
      else if (type == AsmTokenType::kAdd) {
        if (opType == AsmTokenType::kInvalid)
          opType = type;
      }
      else if (type == AsmTokenType::kSub) {
        if (opType == AsmTokenType::kInvalid)
          opType = type;
        else
          opType = opType == AsmTokenType::kSub ? AsmTokenType::kAdd : AsmTokenType::kSub;
      }
      else if (type == AsmTokenType::kRBracket) {
        if (opType != AsmTokenType::kInvalid)
          return DebugUtils::errored(kErrorInvalidAddress);

        // Reverse base and index if base is a vector register.
        if (x86::Reg::isVec(base)) {
          if (index.isReg())
            return DebugUtils::errored(kErrorInvalidAddress);
          std::swap(base, index);
        }

        if (!base.isNone()) {
          // Verify the address can be assigned to the operand.
          if (!Support::isInt32(int64_t(offset))) {
            if (!Support::isUInt32(int64_t(offset)))
              return DebugUtils::errored(kErrorInvalidAddress64Bit);

            if (base.as<BaseReg>().isReg(RegType::kX86_Gpq))
              return DebugUtils::errored(kErrorInvalidAddress64BitZeroExtension);
          }

          int32_t disp32 = int32_t(offset & 0xFFFFFFFFu);
          if (base.isLabel())
            dst = x86::ptr(base.as<Label>(), disp32);
          else if (!index.isReg())
            dst = x86::ptr(base.as<x86::Gp>(), disp32);
          else
            dst = x86::ptr(base.as<x86::Gp>(), index.as<x86::Gp>(), shift, disp32);
        }
        else {
          if (!index.isReg())
            dst = x86::ptr(offset);
          else
            dst = x86::ptr(offset, index.as<x86::Gp>(), shift);
        }

        dst.as<x86::Mem>().setSize(memSize);
        dst._signature |= signature;

        if (seg.isReg())
          dst.as<x86::Mem>().setSegment(seg.as<x86::SReg>());

        return kErrorOk;
      }
      else if (type == AsmTokenType::kComma) {
        if (commaSeparated)
          return DebugUtils::errored(kErrorInvalidAddress);

        opType = AsmTokenType::kAdd;
        commaSeparated = true;
      }
      else {
        return DebugUtils::errored(kErrorInvalidAddress);
      }

      type = parser.nextToken(token);
    }
  }

  // Immediate.
  if (type == AsmTokenType::kU64 || type == AsmTokenType::kSub) {
    bool negative = (type == AsmTokenType::kSub);
    if (negative) {
      type = parser.nextToken(token);
      if (type != AsmTokenType::kU64)
        return DebugUtils::errored(kErrorInvalidState);
    }

    dst = imm(negative ? -token->i64Value() : token->i64Value());
    return kErrorOk;
  }

  return DebugUtils::errored(kErrorInvalidState);
}

static InstOptions x86ParseInstOption(const uint8_t* s, size_t size) noexcept {
  constexpr uint32_t kMinSize = 3;
  constexpr uint32_t kMaxSize = 8;

  if (size < kMinSize || size > kMaxSize)
    return InstOptions::kNone;

  ParserUtils::WordParser word;

  // Options of length '3':
  word.addLowercasedChar(s, 0);
  word.addLowercasedChar(s, 1);
  word.addLowercasedChar(s, 2);

  if (size == 3) {
    if (word.test('b', 'n', 'd')) return InstOptions::kX86_Repne;
    if (word.test('r', 'e', 'p')) return InstOptions::kX86_Rep;
    if (word.test('r', 'e', 'x')) return InstOptions::kX86_Rex;
    if (word.test('v', 'e', 'x')) return InstOptions::kX86_Vex;

    return InstOptions::kNone;
  }

  // Options of length '4':
  word.addLowercasedChar(s, 3);

  if (size == 4) {
    if (word.test('e', 'v', 'e', 'x')) return InstOptions::kX86_Evex;
    if (word.test('l', 'o', 'c', 'k')) return InstOptions::kX86_Lock;
    if (word.test('l', 'o', 'n', 'g')) return InstOptions::kLongForm;
    if (word.test('r', 'e', 'p', 'e')) return InstOptions::kX86_Rep;
    if (word.test('r', 'e', 'p', 'z')) return InstOptions::kX86_Rep;
    if (word.test('v', 'e', 'x', '3')) return InstOptions::kX86_Vex3;

    return InstOptions::kNone;
  }

  // Options of length '5':
  word.addLowercasedChar(s, 4);

  if (size == 5) {
    if (word.test('m', 'o', 'd', 'r', 'm')) return InstOptions::kX86_ModRM;
    if (word.test('m', 'o', 'd', 'm', 'r')) return InstOptions::kX86_ModMR;
    if (word.test('r', 'e', 'p', 'n', 'e')) return InstOptions::kX86_Repne;
    if (word.test('r', 'e', 'p', 'n', 'z')) return InstOptions::kX86_Repne;
    if (word.test('s', 'h', 'o', 'r', 't')) return InstOptions::kShortForm;

    return InstOptions::kNone;
  }

  // Options of length '8':
  word.addLowercasedChar(s, 5);
  word.addLowercasedChar(s, 6);
  word.addLowercasedChar(s, 7);

  if (size == 8) {
    if (word.test('x', 'a', 'c', 'q', 'u', 'i', 'r', 'e')) return InstOptions::kX86_XAcquire;
    if (word.test('x', 'r', 'e', 'l', 'e', 'a', 's', 'e')) return InstOptions::kX86_XRelease;

    return InstOptions::kNone;
  }

  return InstOptions::kNone;
}

static InstOptions x86ParseAvx512Option(const uint8_t* s, size_t size) noexcept {
  constexpr uint32_t kMinSize = 3;
  constexpr uint32_t kMaxSize = 6;

  if (size < kMinSize || size > kMaxSize)
    return InstOptions::kNone;

  ParserUtils::WordParser word;

  // Options of length '3':
  word.addLowercasedChar(s, 0);
  word.addLowercasedChar(s, 1);
  word.addLowercasedChar(s, 2);

  if (size == 3) {
    if (word.test('s', 'a', 'e')) return InstOptions::kX86_SAE;

    return InstOptions::kNone;
  }

  if (size < 6)
    return InstOptions::kNone;

  // Options of length '6':
  word.addLowercasedChar(s, 3);
  word.addLowercasedChar(s, 4);
  word.addLowercasedChar(s, 5);

  if (size == 6) {
    if (word.test('r', 'n', '-', 's', 'a', 'e')) return InstOptions::kX86_ER | InstOptions::kX86_RN_SAE;
    if (word.test('r', 'd', '-', 's', 'a', 'e')) return InstOptions::kX86_ER | InstOptions::kX86_RD_SAE;
    if (word.test('r', 'u', '-', 's', 'a', 'e')) return InstOptions::kX86_ER | InstOptions::kX86_RU_SAE;
    if (word.test('r', 'z', '-', 's', 'a', 'e')) return InstOptions::kX86_ER | InstOptions::kX86_RZ_SAE;

    return InstOptions::kNone;
  }

  return InstOptions::kNone;
}

static x86::Mem::Broadcast x86ParseAvx512Broadcast(const uint8_t* s, size_t size) noexcept {
  constexpr uint32_t kMinSize = 4;
  constexpr uint32_t kMaxSize = 5;

  if (size < kMinSize || size > kMaxSize)
    return x86::Mem::Broadcast::kNone;

  ParserUtils::WordParser word;

  // Broadcast option of length '4':
  word.addLowercasedChar(s, 0);
  word.addLowercasedChar(s, 1);
  word.addLowercasedChar(s, 2);
  word.addLowercasedChar(s, 3);

  if (size == 4) {
    if (word.test('1', 't', 'o', '2')) return x86::Mem::Broadcast::k1To2;
    if (word.test('1', 't', 'o', '4')) return x86::Mem::Broadcast::k1To4;
    if (word.test('1', 't', 'o', '8')) return x86::Mem::Broadcast::k1To8;

    return x86::Mem::Broadcast::kNone;
  }

  // Broadcast option of length '5':
  word.addLowercasedChar(s, 4);

  if (size == 5) {
    if (word.test('1', 't', 'o', '1', '6')) return x86::Mem::Broadcast::k1To16;
    if (word.test('1', 't', 'o', '3', '2')) return x86::Mem::Broadcast::k1To32;
    if (word.test('1', 't', 'o', '6', '4')) return x86::Mem::Broadcast::k1To64;

    return x86::Mem::Broadcast::kNone;
  }

  return x86::Mem::Broadcast::kNone;
}

static uint32_t x86ParseDirective(const uint8_t* s, size_t size) noexcept {
  if (size < 2)
    return 0;

  ParserUtils::WordParser word;
  word.addLowercasedChar(s, 0);
  word.addLowercasedChar(s, 1);

  if (size == 2) {
    if (word.test('d', 'b')) return kX86DirectiveDB;
    if (word.test('d', 'w')) return kX86DirectiveDW;
    if (word.test('d', 'd')) return kX86DirectiveDD;
    if (word.test('d', 'q')) return kX86DirectiveDQ;
    return 0;
  }

  if (size < 5)
    return 0;

  word.addLowercasedChar(s, 2);
  word.addLowercasedChar(s, 3);
  word.addLowercasedChar(s, 4);
  if (size == 5) {
    if (word.test('a', 'l', 'i', 'g', 'n')) return kX86DirectiveAlign;
    return 0;
  }

  return 0;
}

static uint32_t x86ParseAlias(const uint8_t* s, size_t size) noexcept {
  if (size < 3)
    return x86::Inst::kIdNone;

  ParserUtils::WordParser word;
  word.addLowercasedChar(s, 0);
  word.addLowercasedChar(s, 1);
  word.addLowercasedChar(s, 2);
  if (size == 3) {
    if (word.test('s', 'a', 'l')) return x86::Inst::kIdShl;
    return x86::Inst::kIdNone;
  }

  word.addLowercasedChar(s, 3);
  if (size == 4) {
    if (word.test('i', 'n', 's', 'b')) return kX86AliasInsb;
    if (word.test('i', 'n', 's', 'w')) return kX86AliasInsw;
    if (word.test('i', 'n', 's', 'd')) return kX86AliasInsd;
    return x86::Inst::kIdNone;
  }

  word.addLowercasedChar(s, 4);
  if (size == 5) {
    if (word.test('c', 'm', 'p', 's', 'b')) return kX86AliasCmpsb;
    if (word.test('c', 'm', 'p', 's', 'w')) return kX86AliasCmpsw;
    if (word.test('c', 'm', 'p', 's', 'd')) return kX86AliasCmpsd;
    if (word.test('c', 'm', 'p', 's', 'q')) return kX86AliasCmpsq;

    if (word.test('l', 'o', 'd', 's', 'b')) return kX86AliasLodsb;
    if (word.test('l', 'o', 'd', 's', 'w')) return kX86AliasLodsw;
    if (word.test('l', 'o', 'd', 's', 'd')) return kX86AliasLodsd;
    if (word.test('l', 'o', 'd', 's', 'q')) return kX86AliasLodsq;

    if (word.test('m', 'o', 'v', 's', 'b')) return kX86AliasMovsb;
    if (word.test('m', 'o', 'v', 's', 'w')) return kX86AliasMovsw;
    if (word.test('m', 'o', 'v', 's', 'd')) return kX86AliasMovsd;
    if (word.test('m', 'o', 'v', 's', 'q')) return kX86AliasMovsq;

    if (word.test('s', 'c', 'a', 's', 'b')) return kX86AliasScasb;
    if (word.test('s', 'c', 'a', 's', 'w')) return kX86AliasScasw;
    if (word.test('s', 'c', 'a', 's', 'd')) return kX86AliasScasd;
    if (word.test('s', 'c', 'a', 's', 'q')) return kX86AliasScasq;

    if (word.test('s', 't', 'o', 's', 'b')) return kX86AliasStosb;
    if (word.test('s', 't', 'o', 's', 'w')) return kX86AliasStosw;
    if (word.test('s', 't', 'o', 's', 'd')) return kX86AliasStosd;
    if (word.test('s', 't', 'o', 's', 'q')) return kX86AliasStosq;

    if (word.test('o', 'u', 't', 's', 'b')) return kX86AliasOutsb;
    if (word.test('o', 'u', 't', 's', 'w')) return kX86AliasOutsw;
    if (word.test('o', 'u', 't', 's', 'd')) return kX86AliasOutsd;

    return x86::Inst::kIdNone;
  }

  return x86::Inst::kIdNone;
}

static Error x86ParseInstruction(AsmParser& parser, InstId& instId, InstOptions& options, AsmToken* token) noexcept {
  for (;;) {
    size_t size = token->size();
    uint8_t lower[32];

    if (size > ASMJIT_ARRAY_SIZE(lower))
      return DebugUtils::errored(kErrorInvalidInstruction);

    strToLower(lower, token->data(), size);

    // Try to match instruction alias, as there are some tricky ones.
    instId = x86ParseAlias(lower, size);
    if (instId == x86::Inst::kIdNone) {
      // If that didn't work out, try to match instruction as defined by AsmJit.
      instId = InstAPI::stringToInstId(parser.emitter()->arch(), reinterpret_cast<char*>(lower), size);
    }

    if (instId == x86::Inst::kIdNone) {
      // Maybe it's an option / prefix?
      InstOptions option = x86ParseInstOption(lower, size);
      if (option == InstOptions::kNone)
        return DebugUtils::errored(kErrorInvalidInstruction);

      // Refuse to parse the same option specified multiple times.
      if (ASMJIT_UNLIKELY(Support::test(options, option)))
        return DebugUtils::errored(kErrorOptionAlreadyDefined);

      options |= option;
      if (parser.nextToken(token) != AsmTokenType::kSym)
        return DebugUtils::errored(kErrorInvalidInstruction);
    }
    else {
      // Ok, we have an instruction. Now let's parse the next token and decide if it belongs to the instruction or not.
      // This is required to parse things such "jmp short" although we prefer "short jmp" (but the former is valid in
      // other assemblers).
      if (parser.nextToken(token) == AsmTokenType::kSym) {
        size = token->size();
        if (size <= ASMJIT_ARRAY_SIZE(lower)) {
          strToLower(lower, token->data(), size);
          InstOptions option = x86ParseInstOption(lower, size);
          if (option == InstOptions::kShortForm) {
            options |= option;
            return kErrorOk;
          }
        }
      }

      parser.putTokenBack(token);
      return kErrorOk;
    }
  }
}

static Error x86FixupInstruction(AsmParser& parser, BaseInst& inst, Operand_* operands, uint32_t& count) noexcept {
  uint32_t i;

  InstId& instId = inst._id;

  if (instId >= kX86AliasStart) {
    x86::Emitter* emitter = static_cast<x86::Emitter*>(parser._emitter);
    uint32_t memSize = 0;
    bool isStr = false;

    switch (instId) {
      case kX86AliasInsb: memSize = 1; instId = x86::Inst::kIdIns; isStr = true; break;
      case kX86AliasInsd: memSize = 4; instId = x86::Inst::kIdIns; isStr = true; break;
      case kX86AliasInsw: memSize = 2; instId = x86::Inst::kIdIns; isStr = true; break;

      case kX86AliasOutsb: memSize = 1; instId = x86::Inst::kIdOuts; isStr = true; break;
      case kX86AliasOutsd: memSize = 4; instId = x86::Inst::kIdOuts; isStr = true; break;
      case kX86AliasOutsw: memSize = 2; instId = x86::Inst::kIdOuts; isStr = true; break;

      case kX86AliasCmpsb: memSize = 1; instId = x86::Inst::kIdCmps; isStr = true; break;
      case kX86AliasCmpsd: memSize = 4;
        isStr = count == 0 || (count == 2 && operands[0].isMem() && operands[1].isMem());
        instId = isStr ? x86::Inst::kIdCmps : x86::Inst::kIdCmpsd;
        break;
      case kX86AliasCmpsq: memSize = 8; instId = x86::Inst::kIdCmps; isStr = true; break;
      case kX86AliasCmpsw: memSize = 2; instId = x86::Inst::kIdCmps; isStr = true; break;

      case kX86AliasMovsb: memSize = 1; instId = x86::Inst::kIdMovs; isStr = true; break;
      case kX86AliasMovsd: memSize = 4;
        isStr = count == 0 || (count == 2 && operands[0].isMem() && operands[1].isMem());
        instId = isStr ? x86::Inst::kIdMovs : x86::Inst::kIdMovsd;
        break;
      case kX86AliasMovsq: memSize = 8; instId = x86::Inst::kIdMovs; isStr = true; break;
      case kX86AliasMovsw: memSize = 2; instId = x86::Inst::kIdMovs; isStr = true; break;

      case kX86AliasLodsb: memSize = 1; instId = x86::Inst::kIdLods; isStr = true; break;
      case kX86AliasLodsd: memSize = 4; instId = x86::Inst::kIdLods; isStr = true; break;
      case kX86AliasLodsq: memSize = 8; instId = x86::Inst::kIdLods; isStr = true; break;
      case kX86AliasLodsw: memSize = 2; instId = x86::Inst::kIdLods; isStr = true; break;

      case kX86AliasScasb: memSize = 1; instId = x86::Inst::kIdScas; isStr = true; break;
      case kX86AliasScasd: memSize = 4; instId = x86::Inst::kIdScas; isStr = true; break;
      case kX86AliasScasq: memSize = 8; instId = x86::Inst::kIdScas; isStr = true; break;
      case kX86AliasScasw: memSize = 2; instId = x86::Inst::kIdScas; isStr = true; break;

      case kX86AliasStosb: memSize = 1; instId = x86::Inst::kIdStos; isStr = true; break;
      case kX86AliasStosd: memSize = 4; instId = x86::Inst::kIdStos; isStr = true; break;
      case kX86AliasStosq: memSize = 8; instId = x86::Inst::kIdStos; isStr = true; break;
      case kX86AliasStosw: memSize = 2; instId = x86::Inst::kIdStos; isStr = true; break;
        break;
    }

    if (isStr) {
      if (count == 0) {
        OperandSignature regSignature = OperandSignature{
          memSize == 1 ? x86::GpbLo::kSignature :
          memSize == 2 ? x86::Gpw::kSignature :
          memSize == 4 ? x86::Gpd::kSignature : x86::Gpq::kSignature};

        // String instructions aliases.
        count = 2;
        switch (instId) {
          case x86::Inst::kIdCmps: operands[0] = emitter->ptr_zsi(); operands[1] = emitter->ptr_zdi(); break;
          case x86::Inst::kIdMovs: operands[0] = emitter->ptr_zdi(); operands[1] = emitter->ptr_zsi(); break;
          case x86::Inst::kIdLods:
          case x86::Inst::kIdScas: operands[0] = BaseReg(regSignature, x86::Gp::kIdAx); operands[1] = emitter->ptr_zdi(); break;
          case x86::Inst::kIdStos: operands[0] = emitter->ptr_zdi(); operands[1] = BaseReg(regSignature, x86::Gp::kIdAx); break;
        }
      }

      for (i = 0; i < count; i++) {
        if (operands[i].isMem()) {
          x86::Mem& mem = operands[i].as<x86::Mem>();

          if (mem.size() == 0)
            mem.setSize(memSize);

          if (mem.baseId() == x86::Gp::kIdDi && mem.segmentId() == x86::SReg::kIdEs)
            mem.resetSegment();
        }
      }
    }
  }

  for (i = 0; i < count; i++) {
    Operand_& op = operands[i];

    // If the parsed memory segment is the default one, remove it. AsmJit always emits segment-override if the
    // segment is specified, this is good on AsmJit side, but causes problems here as it's not necessary to emit
    // 'ds:' everywhere if the input contains it (and it's common).
    if (op.isMem() && op.as<x86::Mem>().hasSegment()) {
      x86::Mem& mem = op.as<x86::Mem>();

      // Default to `ds` segment for most instructions.
      uint32_t defaultSeg = x86::SReg::kIdDs;

      // Default to `ss` segment if the operand has esp|rsp or ebp|rbp base.
      if (mem.hasBaseReg()) {
        if (mem.baseId() == x86::Gp::kIdSp || mem.baseId() == x86::Gp::kIdBp)
          defaultSeg = x86::SReg::kIdSs;
      }

      if (mem.segmentId() == defaultSeg)
        mem.resetSegment();
    }
  }

  return kErrorOk;
}

Error AsmParser::parse(const char* input, size_t size) noexcept {
  setInput(input, size);
  while (!isEndOfInput())
    ASMJIT_PROPAGATE(parseCommand());
  return kErrorOk;
}

Error AsmParser::parseCommand() noexcept {
  AsmToken token;
  AsmTokenType tType = nextToken(&token);

  _currentCommandOffset = (size_t)(reinterpret_cast<const char*>(token.data()) - input());

  if (tType == AsmTokenType::kSym) {
    AsmToken tmp;

    tType = nextToken(&tmp);
    if (tType == AsmTokenType::kColon) {
      // Parse label.
      Label label;
      ASMJIT_PROPAGATE(asmHandleSymbol(*this, label, token.data(), token.size()));
      ASMJIT_PROPAGATE(_emitter->bind(label));

      // Must be valid if we passed through asmHandleSymbol() and bind().
      LabelEntry* le = _emitter->code()->labelEntry(label);
      ASMJIT_ASSERT(le);

      if (le->type() == LabelType::kGlobal)
        _currentGlobalLabelId = label.id();

      return kErrorOk;
    }

    if (token.dataAt(0) == '.') {
      // Parse directive (instructions never start with '.').
      uint32_t directive = x86ParseDirective(token.data() + 1, token.size() - 1);

      if (directive == kX86DirectiveAlign) {
        if (tType != AsmTokenType::kU64)
          return DebugUtils::errored(kErrorInvalidState);

        if (tmp.u64Value() > std::numeric_limits<uint32_t>::max() || !Support::isPowerOf2(tmp.u64Value()))
          return DebugUtils::errored(kErrorInvalidState);

        ASMJIT_PROPAGATE(_emitter->align(AlignMode::kCode, uint32_t(tmp.u64Value())));

        tType = nextToken(&token);
        // Fall through as we would like to see EOL or EOF.
      }
      else if (directive >= kX86DirectiveDB && directive <= kX86DirectiveDQ) {
        if (tType != AsmTokenType::kU64)
          return DebugUtils::errored(kErrorInvalidState);

        uint32_t nBytes   = (directive == kX86DirectiveDB) ? 1 :
                            (directive == kX86DirectiveDW) ? 2 :
                            (directive == kX86DirectiveDD) ? 4 : 8;
        uint64_t maxValue = Support::lsbMask<uint64_t>(nBytes * 8);

        StringTmp<512> db;
        for (;;) {
          if (tType != AsmTokenType::kU64)
            return DebugUtils::errored(kErrorInvalidState);

          if (tmp.u64Value() > maxValue)
            return DebugUtils::errored(kErrorInvalidImmediate);

          db.append(tmp.valueChars(), nBytes);

          tType = nextToken(&tmp);
          if (tType != AsmTokenType::kComma)
            break;

          tType = nextToken(&tmp);
        }

        ASMJIT_PROPAGATE(_emitter->embed(db.data(), db.size()));
      }
      else {
        return DebugUtils::errored(kErrorInvalidDirective);
      }
    }
    else {
      // Parse instruction.
      putTokenBack(&tmp);

      BaseInst inst;
      ASMJIT_PROPAGATE(x86ParseInstruction(*this, inst._id, inst._options, &token));

      // Parse operands.
      uint32_t count = 0;
      Operand_ operands[6];
      x86::Mem* memOp = nullptr;

      for (;;) {
        tType = nextToken(&token);

        // Instruction without operands...
        if ((tType == AsmTokenType::kNL || tType == AsmTokenType::kEnd) && count == 0)
          break;

        // Parse {AVX-512} options that act as operand (valid syntax).
        if (tType == AsmTokenType::kLCurl) {
          constexpr InstOptions kAllowed =
            InstOptions::kX86_ER     |
            InstOptions::kX86_SAE    |
            InstOptions::kX86_RN_SAE |
            InstOptions::kX86_RD_SAE |
            InstOptions::kX86_RU_SAE |
            InstOptions::kX86_RZ_SAE ;

          tType = nextToken(&tmp, ParseFlags::kParseSymbol | ParseFlags::kIncludeDashes);
          if (tType != AsmTokenType::kSym && tType != AsmTokenType::kNSym)
            return DebugUtils::errored(kErrorInvalidState);

          tType = nextToken(&token);
          if (tType != AsmTokenType::kRCurl)
            return DebugUtils::errored(kErrorInvalidState);

          InstOptions option = x86ParseAvx512Option(tmp.data(), tmp.size());
          if (option == InstOptions::kNone || Support::test(option, ~kAllowed))
            return DebugUtils::errored(kErrorInvalidOption);

          if (inst.hasOption(option))
            return DebugUtils::errored(kErrorOptionAlreadyDefined);

          inst.addOptions(option);
          tType = nextToken(&token);
        }
        else {
          if (count == ASMJIT_ARRAY_SIZE(operands))
            return DebugUtils::errored(kErrorInvalidInstruction);

          // Parse operand.
          ASMJIT_PROPAGATE(x86ParseOperand(*this, operands[count], &token));

          if (operands[count].isMem())
            memOp = static_cast<x86::Mem*>(&operands[count]);

          // Parse {AVX-512} option(s) immediately next to the operand.
          tType = nextToken(&token);
          if (tType == AsmTokenType::kLCurl) {
            do {
              tType = nextToken(&tmp, ParseFlags::kParseSymbol | ParseFlags::kIncludeDashes);
              if (tType != AsmTokenType::kSym && tType != AsmTokenType::kNSym)
                return DebugUtils::errored(kErrorInvalidState);

              tType = nextToken(&token);
              if (tType != AsmTokenType::kRCurl)
                return DebugUtils::errored(kErrorInvalidState);

              uint32_t maskRegId = 0;
              size_t size = tmp.size();
              const uint8_t* str = tmp.data();

              if (size == 2 && (str[0] == 'k' || str[1] == 'K') && (maskRegId = (str[1] - (uint8_t)'0')) < 8) {
                RegOnly& extraReg = inst._extraReg;
                if (count != 0)
                  return DebugUtils::errored(kErrorInvalidOption);

                if (!extraReg.isNone())
                  return DebugUtils::errored(kErrorOptionAlreadyDefined);

                extraReg.init(x86::KReg(maskRegId));
              }
              else if (size == 1 && (str[0] == 'z' || str[1] == 'Z')) {
                if (count != 0)
                  return DebugUtils::errored(kErrorInvalidOption);

                if (inst.hasOption(InstOptions::kX86_ZMask))
                  return DebugUtils::errored(kErrorOptionAlreadyDefined);

                inst.addOptions(InstOptions::kX86_ZMask);
              }
              else {
                InstOptions option = x86ParseAvx512Option(str, size);
                if (option != InstOptions::kNone) {
                  if (inst.hasOption(option))
                    return DebugUtils::errored(kErrorOptionAlreadyDefined);
                  inst.addOptions(option);
                }
                else {
                  x86::Mem::Broadcast broadcast = x86ParseAvx512Broadcast(str, size);
                  if (broadcast == x86::Mem::Broadcast::kNone)
                    return DebugUtils::errored(kErrorInvalidOption);

                  if (!memOp || memOp->hasBroadcast())
                    return DebugUtils::errored(kErrorInvalidBroadcast);

                  memOp->setBroadcast(broadcast);
                }
              }

              tType = nextToken(&token);
            } while (tType == AsmTokenType::kLCurl);
          }

          count++;
        }

        if (tType == AsmTokenType::kComma)
          continue;

        if (tType == AsmTokenType::kNL || tType == AsmTokenType::kEnd)
          break;

        return DebugUtils::errored(kErrorInvalidState);
      }

      ASMJIT_PROPAGATE(x86FixupInstruction(*this, inst, operands, count));
      ASMJIT_PROPAGATE(InstAPI::validate(_emitter->arch(), inst, operands, count));

      _emitter->setInstOptions(inst.options());
      _emitter->setExtraReg(inst.extraReg());
      ASMJIT_PROPAGATE(_emitter->emitOpArray(inst.id(), operands, count));
    }
  }

  if (tType == AsmTokenType::kNL)
    return kErrorOk;

  if (tType == AsmTokenType::kEnd) {
    _endOfInput = true;
    return kErrorOk;
  }

  return DebugUtils::errored(kErrorInvalidState);
}

} // {asmtk}
