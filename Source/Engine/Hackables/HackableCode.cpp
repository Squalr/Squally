#include "HackableCode.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Utils/HackUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

std::map<void*, std::vector<HackableCode*>> HackableCode::HackableCodeCache = std::map<void*, std::vector<HackableCode*>>();

// Note: all tags are assumed to start with a different byte and have the same length
const int HackableCode::StartTagFuncIdIndex = 2;
const unsigned char HackableCode::StartTagSignature[] = { 0x57, 0x6A, 0x00, 0xBF, 0xDE, 0xC0, 0xED, 0xFE, 0x5F, 0x5F };
const unsigned char HackableCode::EndTagSignature[] = { 0x56, 0x6A, 0x45, 0xBE, 0xDE, 0xC0, 0xAD, 0xDE, 0x5E, 0x5E };
const unsigned char HackableCode::StopSearchTagSignature[] = { 0x52, 0x6A, 0x45, 0xBA, 0x5E, 0xEA, 0x15, 0x0D, 0x5A, 0x5A };

std::vector<HackableCode*> HackableCode::create(void* functionStart, std::map<unsigned char, LateBindData>& lateBindDataMap)
{
	functionStart = HackUtils::resolveVTableAddress(functionStart);

	if (HackableCode::HackableCodeCache.find(functionStart) != HackableCode::HackableCodeCache.end())
	{
		std::vector<HackableCode*> clonedHackables = std::vector<HackableCode*>();

		for (auto it = HackableCode::HackableCodeCache[functionStart].begin(); it != HackableCode::HackableCodeCache[functionStart].end(); it++)
		{
			clonedHackables.push_back((*it)->clone());
		}

		return clonedHackables;
	}

	std::vector<HackableCode*> extractedHackableCode = std::vector<HackableCode*>();

	const int tagSize = sizeof(HackableCode::StartTagSignature) / sizeof((HackableCode::StartTagSignature)[0]);
	const int stopSearchingAfterXBytesFailSafe = 4096;

	unsigned char* currentBase = (unsigned char*)functionStart;
	unsigned char* currentSeek = (unsigned char*)functionStart;
	unsigned char funcId = 0;
	const unsigned char* targetArray = nullptr;
	void* nextHackableCodeStart = nullptr;

	while (true)
	{
		int signatureIndex = (int)((unsigned long)currentSeek - (unsigned long)currentBase);

		if (signatureIndex > stopSearchingAfterXBytesFailSafe)
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

		// Special case in the start tag where we embed a local identifier for the function, which we need to pull out
		if (targetArray == HackableCode::StartTagSignature && signatureIndex == HackableCode::StartTagFuncIdIndex)
		{
			funcId = *currentSeek;
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
					if (nextHackableCodeStart != nullptr)
					{
						void* nextHackableCodeEnd = (void*)currentBase;

						// Fetch the late-bind data for this function from the map
						if (lateBindDataMap.find(funcId) != lateBindDataMap.end())
						{
							LateBindData lateBindData = lateBindDataMap[funcId];
							HackableCode* hackableCode = HackableCode::create(nextHackableCodeStart, nextHackableCodeEnd, lateBindData);
							HackableCode* hackableClone = hackableCode->clone();

							hackableClone->retain();

							extractedHackableCode.push_back(hackableClone);
						}
						else
						{
							LogUtils::logError("Could not find late-bind data for an extracted function!");
						}

						nextHackableCodeStart = nullptr;
					}
				}
				else if (targetArray == HackableCode::StopSearchTagSignature)
				{
					break;
				}
			}
			else
			{
				// Keep searching this signature
				continue;
			}
		}

		// Reset search state
		targetArray = nullptr;
		currentBase++;
		currentSeek = currentBase;
	}

	HackableCode::HackableCodeCache[functionStart] = extractedHackableCode;

	return extractedHackableCode;
}

HackableCode* HackableCode::create(void* codeStart, void* codeEnd, LateBindData lateBindData)
{
	HackableCode* hackableCode = new HackableCode(codeStart, codeEnd, lateBindData);

	hackableCode->autorelease();

	return hackableCode;
}

HackableCode::HackableCode(void* codeStart, void* codeEnd, LateBindData lateBindData) : HackableAttribute(lateBindData.hackFlags, lateBindData.duration, lateBindData.iconResource, lateBindData.functionName, lateBindData.hackablePreview, lateBindData.clippy)
{
	this->hackableCodeIdentifier = lateBindData.hackableObjectIdentifier + "_" + lateBindData.functionName->getStringIdentifier();
	this->codePointer = (unsigned char*)codeStart;
	this->codeEndPointer = (unsigned char*)codeEnd;
	this->lateBindData = lateBindData;
	this->originalCodeLength = (int)((unsigned long)codeEnd - (unsigned long)codeStart);
	this->originalCodeCopy = std::vector<unsigned char>();
	this->registerHints = lateBindData.registerHints;

	for (auto it = this->registerHints.begin(); it != this->registerHints.end(); it++)
	{
		if ((*it).second != nullptr)
		{
			this->addChild((*it).second);
		}
	}

	if (codeStart != nullptr)
	{
		for (int index = 0; index < this->originalCodeLength; index++)
		{
			this->originalCodeCopy.push_back(((unsigned char*)codeStart)[index]);
		}
	}

	// Disassemble starting bytes, strip out NOPs
	if (!lateBindData.asmOverride.empty())
	{
		this->originalAssemblyString = lateBindData.asmOverride;
	}
	else
	{
		this->originalAssemblyString = StrUtils::replaceAll(HackUtils::disassemble(codeStart, this->originalCodeLength), "nop\n", "");
	}
	
	this->assemblyString = this->originalAssemblyString;
}

HackableCode::~HackableCode()
{
}

HackableCode* HackableCode::clone()
{
	LateBindData clonedData = this->lateBindData;
	std::map<Register, LocalizedString*> registerHintsClone = std::map<Register, LocalizedString*>();

	clonedData.functionName = this->lateBindData.functionName->clone();

	for (auto it = this->lateBindData.registerHints.begin(); it != this->lateBindData.registerHints.end(); it++)
	{
		registerHintsClone[it->first] = it->second == nullptr ? nullptr : it->second->clone();
	}

	clonedData.registerHints = registerHintsClone;

	return HackableCode::create(this->codePointer, this->codeEndPointer, clonedData);
}

std::string HackableCode::getHackableCodeIdentifier()
{
	return this->hackableCodeIdentifier;
}

std::string HackableCode::getAssemblyString()
{
	return this->assemblyString;
}

std::string HackableCode::getOriginalAssemblyString()
{
	return this->originalAssemblyString;
}

void* HackableCode::getPointer()
{
	return this->codePointer;
}

int HackableCode::getOriginalLength()
{
	return this->originalCodeLength;
}

bool HackableCode::applyCustomCode(std::string newAssembly)
{
	this->assemblyString = newAssembly;

	if (this->codePointer == nullptr)
	{
		return false;
	}

	HackUtils::CompileResult compileResult = HackUtils::assemble(this->assemblyString, this->codePointer);

	// Sanity check that the code compiles -- there isn't any reason it shouldn't
	if (compileResult.hasError || compileResult.byteCount > this->originalCodeLength)
	{
		// Fail the activation
		return false;
	}

	int unfilledBytes = this->originalCodeLength - compileResult.byteCount;

	// Fill remaining bytes with NOPs
	for (int index = 0; index < unfilledBytes; index++)
	{
		const unsigned char nop = 0x90;
		compileResult.compiledBytes.push_back(nop);
	}

	HackUtils::writeMemory(this->codePointer, compileResult.compiledBytes.data(), compileResult.compiledBytes.size());

	HackableEvents::TriggerOnHackApplied(HackableEvents::HackAppliedArgs(this));
	this->resetTimer();

	return true;
}

void HackableCode::restoreState()
{
	if (this->codePointer == nullptr)
	{
		return;
	}

	HackUtils::writeMemory(this->codePointer, this->originalCodeCopy.data(), this->originalCodeCopy.size());
}
