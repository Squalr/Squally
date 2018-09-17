#pragma once

#include "string"

using namespace std;

/// <summary>
/// The native function to get the version of FASM compiler embedded in Fasm.obj.
/// </summary>
/// <returns>The return valus is a double word containg major version in lower 16 bits, and minor version in the higher 16 bits.</returns>
extern "C" int fasm_GetVersion();

/// <summary>
/// The native function to assemble mnemonics of FASM compiler embedded in Fasm.obj.
/// </summary>
/// <param name="source">The mnemonic to assemble.</param>
/// <param name="lpMemory">The pointer to a buffer used to assemble mnemonics.</param>
/// <param name="memorySize">The memory size allocated for the buffer.</param>
/// <param name="passLimit">The maximum number of pass to perform.</param>
/// <returns>The return value is an FasmResults enumeration.</returns>
extern "C" int fasm_Assemble(char* szSource, unsigned char* lpMemory, int nSize, int nPassesLimit, void* hDisplayPipe);

class Fasm
{
public:

	/// <summary>
	/// The enumeration containing all results of FASM compiler.
	/// </summary>
	enum FasmResultCode
	{
		Ok = 0,
		Working = 1,
		Error = 2,
		InvalidParameter = -1,
		OutOfMemory = -2,
		StackOverflow = -3,
		SourceNotFound = -4,
		UnexpectedEndOfSource = -5,
		CannotGenerateCode = -6,
		FormatLimitationsExcedded = -7,
		WriteFailed = -8
	};

	/// <summary>
	/// The enumeration containing all errors of FASM compiler.
	/// </summary>
	enum FasmErrorCode
	{
		FileNotFound = -101,
		ErrorReadingFile = -102,
		InvalidFileFormat = -103,
		InvalidMacroArguments = -104,
		IncompleteMacro = -105,
		UnexpectedCharacters = -106,
		InvalidArgument = -107,
		IllegalInstruction = -108,
		InvalidOperand = -109,
		InvalidOperandSize = -110,
		OperandSizeNotSpecified = -111,
		OperandSizesDoNotMatch = -112,
		InvalidAddressSize = -113,
		AddressSizesDoNotAgree = -114,
		DisallowedCombinationOfRegisters = -115,
		LongImmediateNotEncodable = -116,
		RelativeJumpOutOfRange = -117,
		InvalidExpression = -118,
		InvalidAddress = -119,
		InvalidValue = -120,
		ValueOutOfRange = -121,
		UndefinedSymbol = -122,
		InvalidUseOfSymbol = -123,
		NameTooLong = -124,
		InvalidName = -125,
		ReservedWordUsedAsSymbol = -126,
		SymbolAlreadyDefined = -127,
		MissingEndQuote = -128,
		MissingEndDirective = -129,
		UnexpectedInstruction = -130,
		ExtraCharactersOnLine = -131,
		SectionNotAlignedEnough = -132,
		SettingAlreadySpecified = -133,
		DataAlreadyDefined = -134,
		TooManyRepeats = -135,
		SymbolOutOfScope = -136,
		UserError = -140,
		AssertionFailed = -141
	};

	struct NativeLineHeader
	{
		char* FilePath;

		int LineNumber;

		union
		{
			int FileOffset;
			NativeLineHeader* MacroCallingFile;
		};

		NativeLineHeader* MacroLine;
	};

	struct FasmResult
	{
		FasmResultCode Condition;

		union
		{
			int OutputLength;
			FasmErrorCode Error;
		};

		union
		{
			unsigned char* OutputData;
			NativeLineHeader* ErrorLine;
		};
	};

	static FasmResult* assemble(string assembly, void* baseAddress);
};