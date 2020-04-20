#include "HackableCode.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/GlobalHackAttributeContainer.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Utils/HackUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/StrUtils.h"

#include "Strings/Strings.h"

using namespace cocos2d;

HackableCode::CodeMap HackableCode::HackableCodeCache = HackableCode::CodeMap();

// Note: all tags are assumed to start with a different byte and have the same length
const int HackableCode::StartTagFuncIdIndex = 2;
const unsigned char HackableCode::StartTagSignature[] = { 0x57, 0x6A, 0x00, 0xBF, 0xDE, 0xC0, 0xED, 0xFE, 0x5F, 0x5F };
const unsigned char HackableCode::EndTagSignature[] = { 0x56, 0x6A, 0x45, 0xBE, 0xDE, 0xC0, 0xAD, 0xDE, 0x5E, 0x5E };
const unsigned char HackableCode::StopSearchTagSignature[] = { 0x52, 0x6A, 0x45, 0xBA, 0x5E, 0xEA, 0x15, 0x0D, 0x5A, 0x5A };
std::map<std::string, std::vector<unsigned char>> HackableCode::OriginalCodeCache = std::map<std::string, std::vector<unsigned char>>();

std::vector<HackableCode*> HackableCode::create(void* functionStart, CodeInfoMap& hackableCodeInfoMap)
{
	return HackableCode::parseHackables(functionStart, hackableCodeInfoMap);
}

HackableCode* HackableCode::create(void* codeStart, void* codeEnd, HackableCodeInfo hackableCodeInfo)
{
	HackableCode* hackableCode = GlobalHackAttributeContainer::GetHackableCode(codeStart);

	if (hackableCode == nullptr)
	{
		hackableCode = new HackableCode(codeStart, codeEnd, hackableCodeInfo);
		hackableCode->autorelease();

		GlobalHackAttributeContainer::RegisterHackableCode(hackableCode);
	}

	return hackableCode;
}

HackableCode::HackableCode(void* codeStart, void* codeEnd, HackableCodeInfo hackableCodeInfo)
	: HackableBase(
		hackableCodeInfo.hackableIdentifier + "_" + (hackableCodeInfo.functionName == nullptr ? "" : hackableCodeInfo.functionName->getStringIdentifier()),
		hackableCodeInfo.hackFlags,
		hackableCodeInfo.duration,
		hackableCodeInfo.cooldown,
		hackableCodeInfo.hackBarColor,
		hackableCodeInfo.iconResource,
		hackableCodeInfo.functionName,
		hackableCodeInfo.hackablePreview,
		hackableCodeInfo.clippy)
{
	this->codePointer = (unsigned char*)codeStart;
	this->codeEndPointer = (unsigned char*)codeEnd;
	this->hackableCodeInfo = hackableCodeInfo;
	this->originalCodeLength = (int)((unsigned long)codeEnd - (unsigned long)codeStart);
	this->originalCodeCopy = std::vector<unsigned char>();
	this->registerHints = hackableCodeInfo.registerHints;

	for (auto next : this->registerHints)
	{
		if (next.second != nullptr)
		{
			this->addChild(next.second);
		}
	}

	if (codeStart != nullptr)
	{
		if (HackableCode::OriginalCodeCache.find(hackableCodeInfo.hackableIdentifier) == HackableCode::OriginalCodeCache.end())
		{
			HackableCode::OriginalCodeCache[hackableCodeInfo.hackableIdentifier] = std::vector<unsigned char>();

			for (int index = 0; index < this->originalCodeLength; index++)
			{
				HackableCode::OriginalCodeCache[hackableCodeInfo.hackableIdentifier].push_back(((unsigned char*)codeStart)[index]);
			}
		}

		this->originalCodeCopy = HackableCode::OriginalCodeCache[hackableCodeInfo.hackableIdentifier];
	}

	this->readOnlyScripts = std::vector<ReadOnlyScript>();

	if (!hackableCodeInfo.excludeDefaultScript)
	{
		std::string script = StrUtils::replaceAll(HackUtils::disassemble(codeStart, this->originalCodeLength), "nop\n", "");

		this->readOnlyScripts.push_back(ReadOnlyScript(
			Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
			script,
			script
		));
	}

	for (auto script : hackableCodeInfo.readOnlyScripts)
	{
		this->readOnlyScripts.push_back(script);
	}

	if (!this->readOnlyScripts.empty())
	{
		this->originalAssemblyString = (sizeof(void*) == 4) ? this->readOnlyScripts.front().scriptx86 : this->readOnlyScripts.front().scriptx64;
	}
	
	this->assemblyString = this->originalAssemblyString;

	for (auto script : this->readOnlyScripts)
	{
		if (script.title != nullptr)
		{
			this->addChild(script.title);
		}
	}
}

HackableCode::~HackableCode()
{
}

HackableCode* HackableCode::clone(CodeInfoMap& hackableCodeInfoMap)
{
	HackableCodeInfo clonedData = this->hackableCodeInfo;
	std::map<Register, LocalizedString*> registerHintsClone = std::map<Register, LocalizedString*>();

	clonedData.functionName = this->hackableCodeInfo.functionName->clone();

	for (auto next : this->hackableCodeInfo.registerHints)
	{
		registerHintsClone[next.first] = next.second == nullptr ? nullptr : next.second->clone();
	}

	clonedData.registerHints = registerHintsClone;

	return HackableCode::create(this->codePointer, this->codeEndPointer, clonedData);
}

std::vector<HackableCode::ReadOnlyScript> HackableCode::getReadOnlyScripts()
{
	return this->readOnlyScripts;
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
	super::restoreState();
	
	if (this->codePointer == nullptr)
	{
		return;
	}

	HackUtils::writeMemory(this->codePointer, this->originalCodeCopy.data(), this->originalCodeCopy.size());
}

std::vector<HackableCode*> HackableCode::parseHackables(void* functionStart, CodeInfoMap& hackableCodeInfoMap)
{
	// Parse the HACKABLE_CODE_BEGIN/END pairs from the function. There may be multiple.
	MarkerMap markerMap = HackableCode::parseHackableMarkers(functionStart, hackableCodeInfoMap);
	
	std::vector<HackableCode*> extractedHackableCode = std::vector<HackableCode*>();

	// Bind the code info to each of the BEGIN/END markers to create a HackableCode object.
	for (auto marker : markerMap)
	{
		unsigned char funcId = marker.first;
		HackableCodeMarkers markers = marker.second;

		// Fetch the late-bind data for this function from the map
		if (hackableCodeInfoMap.find(funcId) != hackableCodeInfoMap.end())
		{
			extractedHackableCode.push_back(HackableCode::create(markers.start, markers.end, hackableCodeInfoMap[funcId]));
		}
		else
		{
			LogUtils::logError("Could not find code info data for an extracted function!");
		}
	}

	return extractedHackableCode;
}

HackableCode::MarkerMap& HackableCode::parseHackableMarkers(void* functionStart, CodeInfoMap& hackableCodeInfoMap)
{
	if (HackableCode::HackableCodeCache.find(functionStart) != HackableCode::HackableCodeCache.end())
	{
		return HackableCode::HackableCodeCache[functionStart];
	}

	void* resolvedFunctionStart = HackUtils::resolveVTableAddress(functionStart);
	MarkerMap extractedMarkers = MarkerMap();

	const int tagSize = sizeof(HackableCode::StartTagSignature) / sizeof((HackableCode::StartTagSignature)[0]);
	const int stopSearchingAfterXBytesFailSafe = 4096;

	unsigned char* currentBase = (unsigned char*)resolvedFunctionStart;
	unsigned char* currentSeek = (unsigned char*)resolvedFunctionStart;
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

						extractedMarkers[funcId] = HackableCodeMarkers(nextHackableCodeStart, nextHackableCodeEnd);

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

	HackableCode::HackableCodeCache[functionStart] = extractedMarkers;

	return HackableCode::HackableCodeCache[functionStart];
}
