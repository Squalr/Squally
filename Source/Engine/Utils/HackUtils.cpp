#include "HackUtils.h"

#include <algorithm>
#include <bitset>
#include <exception>
#include <iomanip>
#include <sstream>

#include "asmjit.h"
#include "udis86.h"

HackUtils::CompileResult HackUtils::assemble(std::string assembly, void* addressStart)
{
	CompileResult compileResult;
	/*
	CodeInfo ci(ArchInfo::kTypeX86);
	CodeHolder code;
	code.init(ci);

	// Attach X86Assembler `code`.
	X86Assembler a(&code);

	// Create AsmParser that will emit to X86Assembler.
	AsmParser p(&a);

	// Parse some assembly.
	Error err = p.parse(
		"push eax\n"
		"mov eax, ebx\n"
		"pop eax\n"
	);

	// Error handling (use asmjit::ErrorHandler for more robust error handling).
	if (err)
	{
		printf("ERROR: %08x (%s)\n", err, DebugUtils::errorAsString(err));
		//return 1;
	}

	// If we are done, you must detach the Assembler from CodeHolder or sync
	// it, so its internal state and position is synced with CodeHolder.
	code.sync();

	// Now you can print the code, which is stored in the first section (.text).
	CodeBuffer& buffer = code.getSectionEntry(0)->getBuffer();
	//dumpCode(buffer.getData(), buffer.getLength());

	//Fasm::FasmResult* fasmResult = Fasm::assemble(assembly, addressStart);
	//HackUtils::CompileResult compileResult = HackUtils::constructCompileResult(fasmResult);
	*/
	//delete(fasmResult);
	return compileResult;
}

std::string HackUtils::disassemble(void* bytes, int length)
{
	static ud_t ud_obj;
	static bool initialized = false;

	if (bytes == nullptr)
	{
		return "nullptr";
	}

	if (length <= 0)
	{
		return "";
	}

	// Only initialize the disassembler once
	if (!initialized)
	{
		ud_init(&ud_obj);
		ud_set_mode(&ud_obj, sizeof(void*) * 8);
		ud_set_syntax(&ud_obj, UD_SYN_INTEL);
	}

	ud_set_input_buffer(&ud_obj, (unsigned char*)bytes, length);

	std::string instructions = "";

	while (ud_disassemble(&ud_obj))
	{
		instructions += ud_insn_asm(&ud_obj);
		instructions += "\n";
	}

	return instructions;
}

std::string HackUtils::hexAddressOf(void* address, bool zeroPad, bool prefix)
{
	std::stringstream stream;

	// Convert to hex
	stream << std::hex << (unsigned int)((unsigned long)(address));
	std::string hexAddress = stream.str();

	// Convert to upper
	std::transform(hexAddress.begin(), hexAddress.end(), hexAddress.begin(), ::toupper);

	if (zeroPad)
	{
		while (hexAddress.length() < sizeof(int*) * 2)
		{
			hexAddress = "0" + hexAddress;
		}
	}

	if (prefix)
	{
		hexAddress = "0x" + hexAddress;
	}

	return hexAddress;
}

std::string HackUtils::toHex(int value)
{
	std::stringstream stream;

	// Convert to hex
	stream << std::hex << (int)(value);
	std::string hexString = stream.str();

	// Convert to upper
	std::transform(hexString.begin(), hexString.end(), hexString.begin(), ::toupper);

	return hexString;
}

std::string HackUtils::toBinary4(int value)
{
	std::stringstream stream;

	// Convert to hex
	stream << std::bitset<4>(value);
	std::string binaryString = stream.str();

	return binaryString;
}

HackUtils::DataType HackUtils::stdTypeToDataType(const std::type_info* typeInfo)
{
	std::string typeName = typeInfo->name();

	if (typeName == "char")
	{
		return HackUtils::DataType::Byte;
	}
	else if (typeName == "signed char")
	{
		return HackUtils::DataType::SByte;
	}
	else if (typeName == "short")
	{
		return HackUtils::DataType::Int16;
	}
	else if (typeName == "unsigned short")
	{
		return HackUtils::DataType::UInt16;
	}
	else if (typeName == "int")
	{
		return HackUtils::DataType::Int32;
	}
	else if (typeName == "unsigned int")
	{
		return HackUtils::DataType::UInt32;
	}
	else if (typeName == "long")
	{
		return HackUtils::DataType::Int64;
	}
	else if (typeName == "unsigned long")
	{
		return HackUtils::DataType::UInt64;
	}
	else if (typeName == "float")
	{
		return HackUtils::DataType::Single;
	}
	else if (typeName == "double")
	{
		return HackUtils::DataType::Double;
	}
	else
	{
		throw std::invalid_argument("Invalid data type");
	}
}

std::string HackUtils::dataTypeToString(HackUtils::DataType dataType)
{
	switch (dataType)
	{
	case HackUtils::DataType::Byte:
		return "Byte";
	case HackUtils::DataType::SByte:
		return "SByte";
	case HackUtils::DataType::Int16:
		return "Int16";
	case HackUtils::DataType::UInt16:
		return "UInt16";
	case HackUtils::DataType::Int32:
		return "Int32";
	case HackUtils::DataType::UInt32:
		return "UInt32";
	case HackUtils::DataType::Int64:
		return "Int64";
	case HackUtils::DataType::UInt64:
		return "UInt64";
	case HackUtils::DataType::Single:
		return "Single";
	case HackUtils::DataType::Double:
		return "Double";
	default:
		throw std::invalid_argument("Invalid data type");
	}
}

std::string HackUtils::valueStringOf(void* dataPointer, HackUtils::DataType dataType)
{
	switch (dataType)
	{
	case HackUtils::DataType::Byte:
		return std::to_string((*(unsigned char*)dataPointer));
	case HackUtils::DataType::SByte:
		return std::to_string((*(signed char*)dataPointer));
	case HackUtils::DataType::Int16:
		return std::to_string((*(short*)dataPointer));
	case HackUtils::DataType::UInt16:
		return std::to_string((*(unsigned short*)dataPointer));
	case HackUtils::DataType::Int32:
		return std::to_string((*(int*)dataPointer));
	case HackUtils::DataType::UInt32:
		return std::to_string((*(unsigned int*)dataPointer));
	case HackUtils::DataType::Int64:
		return std::to_string((*(long*)dataPointer));
	case HackUtils::DataType::UInt64:
		return std::to_string((*(unsigned long*)dataPointer));
	case HackUtils::DataType::Single:
		return std::to_string((*(float*)dataPointer));
	case HackUtils::DataType::Double:
		return std::to_string((*(double*)dataPointer));
	default:
		throw std::invalid_argument("Invalid data type");
	}
}

std::string HackUtils::arrayOfByteStringOf(void* dataPointer, int length, int maxLength)
{
	std::string result = std::string("[");

	for (int index = 0; index < length; index++)
	{
		if (index >= maxLength)
		{
			result.append(" ...");
			break;
		}

		std::stringstream stream;

		// Convert to hex
		stream << std::hex << (int)(((unsigned char*)dataPointer)[index]);
		std::string hexByte = stream.str();

		// Convert to upper
		std::transform(hexByte.begin(), hexByte.end(), hexByte.begin(), ::toupper);

		result.append(hexByte);

		if (index < length - 1)
		{
			result.append(", ");
		}
	}

	result.append("]");

	return result;
}

/*
HackUtils::CompileResult HackUtils::constructCompileResult(Fasm::FasmResult* fasmResult)
{
	// Note the 2 here is due to the first two lines of FASM specifying 32/64 bit and the origin point
	const int lineOffset = 2;

	CompileResult compileResult;

	if (fasmResult->ErrorLine != nullptr)
	{
		compileResult.errorData.lineNumber = fasmResult->ErrorLine->LineNumber - lineOffset;
	}
	else
	{
		compileResult.errorData.lineNumber = 0;
	}

	switch (fasmResult->Error)
	{
	case Fasm::FasmErrorCode::FileNotFound:
		compileResult.errorData.message = "File Not Found";
		break;
	case Fasm::FasmErrorCode::ErrorReadingFile:
		compileResult.errorData.message = "Error Reading File";
		break;
	case Fasm::FasmErrorCode::InvalidFileFormat:
		compileResult.errorData.message = "Invalid File Format";
		break;
	case Fasm::FasmErrorCode::InvalidMacroArguments:
		compileResult.errorData.message = "Invalid Macro Arguments";
		break;
	case Fasm::FasmErrorCode::IncompleteMacro:
		compileResult.errorData.message = "Incomplete Macro";
		break;
	case Fasm::FasmErrorCode::UnexpectedCharacters:
		compileResult.errorData.message = "Unexpected Characters";
		break;
	case Fasm::FasmErrorCode::InvalidArgument:
		compileResult.errorData.message = "Invalid Argument";
		break;
	case Fasm::FasmErrorCode::IllegalInstruction:
		compileResult.errorData.message = "Illegal Instruction";
		break;
	case Fasm::FasmErrorCode::InvalidOperand:
		compileResult.errorData.message = "Invalid Operand";
		break;
	case Fasm::FasmErrorCode::InvalidOperandSize:
		compileResult.errorData.message = "Invalid Operand Size";
		break;
	case Fasm::FasmErrorCode::OperandSizeNotSpecified:
		compileResult.errorData.message = "Operand Size Not Specified";
		break;
	case Fasm::FasmErrorCode::OperandSizesDoNotMatch:
		compileResult.errorData.message = "Operand Sizes Do Not Match";
		break;
	case Fasm::FasmErrorCode::InvalidAddressSize:
		compileResult.errorData.message = "Invalid Address Size";
		break;
	case Fasm::FasmErrorCode::AddressSizesDoNotAgree:
		compileResult.errorData.message = "Address Sizes Do Not Agree";
		break;
	case Fasm::FasmErrorCode::DisallowedCombinationOfRegisters:
		compileResult.errorData.message = "Disallowed Combination Of Registers";
		break;
	case Fasm::FasmErrorCode::LongImmediateNotEncodable:
		compileResult.errorData.message = "Long Immediate Not Encodable";
		break;
	case Fasm::FasmErrorCode::RelativeJumpOutOfRange:
		compileResult.errorData.message = "Relative Jump Out Of Range";
		break;
	case Fasm::FasmErrorCode::InvalidExpression:
		compileResult.errorData.message = "Invalid Expression";
		break;
	case Fasm::FasmErrorCode::InvalidAddress:
		compileResult.errorData.message = "Invalid Address";
		break;
	case Fasm::FasmErrorCode::InvalidValue:
		compileResult.errorData.message = "Invalid Value";
		break;
	case Fasm::FasmErrorCode::ValueOutOfRange:
		compileResult.errorData.message = "Value Out Of Range";
		break;
	case Fasm::FasmErrorCode::UndefinedSymbol:
		compileResult.errorData.message = "Undefined Symbol";
		break;
	case Fasm::FasmErrorCode::InvalidUseOfSymbol:
		compileResult.errorData.message = "Invalid Use Of Symbol";
		break;
	case Fasm::FasmErrorCode::NameTooLong:
		compileResult.errorData.message = "Name Too Long";
		break;
	case Fasm::FasmErrorCode::InvalidName:
		compileResult.errorData.message = "Invalid Name";
		break;
	case Fasm::FasmErrorCode::ReservedWordUsedAsSymbol:
		compileResult.errorData.message = "Reserved Word Used As Symbol";
		break;
	case Fasm::FasmErrorCode::SymbolAlreadyDefined:
		compileResult.errorData.message = "Symbol Already Defined";
		break;
	case Fasm::FasmErrorCode::MissingEndQuote:
		compileResult.errorData.message = "Missing End Quote";
		break;
	case Fasm::FasmErrorCode::MissingEndDirective:
		compileResult.errorData.message = "Missing End Directive";
		break;
	case Fasm::FasmErrorCode::UnexpectedInstruction:
		compileResult.errorData.message = "Unexpected Instruction";
		break;
	case Fasm::FasmErrorCode::ExtraCharactersOnLine:
		compileResult.errorData.message = "Extra Characters On Line";
		break;
	case Fasm::FasmErrorCode::SectionNotAlignedEnough:
		compileResult.errorData.message = "Section Not Aligned Enough";
		break;
	case Fasm::FasmErrorCode::SettingAlreadySpecified:
		compileResult.errorData.message = "Setting Already Specified";
		break;
	case Fasm::FasmErrorCode::DataAlreadyDefined:
		compileResult.errorData.message = "Data Already Defined";
		break;
	case Fasm::FasmErrorCode::TooManyRepeats:
		compileResult.errorData.message = "Too Many Repeats";
		break;
	case Fasm::FasmErrorCode::SymbolOutOfScope:
		compileResult.errorData.message = "Symbol Out Of Scope";
		break;
	case Fasm::FasmErrorCode::UserError:
		compileResult.errorData.message = "User Error";
		break;
	case Fasm::FasmErrorCode::AssertionFailed:
		compileResult.errorData.message = "Assertion Failed";
		break;
	default:
		compileResult.errorData.message = "";
		break;
	}

	switch (fasmResult->Condition)
	{
	case Fasm::FasmResultCode::CannotGenerateCode:
	case Fasm::FasmResultCode::Error:
	case Fasm::FasmResultCode::FormatLimitationsExcedded:
	case Fasm::FasmResultCode::InvalidParameter:
	case Fasm::FasmResultCode::OutOfMemory:
	case Fasm::FasmResultCode::SourceNotFound:
	case Fasm::FasmResultCode::StackOverflow:
	case Fasm::FasmResultCode::UnexpectedEndOfSource:
	case Fasm::FasmResultCode::Working:
	case Fasm::FasmResultCode::WriteFailed:
	{
		compileResult.hasError = true;
		break;
	}
	case Fasm::FasmResultCode::Ok:
	default:
		compileResult.byteCount = fasmResult->OutputLength;
		compileResult.compiledBytes = new unsigned char[fasmResult->OutputLength];
		memcpy(compileResult.compiledBytes, fasmResult->OutputData, fasmResult->OutputLength);
		compileResult.hasError = false;
		break;
	}

	return compileResult;
}
*/
