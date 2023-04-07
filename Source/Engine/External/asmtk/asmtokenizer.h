// [AsmTk]
// Assembler toolkit based on AsmJit.
//
// [License]
// Zlib - See LICENSE.md file in the package.

#ifndef _ASMTK_ASMTOKENIZER_H
#define _ASMTK_ASMTOKENIZER_H

#include "./globals.h"
#include "./strtod.h"

namespace asmtk {

enum class AsmTokenType : uint8_t {
  kEnd,
  kNL,
  kSym,
  kNSym,
  kU64,
  kF64,
  kLCurl,
  kRCurl,
  kLBracket,
  kRBracket,
  kLParen,
  kRParen,
  kAdd,
  kSub,
  kMul,
  kDiv,
  kComma,
  kColon,
  kOther,
  kInvalid
};

//! Token.
struct AsmToken {
  //! \name Members
  //! \{

  AsmTokenType _type;
  const uint8_t* _data;
  size_t _size;

  union {
    double _f64;
    int64_t _i64;
    uint64_t _u64;

    char _valueChars[8];
    uint8_t _valueBytes[8];
  };

  //! \}

  template<typename... Args>
  inline bool _isImpl(size_t index, char c) noexcept {
    return _data[index] == c;
  }

  template<typename... Args>
  inline bool _isImpl(size_t index, char c, Args&&... args) noexcept {
    return _data[index] == c && _isImpl(index + 1, args...);
  }

  template<typename... Args>
  inline bool is(Args&&... args) noexcept {
    return _size == sizeof...(args) && _isImpl(0, args...);
  }

  inline AsmTokenType type() const noexcept { return _type; }
  inline const uint8_t* data() const noexcept { return _data; }
  inline size_t size() const noexcept { return _size; }

  inline uint8_t dataAt(size_t index) const noexcept {
    ASMJIT_ASSERT(index < _size);
    return _data[index];
  }

  inline double f64Value() const noexcept { return _f64; }
  inline int64_t i64Value() const noexcept { return _i64; }
  inline uint64_t u64Value() const noexcept { return _u64; }
  inline const char* valueChars() const noexcept { return _valueChars; }
  inline const uint8_t* valueBytes() const noexcept { return _valueBytes; }

  inline void reset() noexcept {
    _type = AsmTokenType::kEnd;
    _data = nullptr;
    _size = 0;
    _u64 = 0;
  }

  inline AsmTokenType setData(AsmTokenType type, const uint8_t* data, size_t size) noexcept {
    _data = data;
    _size = size;
    _type = type;
    return type;
  }

  inline AsmTokenType setData(AsmTokenType type, const uint8_t* data, const uint8_t* end) noexcept {
    return setData(type, data, (size_t)(end - data));
  }
};

enum class ParseFlags {
  //! No flags.
  kNone = 0,
  //! Don't attempt to parse number (always parse symbol).
  kParseSymbol = 0x00000001u,
  //! Consider dashes as text in a parsed symbol.
  kIncludeDashes = 0x00000002u
};
ASMJIT_DEFINE_ENUM_FLAGS(ParseFlags)

//! Tokenizer.
class AsmTokenizer {
public:
  //! Creates a tokanizer.
  ASMTK_API AsmTokenizer() noexcept;
  //! Destroys the tokanizer.
  ASMTK_API ~AsmTokenizer() noexcept;

  //! Parses a next `token` and advances.
  ASMTK_API AsmTokenType next(AsmToken* token, ParseFlags parseFlags = ParseFlags::kNone) noexcept;

  //! Puts a token back to the tokenizer so that `next()` would parse it again.
  inline void putBack(AsmToken* token) noexcept {
    _cur = token->data();
  }

  //! Sets the input of the tokenizer to `input` and `size`. The input doesn't
  //! have to be null terminated as the tokenizer would never go beyond the
  //! `size` specified. This means that the tokenizer can be used with string
  //! views.
  inline void setInput(const uint8_t* input, size_t size) noexcept {
    _input = input;
    _end = input + size;
    _cur = input;
  }

  const uint8_t* _input;
  const uint8_t* _end;
  const uint8_t* _cur;

  StrToD _stodctx;
};

} // {asmtk}

#endif // _ASMTK_ASMTOKENIZER_H
