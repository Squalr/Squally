#include "HackableCode.h"

HackableCode * HackableCode::create(std::string name, void* codeStart, int codeLength)
{
	HackableCode* hackableCode = new HackableCode(name, codeStart, codeLength);

	hackableCode->autorelease();

	return hackableCode;
}

HackableCode::HackableCode(std::string name, void* codeStart, int codeLength)
{
	this->functionName = name;
	this->codePointer = (byte*)codeStart;
	this->codeOriginalLength = codeLength;
	this->allocations = new std::map<void*, int>();

	this->originalCodeCopy = new byte(codeLength);
	memcpy(originalCodeCopy, codeStart, codeLength);

	this->assemblyString = HackUtils::disassemble(codeStart, codeLength);
}

void HackableCode::restoreOriginalCode()
{
	DWORD old;
	VirtualProtect(this->codePointer, this->codeOriginalLength, PAGE_EXECUTE_READWRITE, &old);
	memcpy(this->codePointer, this->originalCodeCopy, this->codeOriginalLength);
}

bool HackableCode::applyCustomCode()
{
	HackUtils::CompileResult compileResult = HackUtils::assemble(this->assemblyString, this->codePointer);

	// Sanity check that the code compiles -- there isn't any reason it shouldn't
	if (compileResult.hasError || compileResult.byteCount > this->codeOriginalLength)
	{
		// Fail the activation
		return false;
	}

	// Write new assembly code
	DWORD old;
	VirtualProtect(this->codePointer, compileResult.byteCount, PAGE_EXECUTE_READWRITE, &old);
	memcpy(this->codePointer, compileResult.compiledBytes, compileResult.byteCount);

	int unfilledBytes = this->codeOriginalLength - compileResult.byteCount;

	// Fill remaining bytes with NOPs
	for (int index = 0; index < unfilledBytes; index++)
	{
		const byte nop = 0x90;
		((byte*)this->codePointer)[compileResult.byteCount + index] = nop;
	}
}

void* HackableCode::allocateMemory(int allocationSize)
{
	void* allocation = malloc(allocationSize);
	this->allocations->insert_or_assign(allocation, allocationSize);

	return allocation;
}

HackableCode::~HackableCode()
{
	for (auto iterator = this->allocations->begin(); iterator != this->allocations->end(); iterator++)
	{
		delete(iterator->first);
	}

	delete(this->originalCodeCopy);
	delete(this->allocations);
}
