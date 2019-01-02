#include "HackUtils.h"

#include <algorithm>
#include <bitset>
#include <iomanip>
#include <sstream>

#include "asmjit.h"
#include "udis86.h"

#include "Engine/asmtk/asmtk.h"
#include "Engine/Utils/LogUtils.h"

#if __GNUC__ || __clang__
	#include <unistd.h>
	#include <sys/mman.h>
#endif

using namespace asmjit;
using namespace asmtk;

void HackUtils::setAllMemoryPermissions(void* address, int length)
{
	#ifdef _WIN32
		DWORD old;
		VirtualProtect(address, length, PAGE_EXECUTE_READWRITE, &old);
	#else
		// Unix requires changing memory protection on the start of the page, not just the address
		size_t pageSize = sysconf(_SC_PAGESIZE);
		void* pageStart = (void*)((unsigned long)address & -pageSize);
		int newLength = (int)((unsigned long)address + length - (unsigned long)pageStart);

		mprotect(pageStart, newLength, PROT_READ | PROT_WRITE | PROT_EXEC);
	#endif
}

void HackUtils::writeMemory(void* to, void* from, int length)
{
	HackUtils::setAllMemoryPermissions(to, length);
	HackUtils::setAllMemoryPermissions(from, length);

	memcpy(to, from, length);

	for (int i = 0; i < length; i++)
	{
		((unsigned char*)to)[i] = ((unsigned char*)from)[i];
	}
}

HackUtils::CompileResult HackUtils::assemble(std::string assembly, void* addressStart)
{
	CompileResult compileResult;
	
	CodeInfo ci(sizeof(void*) == 4 ? ArchInfo::kTypeX86 : ArchInfo::kTypeX64);
	CodeHolder code;
	code.init(ci);

	// Attach X86Assembler `code`.
	X86Assembler a(&code);

	// Create AsmParser that will emit to X86Assembler.
	AsmParser p(&a);

	// Parse the assembly.
	Error err = p.parse(assembly.c_str());

	// Error handling (use asmjit::ErrorHandler for more robust error handling).
	if (err)
	{
		compileResult.hasError = true;
		compileResult.errorData.lineNumber = 0;
		compileResult.errorData.message = DebugUtils::errorAsString(err);
		// printf("ERROR: %08x (%s)\n", err, DebugUtils::errorAsString(err));
		LogUtils::logError(DebugUtils::errorAsString(err));
		return compileResult;
	}

	// If we are done, you must detach the Assembler from CodeHolder or sync
	// it, so its internal state and position is synced with CodeHolder.
	code.sync();

	// Now you can print the code, which is stored in the first section (.text).
	CodeBuffer& buffer = code.getSectionEntry(0)->getBuffer();

	compileResult.byteCount = buffer.getLength();
	compileResult.compiledBytes = new unsigned char[buffer.getLength()]; // TODO: This is a memleak
	memcpy(compileResult.compiledBytes, buffer.getData(), buffer.getLength());
	compileResult.hasError = false;

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

		initialized = true;
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

HackUtils::DataType HackUtils::stdTypeToDataType(const std::type_info& dataTypeInfo)
{
	if (dataTypeInfo == typeid(unsigned char))
	{
		return HackUtils::DataType::Byte;
	}
	else if (dataTypeInfo == typeid(char))
	{
		return HackUtils::DataType::SByte;
	}
	else if (dataTypeInfo == typeid(short))
	{
		return HackUtils::DataType::Int16;
	}
	else if (dataTypeInfo == typeid(unsigned short))
	{
		return HackUtils::DataType::UInt16;
	}
	else if (dataTypeInfo == typeid(int))
	{
		return HackUtils::DataType::Int32;
	}
	else if (dataTypeInfo == typeid(unsigned int))
	{
		return HackUtils::DataType::UInt32;
	}
	else if (dataTypeInfo == typeid(long))
	{
		return HackUtils::DataType::Int64;
	}
	else if (dataTypeInfo == typeid(unsigned long))
	{
		return HackUtils::DataType::UInt64;
	}
	else if (dataTypeInfo == typeid(float))
	{
		return HackUtils::DataType::Single;
	}
	else if (dataTypeInfo == typeid(double))
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
		{
			return "Byte";
		}
		case HackUtils::DataType::SByte:
		{
			return "SByte";
		}
		case HackUtils::DataType::Int16:
		{
			return "Int16";
		}
		case HackUtils::DataType::UInt16:
		{
			return "UInt16";
		}
		case HackUtils::DataType::Int32:
		{
			return "Int32";
		}
		case HackUtils::DataType::UInt32:
		{
			return "UInt32";
		}
		case HackUtils::DataType::Int64:
		{
			return "Int64";
		}
		case HackUtils::DataType::UInt64:
		{
			return "UInt64";
		}
		case HackUtils::DataType::Single:
		{
			return "Single";
		}
		case HackUtils::DataType::Double:
		{
			return "Double";
		}
		default:
		{
			throw std::invalid_argument("Invalid data type");
		}
	}
}

std::string HackUtils::valueStringOf(void* dataPointer, HackUtils::DataType dataType)
{
	switch (dataType)
	{
		case HackUtils::DataType::Byte:
		{
			return std::to_string((*(unsigned char*)dataPointer));
		}
		case HackUtils::DataType::SByte:
		{
			return std::to_string((*(signed char*)dataPointer));
		}
		case HackUtils::DataType::Int16:
		{
			return std::to_string((*(short*)dataPointer));
		}
		case HackUtils::DataType::UInt16:
		{
			return std::to_string((*(unsigned short*)dataPointer));
		}
		case HackUtils::DataType::Int32:
		{
			return std::to_string((*(int*)dataPointer));
		}
		case HackUtils::DataType::UInt32:
		{
			return std::to_string((*(unsigned int*)dataPointer));
		}
		case HackUtils::DataType::Int64:
		{
			return std::to_string((*(long*)dataPointer));
		}
		case HackUtils::DataType::UInt64:
		{
			return std::to_string((*(unsigned long*)dataPointer));
		}
		case HackUtils::DataType::Single:
		{
			return std::to_string((*(float*)dataPointer));
		}
		case HackUtils::DataType::Double:
		{
			return std::to_string((*(double*)dataPointer));
		}
		default:
		{
			throw std::invalid_argument("Invalid data type");
		}
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
