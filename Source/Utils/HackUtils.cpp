#include "HackUtils.h"

Fasm::FasmResult* HackUtils::assemble(std::string assembly, void* addressStart)
{
	return Fasm::assemble(assembly, addressStart);
}

std::string HackUtils::disassemble(void* bytes, int length)
{
	static ud_t ud_obj;
	static bool initialized = false;

	// Only initialize the disassembler once
	if (!initialized)
	{
		ud_init(&ud_obj);
		ud_set_mode(&ud_obj, sizeof(void*) * 8);
		ud_set_syntax(&ud_obj, UD_SYN_INTEL);
	}

	ud_set_input_buffer(&ud_obj, (byte*)bytes, length);

	std::string instructions = "";

	while (ud_disassemble(&ud_obj))
	{
		instructions += ud_insn_asm(&ud_obj);
		instructions += "\r\n";
	}

	return instructions;
}

std::string HackUtils::hexAddressOf(void* address, bool zeroPad, bool prefix)
{
	std::stringstream stream;

	// Convert to hex
	stream << std::hex << (int)(address);
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
		return std::to_string((*(byte*)dataPointer));
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
		stream << std::hex << (int)(((byte*)dataPointer)[index]);
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
