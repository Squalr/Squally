#include "HackableCode.h"

#include "Engine/Utils/HackUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Resources/UIResources.h"

// Note: all tags are assumed to start with a different byte and have the same length
const unsigned char HackableCode::StartTagSignature[] = { 0x57, 0x6A, 0x45, 0xBF, 0xDE, 0xC0, 0xED, 0xFE, 0x5F, 0x5F };
const unsigned char HackableCode::EndTagSignature[] = { 0x56, 0x6A, 0x45, 0xBE, 0xDE, 0xC0, 0xAD, 0xDE, 0x5E, 0x5E };
const unsigned char HackableCode::StopSearchTagSignature[] = { 0x55, 0x6A, 0x45, 0xBD, 0x5E, 0xEA, 0x5E, 0xD1, 0x5D, 0x5D };

std::vector<HackableCode*> HackableCode::create(void* functionStart)
{
	std::vector<HackableCode*> extractedHackableCode = std::vector<HackableCode*>();

	const int tagSize = sizeof(HackableCode::StartTagSignature) / sizeof((HackableCode::StartTagSignature)[0]);
	const int readSizeFailSafe = 4096;

	unsigned char* currentBase = (unsigned char*)functionStart;
	unsigned char* currentSeek = (unsigned char*)functionStart;
	const unsigned char* targetArray = nullptr;
	void* nextHackableCodeStart = nullptr;

	while (true)
	{
		int signatureIndex = (int)((unsigned long)currentSeek - (unsigned long)currentBase);

		if (signatureIndex > readSizeFailSafe)
		{
			LogUtils::logError("Potentially fatal error: unable to find end signature in hackable code!");
			break;
		}

		if (targetArray == nullptr)
		{
			if (*currentSeek == HackableCode::StartTagSignature[0])
			{
				targetArray = HackableCode::StartTagSignature;
			}
			else if (*currentSeek == HackableCode::EndTagSignature[0])
			{
				targetArray = HackableCode::EndTagSignature;
			}
			else if (*currentSeek == HackableCode::StopSearchTagSignature[0])
			{
				targetArray = HackableCode::StopSearchTagSignature;
			}
			else
			{
				// Next byte does not match the start of any signature
				currentBase++;
				currentSeek = currentBase;
				continue;
			}

			currentSeek++;
			continue;
		}

		// Check if we match the next expected character
		if (*currentSeek == targetArray[signatureIndex])
		{
			currentSeek++;

			if (signatureIndex == tagSize - 1)
			{
				if (targetArray == HackableCode::StartTagSignature)
				{
					nextHackableCodeStart = (void*)currentSeek;
				}
				else if (targetArray == HackableCode::EndTagSignature)
				{
					void* nextHackableCodeEnd = (void*)currentBase;

					HackableCode* hackableCode = HackableCode::create("", nextHackableCodeStart, (int)((unsigned long)nextHackableCodeEnd - (unsigned long)nextHackableCodeStart), UIResources::Menus_Icons_CrossHair);

					extractedHackableCode.push_back(hackableCode);
				}
				else if (targetArray == HackableCode::StopSearchTagSignature)
				{
					break;
				}

				// Reset search state
				targetArray = nullptr;
				currentBase++;
				currentSeek = currentBase;
			}
		}
		else
		{
			// Match chain broken: Start again
			targetArray = nullptr;
			currentBase++;
			currentSeek = currentBase;
		}
	}

	return extractedHackableCode;
}

HackableCode* HackableCode::create(std::string name, void* codeStart, int codeLength, std::string iconResource)
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

	#ifdef _WIN32
		DWORD old;
		VirtualProtect(codeStart, codeLength, PAGE_EXECUTE_READWRITE, &old);
	#else
		mprotect(codeStart, codeLength, PROT_READ | PROT_WRITE | PROT_EXEC);
	#endif

	if (codeStart != nullptr && codeLength > 0)
	{
		this->originalCodeCopy = new unsigned char[codeLength];
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
