#include "HackableCode.h"

#include "Engine/Utils/HackUtils.h"

HackableCode * HackableCode::create(std::string name, void* codeStart, int codeLength, std::string iconResource)
{
	HackableCode* hackableCode = new HackableCode(name, codeStart, codeLength, iconResource);

	hackableCode->autorelease();

	return hackableCode;
}

HackableCode::HackableCode(std::string name, void* codeStart, int codeLength, std::string iconResource) : HackableAttribute(iconResource)
{
	this->functionName = name;
	this->codePointer = (unsigned char*)codeStart;
	this->codeOriginalLength = codeLength;
	this->allocations = std::map<void*, int>();

	if (codeStart != nullptr && codeLength > 0)
	{
		this->originalCodeCopy = new unsigned char(codeLength);
		memcpy(originalCodeCopy, codeStart, codeLength);
	}
	else
	{
		this->originalCodeCopy = nullptr;
	}

	this->assemblyString = HackUtils::disassemble(codeStart, codeLength);
}

void HackableCode::restoreOriginalCode()
{
	if (this->codePointer == nullptr || this->originalCodeCopy == nullptr)
	{
		return;
	}

	#ifdef _WIN32
		DWORD old;
		VirtualProtect(this->codePointer, this->codeOriginalLength, PAGE_EXECUTE_READWRITE, &old);
	#else
		mprotect(this->codePointer, this->codeOriginalLength, PROT_READ | PROT_WRITE | PROT_EXEC);
	#endif
	
	memcpy(this->codePointer, this->originalCodeCopy, this->codeOriginalLength);
}

bool HackableCode::applyCustomCode()
{
	if (this->codePointer == nullptr)
	{
		return false;
	}

	HackUtils::CompileResult compileResult = HackUtils::assemble(this->assemblyString, this->codePointer);

	// Sanity check that the code compiles -- there isn't any reason it shouldn't
	if (compileResult.hasError || compileResult.byteCount > this->codeOriginalLength)
	{
		// Fail the activation
		return false;
	}

	// Write new assembly code
	#ifdef _WIN32
		DWORD old;
		VirtualProtect(this->codePointer, compileResult.byteCount, PAGE_EXECUTE_READWRITE, &old);
	#else
		mprotect(this->codePointer, compileResult.byteCount, PROT_READ | PROT_WRITE | PROT_EXEC);
	#endif

	memcpy(this->codePointer, compileResult.compiledBytes, compileResult.byteCount);

	int unfilledBytes = this->codeOriginalLength - compileResult.byteCount;

	// Fill remaining bytes with NOPs
	for (int index = 0; index < unfilledBytes; index++)
	{
		const unsigned char nop = 0x90;
		((unsigned char*)this->codePointer)[compileResult.byteCount + index] = nop;
	}

	return true;
}

void* HackableCode::allocateMemory(int allocationSize)
{
	void* allocation = malloc(allocationSize);
	this->allocations[allocation] = allocationSize;

	return allocation;
}

HackableCode::~HackableCode()
{
	for (auto iterator = this->allocations.begin(); iterator != this->allocations.end(); iterator++)
	{
		delete(iterator->first);
	}

	delete(this->originalCodeCopy);
}
