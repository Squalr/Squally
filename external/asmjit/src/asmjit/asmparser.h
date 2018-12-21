// [AsmTk]
// Assembler toolkit based on AsmJit.
//
// [License]
// Zlib - See LICENSE.md file in the package.

// [Guard]
#ifndef _ASMTK_ASMPARSER_H
#define _ASMTK_ASMPARSER_H

// [Dependencies]
#include "./strtod.h"
#include "./asmtokenizer.h"

namespace asmtk {

using asmjit::Error;

// ============================================================================
// [asmtk::AsmParser]
// ============================================================================

//! Asm parser.
class AsmParser {
public:
  typedef Error (ASMJIT_CDECL* UnknownSymbolHandler)(AsmParser* parser, asmjit::Operand* out, const char* name, size_t len);

  AsmParser(asmjit::CodeEmitter* emitter);
  ~AsmParser();

  Error parse(const char* input, size_t len = asmjit::Globals::kInvalidIndex);

  // --------------------------------------------------------------------------
  // [Accessors]
  // --------------------------------------------------------------------------

  ASMJIT_INLINE asmjit::CodeEmitter* getEmitter() const { return _emitter; }

  ASMJIT_INLINE bool hasUnknownSymbolHandler() const { return _unknownSymbolHandler != NULL; }

  ASMJIT_INLINE UnknownSymbolHandler getUnknownSymbolHandler() const { return _unknownSymbolHandler; }
  ASMJIT_INLINE void* getUnknownSymbolHandlerData() const { return _unknownSymbolHandlerData; }

  ASMJIT_INLINE void setUnknownSymbolHandler(UnknownSymbolHandler handler, void* data = NULL) {
    _unknownSymbolHandler = handler;
    _unknownSymbolHandlerData = data;
  }
  ASMJIT_INLINE void resetUnknownSymbolHandler() { setUnknownSymbolHandler((UnknownSymbolHandler)NULL, NULL); }

  // --------------------------------------------------------------------------
  // [Members]
  // --------------------------------------------------------------------------

  asmjit::CodeEmitter* _emitter;
  AsmTokenizer _tokenizer;

  UnknownSymbolHandler _unknownSymbolHandler;
  void* _unknownSymbolHandlerData;
};

} // asmtk namespace

// [Guard]
#endif // _ASMTK_ASMPARSER_H
