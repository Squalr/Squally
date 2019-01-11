#include "HackUtils.h"

#include <algorithm>
#include <bitset>
#include <iomanip>
#include <sstream>

#include "asmjit.h"
#include "udis86.h"

#include "Engine/asmtk/asmtk.h"
#include "Engine/Utils/LogUtils.h"

#include "Strings/Hacking/CodeEditor/Errors/AlreadyInitialized.h"
#include "Strings/Hacking/CodeEditor/Errors/AmbiguousOperandSize.h"
#include "Strings/Hacking/CodeEditor/Errors/CodeTooLarge.h"
#include "Strings/Hacking/CodeEditor/Errors/FeatureNotEnabled.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidAddress.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidAddressIndex.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidAddressScale.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidArchitecture.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidArgument.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidBroadcast.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidDisplacement.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidImmediateValue.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidInstruction.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidLabel.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidLabelName.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidLockPrefix.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidMask.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidOperandSize.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidOption.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidParentLabel.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidPrefixCombination.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidRegisterKind.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidRegisterPhysicalId.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidRegisterType.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidRegisterVirtualId.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidRelocationEntry.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidRepPrefix.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidRexPrefix.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidSegment.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidState.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidTypeInfo.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidUseDouble.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidUseOf8BitRegister.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidUseOf64BitAddress.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidUseOf64BitRegister.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidUseOf80BitFloat.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidUseSingle.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidXAquirePrefix.h"
#include "Strings/Hacking/CodeEditor/Errors/InvalidXReleasePrefix.h"
#include "Strings/Hacking/CodeEditor/Errors/LabelAlreadyBound.h"
#include "Strings/Hacking/CodeEditor/Errors/LabelAlreadyDefined.h"
#include "Strings/Hacking/CodeEditor/Errors/LabelIndexOverflow.h"
#include "Strings/Hacking/CodeEditor/Errors/LabelNameTooLong.h"
#include "Strings/Hacking/CodeEditor/Errors/NoCodeGenerated.h"
#include "Strings/Hacking/CodeEditor/Errors/NoHeapMemory.h"
#include "Strings/Hacking/CodeEditor/Errors/NonLocalLabelCantHaveParent.h"
#include "Strings/Hacking/CodeEditor/Errors/NoPhysicalRegisters.h"
#include "Strings/Hacking/CodeEditor/Errors/NotConsecutiveRegisters.h"
#include "Strings/Hacking/CodeEditor/Errors/NotInitialized.h"
#include "Strings/Hacking/CodeEditor/Errors/NoVirtualMemory.h"
#include "Strings/Hacking/CodeEditor/Errors/Ok.h"
#include "Strings/Hacking/CodeEditor/Errors/OperandSizeMismatch.h"
#include "Strings/Hacking/CodeEditor/Errors/OverlappedRegisters.h"
#include "Strings/Hacking/CodeEditor/Errors/OverlappingRegisterAndArgsRegister.h"
#include "Strings/Hacking/CodeEditor/Errors/RelocationIndexOverflow.h"
#include "Strings/Hacking/CodeEditor/Errors/SlotOccupied.h"
#include "Strings/Hacking/CodeEditor/Errors/UnknownError.h"

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

		switch ((CompileResult::ErrorId) err)
		{
			case CompileResult::ErrorId::Ok:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_Ok::create();
				break;
			}
			case CompileResult::ErrorId::NoHeapMemory:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_NoHeapMemory::create();
				break;
			}
			case CompileResult::ErrorId::NoVirtualMemory:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_NoVirtualMemory::create();
				break;
			}
			case CompileResult::ErrorId::InvalidArgument:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidArgument::create();
				break;
			}
			case CompileResult::ErrorId::InvalidState:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidState::create();
				break;
			}
			case CompileResult::ErrorId::InvalidArchitecture:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidArchitecture::create();
				break;
			}
			case CompileResult::ErrorId::NotInitialized:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_NotInitialized::create();
				break;
			}
			case CompileResult::ErrorId::AlreadyInitialized:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_AlreadyInitialized::create();
				break;
			}
			case CompileResult::ErrorId::FeatureNotEnabled:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_FeatureNotEnabled::create();
				break;
			}
			case CompileResult::ErrorId::SlotOccupied:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_SlotOccupied::create();
				break;
			}
			case CompileResult::ErrorId::NoCodeGenerated:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_NoCodeGenerated::create();
				break;
			}
			case CompileResult::ErrorId::CodeTooLarge:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_CodeTooLarge::create();
				break;
			}
			case CompileResult::ErrorId::InvalidLabel:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidLabel::create();
				break;
			}
			case CompileResult::ErrorId::LabelIndexOverflow:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_LabelIndexOverflow::create();
				break;
			}
			case CompileResult::ErrorId::LabelAlreadyBound:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_LabelAlreadyBound::create();
				break;
			}
			case CompileResult::ErrorId::LabelAlreadyDefined:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_LabelAlreadyDefined::create();
				break;
			}
			case CompileResult::ErrorId::LabelNameTooLong:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_LabelNameTooLong::create();
				break;
			}
			case CompileResult::ErrorId::InvalidLabelName:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidLabelName::create();
				break;
			}
			case CompileResult::ErrorId::InvalidParentLabel:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidParentLabel::create();
				break;
			}
			case CompileResult::ErrorId::NonLocalLabelCantHaveParent:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_NonLocalLabelCantHaveParent::create();
				break;
			}
			case CompileResult::ErrorId::RelocationIndexOverflow:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_RelocationIndexOverflow::create();
				break;
			}
			case CompileResult::ErrorId::InvalidRelocationEntry:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidRelocationEntry::create();
				break;
			}
			case CompileResult::ErrorId::InvalidInstruction:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidInstruction::create();
				break;
			}
			case CompileResult::ErrorId::InvalidRegisterType:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidRegisterType::create();
				break;
			}
			case CompileResult::ErrorId::InvalidRegisterKind:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidRegisterKind::create();
				break;
			}
			case CompileResult::ErrorId::InvalidRegisterPhysicalId:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidRegisterPhysicalId::create();
				break;
			}
			case CompileResult::ErrorId::InvalidRegisterVirtualId:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidRegisterVirtualId::create();
				break;
			}
			case CompileResult::ErrorId::InvalidPrefixCombination:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidPrefixCombination::create();
				break;
			}
			case CompileResult::ErrorId::InvalidLockPrefix:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidLockPrefix::create();
				break;
			}
			case CompileResult::ErrorId::InvalidXAcquirePrefix:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidXAquirePrefix::create();
				break;
			}
			case CompileResult::ErrorId::InvalidXReleasePrefix:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidXReleasePrefix::create();
				break;
			}
			case CompileResult::ErrorId::InvalidRepPrefix:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidRepPrefix::create();
				break;
			}
			case CompileResult::ErrorId::InvalidRexPrefix:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidRexPrefix::create();
				break;
			}
			case CompileResult::ErrorId::InvalidMask:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidMask::create();
				break;
			}
			case CompileResult::ErrorId::InvalidUseSingle:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidUseSingle::create();
				break;
			}
			case CompileResult::ErrorId::InvalidUseDouble:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidUseDouble::create();
				break;
			}
			case CompileResult::ErrorId::InvalidBroadcast:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidBroadcast::create();
				break;
			}
			case CompileResult::ErrorId::InvalidOption:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidOption::create();
				break;
			}
			case CompileResult::ErrorId::InvalidAddress:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidAddress::create();
				break;
			}
			case CompileResult::ErrorId::InvalidAddressIndex:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidAddressIndex::create();
				break;
			}
			case CompileResult::ErrorId::InvalidAddressScale:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidAddressScale::create();
				break;
			}
			case CompileResult::ErrorId::InvalidUseOf64BitAddress:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidUseOf64BitAddress::create();
				break;
			}
			case CompileResult::ErrorId::InvalidDisplacement:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidDisplacement::create();
				break;
			}
			case CompileResult::ErrorId::InvalidSegment:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidSegment::create();
				break;
			}
			case CompileResult::ErrorId::InvalidImmediateValue:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidImmediateValue::create();
				break;
			}
			case CompileResult::ErrorId::InvalidOperandSize:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidOperandSize::create();
				break;
			}
			case CompileResult::ErrorId::AmbiguousOperandSize:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_AmbiguousOperandSize::create();
				break;
			}
			case CompileResult::ErrorId::OperandSizeMismatch:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_OperandSizeMismatch::create();
				break;
			}
			case CompileResult::ErrorId::InvalidTypeInfo:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidTypeInfo::create();
				break;
			}
			case CompileResult::ErrorId::InvalidUseOf8BitRegister:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidUseOf8BitRegister::create();
				break;
			}
			case CompileResult::ErrorId::InvalidUseOf64BitRegister:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidUseOf64BitRegister::create();
				break;
			}
			case CompileResult::ErrorId::InvalidUseOf80BitFloat:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_InvalidUseOf80BitFloat::create();
				break;
			}
			case CompileResult::ErrorId::NotConsecutiveRegisters:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_NotConsecutiveRegisters::create();
				break;
			}
			case CompileResult::ErrorId::NoPhysicalRegisters:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_NoPhysicalRegisters::create();
				break;
			}
			case CompileResult::ErrorId::OverlappedRegisters:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_OverlappedRegisters::create();
				break;
			}
			case CompileResult::ErrorId::OverlappingRegisterAndArgsRegister:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_OverlappingRegisterAndArgsRegister::create();
				break;
			}
			case CompileResult::ErrorId::UnknownError:
			default:
			{
				compileResult.errorData.message = Strings::Hacking_CodeEditor_Errors_UnknownError::create();
				break;
			}
		}

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
