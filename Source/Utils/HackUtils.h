#pragma once
#include <bitset>
#include "cocos2d.h"
#include "udis86.h"
#include "fasm.h"

using namespace cocos2d;

class HackUtils
{
public:
	enum DataType
	{
		Byte,
		SByte,
		Int16,
		UInt16,
		Int32,
		UInt32,
		Int64,
		UInt64,
		Single,
		Double,
	};

	struct CompileResult
	{
		struct ErrorData
		{
			int lineNumber;
			std::string message;
		};

		ErrorData errorData;
		bool hasError;

		unsigned char* compiledBytes;
		int byteCount;
	};

	static HackUtils::CompileResult assemble(std::string assembly, void* addressStart);
	static std::string disassemble(void* bytes, int length);
	static std::string hexAddressOf(void* address, bool zeroPad, bool prefix);
	static std::string toHex(int value);
	static std::string toBinary4(int value);
	static DataType stdTypeToDataType(const std::type_info* typeInfo);
	static std::string dataTypeToString(DataType dataType);
	static std::string valueStringOf(void* dataPointer, DataType dataType);
	static std::string arrayOfByteStringOf(void* dataPointer, int length, int maxLength);

private:
	static CompileResult constructCompileResult(Fasm::FasmResult* fasmResult);
};

