#pragma once
#include <string>
#include <vector>

class LocalizedString;

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
		enum class ErrorId
		{
			Ok = 0,
			NoHeapMemory = 1,
			NoVirtualMemory = 2,
			InvalidArgument = 3,
			InvalidState = 4,
			InvalidArchitecture = 5,
			NotInitialized = 6,
			AlreadyInitialized = 7,
			FeatureNotEnabled = 8,
			SlotOccupied = 9,
			NoCodeGenerated = 10,
			CodeTooLarge = 11,
			InvalidLabel = 12,
			LabelIndexOverflow = 13,
			LabelAlreadyBound = 14,
			LabelAlreadyDefined = 15,
			LabelNameTooLong = 16,
			InvalidLabelName = 17,
			InvalidParentLabel = 18,
			NonLocalLabelCantHaveParent = 19,
			RelocationIndexOverflow = 20,
			InvalidRelocationEntry = 21,
			InvalidInstruction = 22,
			InvalidRegisterType = 23,
			InvalidRegisterKind = 24,
			InvalidRegisterPhysicalId = 25,
			InvalidRegisterVirtualId = 26,
			InvalidPrefixCombination = 27,
			InvalidLockPrefix = 28,
			InvalidXAcquirePrefix = 29,
			InvalidXReleasePrefix = 30,
			InvalidRepPrefix = 31,
			InvalidRexPrefix = 32,
			InvalidMask = 33,
			InvalidUseSingle = 34,
			InvalidUseDouble = 35,
			InvalidBroadcast = 36,
			InvalidOption = 37,
			InvalidAddress = 38,
			InvalidAddressIndex = 39,
			InvalidAddressScale = 40,
			InvalidUseOf64BitAddress = 41,
			InvalidDisplacement = 42,
			InvalidSegment = 43,
			InvalidImmediateValue = 44,
			InvalidOperandSize = 45,
			AmbiguousOperandSize = 46,
			OperandSizeMismatch = 47,
			InvalidTypeInfo = 48,
			InvalidUseOf8BitRegister = 49,
			InvalidUseOf64BitRegister = 50,
			InvalidUseOf80BitFloat = 51,
			NotConsecutiveRegisters = 52,
			NoPhysicalRegisters = 53,
			OverlappedRegisters = 54,
			OverlappingRegisterAndArgsRegister = 55,
			UnknownError = 56,
		};

		struct ErrorData
		{
			int lineNumber;
			LocalizedString* message;
		};

		ErrorData errorData;
		bool hasError;
		std::vector<unsigned char> compiledBytes;
		int byteCount;
	};

	static void setAllMemoryPermissions(void* address, int length);
	static void writeMemory(void* to, void* from, int length);
	static HackUtils::CompileResult assemble(std::string assembly, void* addressStart);
	static void* resolveVTableAddress(void* address);
	static std::string disassemble(void* address, int length);
	static std::string hexAddressOf(void* address, bool zeroPad, bool prefix);
	static std::string toHex(int value);
	static std::string toBinary4(int value);
	static void* hexToPointer(std::string hexString, void* fallback = nullptr);
	static DataType stdTypeToDataType(const std::type_info& dataTypeInfo);
	static std::string dataTypeToString(DataType dataType);
	static std::string valueStringOf(void* dataPointer, DataType dataType);
	static std::string arrayOfByteStringOf(void* dataPointer, int length, int maxLength);
};

