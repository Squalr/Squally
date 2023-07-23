#include "HackableCode.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/GlobalHackAttributeContainer.h"
#include "Engine/Localization/ConstantString.h"
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
	HackableCode* instance = GlobalHackAttributeContainer::GetHackableCode(codeStart);

	if (instance == nullptr)
	{
		instance = new HackableCode(codeStart, codeEnd, hackableCodeInfo);
		instance->autorelease();

		GlobalHackAttributeContainer::RegisterHackableCode(instance);
	}

	return instance;
}

HackableCode::HackableCode(void* codeStart, void* codeEnd, HackableCodeInfo hackableCodeInfo)
	: HackableBase(
		hackableCodeInfo.hackableIdentifier,
		hackableCodeInfo.hackFlags,
		hackableCodeInfo.duration,
		hackableCodeInfo.cooldown,
		hackableCodeInfo.hackBarColor,
		hackableCodeInfo.iconResource,
		hackableCodeInfo.functionName,
		hackableCodeInfo.hackablePreview)
{
	this->codePointer = (unsigned char*)codeStart;
	this->codeEndPointer = (unsigned char*)codeEnd;
	this->hackableCodeInfo = hackableCodeInfo;
	this->originalCodeLength = (int)((unsigned long)codeEnd - (unsigned long)codeStart);
	this->registerHints = hackableCodeInfo.registerHints;

	for (const RegisterHintInfo& registerHint : this->registerHints)
	{
		this->addChild(registerHint.hint);
	}

	if (codeStart != nullptr)
	{
		std::string cacheIdentifier = this->getHackableIdentifier() + "_" + (hackableCodeInfo.functionName == nullptr ? "" : hackableCodeInfo.functionName->getStringIdentifier());

		if (HackableCode::OriginalCodeCache.find(cacheIdentifier) == HackableCode::OriginalCodeCache.end())
		{
			HackableCode::OriginalCodeCache[cacheIdentifier] = std::vector<unsigned char>();

			for (int index = 0; index < this->originalCodeLength; index++)
			{
				HackableCode::OriginalCodeCache[cacheIdentifier].push_back(((unsigned char*)codeStart)[index]);
			}
		}

		this->originalCodeCopy = HackableCode::OriginalCodeCache[cacheIdentifier];
	}

	this->readOnlyScripts = std::vector<ReadOnlyScript>();

	if (!hackableCodeInfo.excludeDefaultScript)
	{
		std::string script = StrUtils::replaceAll(HackUtils::disassemble(codeStart, this->originalCodeLength), "nop\n", "");

		this->readOnlyScripts.push_back(ReadOnlyScript(
			Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
			ConstantString::create(script),
			ConstantString::create(script)
		));
	}

	for (HackableCode::ReadOnlyScript& script : hackableCodeInfo.readOnlyScripts)
	{
		this->readOnlyScripts.push_back(script);
	}

	if (!this->readOnlyScripts.empty())
	{
		bool is32Bit = sizeof(void*) == 4;
		this->originalAssemblyString = (is32Bit) ? this->readOnlyScripts.front().scriptx86 : this->readOnlyScripts.front().scriptx64;
	}
	
	this->assemblyString = this->originalAssemblyString == nullptr ? "" : this->originalAssemblyString->getString();

	for (HackableCode::ReadOnlyScript& script : this->readOnlyScripts)
	{
		if (script.title != nullptr)
		{
			this->addChild(script.title);
		}

		if (script.scriptx86 != nullptr)
		{
			this->addChild(script.scriptx86);
		}

		if (script.scriptx64 != nullptr)
		{
			this->addChild(script.scriptx64);
		}
	}
}

HackableCode::~HackableCode()
{
}

HackableCode* HackableCode::clone(CodeInfoMap& hackableCodeInfoMap)
{
	HackableCodeInfo clonedData = this->hackableCodeInfo;
	std::vector<RegisterHintInfo> registerHintsClone = std::vector<RegisterHintInfo>();

	clonedData.functionName = this->hackableCodeInfo.functionName->clone();

	for (const RegisterHintInfo& registerHint : this->registerHints)
	{
		registerHintsClone.push_back(registerHint.clone());
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

LocalizedString* HackableCode::getOriginalAssemblyString()
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

	// Remove comments to improve compilation speeds
	std::string simplifiedAssembly = HackableCode::removeComments(this->assemblyString);

	HackUtils::CompileResult compileResult = HackUtils::assemble(simplifiedAssembly, this->codePointer);

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

	HackableEvents::TriggerOnHackApplied(HackAppliedArgs(this));
	this->startTimer();

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

std::string HackableCode::registerToString(HackableCode::Register reg, bool is32Bit)
{
	return HackableCode::registerToLocalizedString(reg, is32Bit)->getString();
}

LocalizedString* HackableCode::registerToLocalizedString(HackableCode::Register reg, bool is32Bit)
{
	switch (reg)
	{
		default:
		case HackableCode::Register::zax:
		{
			return ((is32Bit ? (LocalizedString*)Strings::Menus_Hacking_RegisterEax::create(): (LocalizedString*)Strings::Menus_Hacking_RegisterRax::create()));
		}
		case HackableCode::Register::zbx:
		{
			return ((is32Bit ? (LocalizedString*)Strings::Menus_Hacking_RegisterEbx::create(): (LocalizedString*)Strings::Menus_Hacking_RegisterRbx::create()));
		}
		case HackableCode::Register::zcx:
		{
			return ((is32Bit ? (LocalizedString*)Strings::Menus_Hacking_RegisterEcx::create(): (LocalizedString*)Strings::Menus_Hacking_RegisterRcx::create()));
		}
		case HackableCode::Register::zdx:
		{
			return ((is32Bit ? (LocalizedString*)Strings::Menus_Hacking_RegisterEdx::create(): (LocalizedString*)Strings::Menus_Hacking_RegisterRdx::create()));
		}
		case HackableCode::Register::zdi:
		{
			return ((is32Bit ? (LocalizedString*)Strings::Menus_Hacking_RegisterEdi::create(): (LocalizedString*)Strings::Menus_Hacking_RegisterRdi::create()));
		}
		case HackableCode::Register::zsi:
		{
			return ((is32Bit ? (LocalizedString*)Strings::Menus_Hacking_RegisterEsi::create(): (LocalizedString*)Strings::Menus_Hacking_RegisterRsi::create()));
		}
		case HackableCode::Register::zbp:
		{
			return ((is32Bit ? (LocalizedString*)Strings::Menus_Hacking_RegisterEbp::create(): (LocalizedString*)Strings::Menus_Hacking_RegisterRbp::create()));
		}
		case HackableCode::Register::zsp:
		{
			return ((is32Bit ? (LocalizedString*)Strings::Menus_Hacking_RegisterEsp::create(): (LocalizedString*)Strings::Menus_Hacking_RegisterRsp::create()));
		}
		case HackableCode::Register::zip:
		{
			return ((is32Bit ? (LocalizedString*)Strings::Menus_Hacking_RegisterEip::create(): (LocalizedString*)Strings::Menus_Hacking_RegisterRip::create()));
		}
		case HackableCode::Register::r8:
		{
			return Strings::Menus_Hacking_RegisterR8::create();
		}
		case HackableCode::Register::r9:
		{
			return Strings::Menus_Hacking_RegisterR9::create();
		}
		case HackableCode::Register::r10:
		{
			return Strings::Menus_Hacking_RegisterR10::create();
		}
		case HackableCode::Register::r11:
		{
			return Strings::Menus_Hacking_RegisterR11::create();
		}
		case HackableCode::Register::r12:
		{
			return Strings::Menus_Hacking_RegisterR12::create();
		}
		case HackableCode::Register::r13:
		{
			return Strings::Menus_Hacking_RegisterR13::create();
		}
		case HackableCode::Register::r14:
		{
			return Strings::Menus_Hacking_RegisterR14::create();
		}
		case HackableCode::Register::r15:
		{
			return Strings::Menus_Hacking_RegisterR15::create();
		}
		case HackableCode::Register::st0:
		{
			return Strings::Menus_Hacking_RegisterSt0::create();
		}
		case HackableCode::Register::st1:
		{
			return Strings::Menus_Hacking_RegisterSt1::create();
		}
		case HackableCode::Register::st2:
		{
			return Strings::Menus_Hacking_RegisterSt2::create();
		}
		case HackableCode::Register::st3:
		{
			return Strings::Menus_Hacking_RegisterSt3::create();
		}
		case HackableCode::Register::st4:
		{
			return Strings::Menus_Hacking_RegisterSt4::create();
		}
		case HackableCode::Register::st5:
		{
			return Strings::Menus_Hacking_RegisterSt5::create();
		}
		case HackableCode::Register::st6:
		{
			return Strings::Menus_Hacking_RegisterSt6::create();
		}
		case HackableCode::Register::st7:
		{
			return Strings::Menus_Hacking_RegisterSt7::create();
		}
		case HackableCode::Register::xmm0:
		{
			return Strings::Menus_Hacking_RegisterXmm0::create();
		}
		case HackableCode::Register::xmm1:
		{
			return Strings::Menus_Hacking_RegisterXmm1::create();
		}
		case HackableCode::Register::xmm2:
		{
			return Strings::Menus_Hacking_RegisterXmm2::create();
		}
		case HackableCode::Register::xmm3:
		{
			return Strings::Menus_Hacking_RegisterXmm3::create();
		}
		case HackableCode::Register::xmm4:
		{
			return Strings::Menus_Hacking_RegisterXmm4::create();
		}
		case HackableCode::Register::xmm5:
		{
			return Strings::Menus_Hacking_RegisterXmm5::create();
		}
		case HackableCode::Register::xmm6:
		{
			return Strings::Menus_Hacking_RegisterXmm6::create();
		}
		case HackableCode::Register::xmm7:
		{
			return Strings::Menus_Hacking_RegisterXmm7::create();
		}
	}
}

std::vector<HackableCode*> HackableCode::parseHackables(void* functionStart, CodeInfoMap& hackableCodeInfoMap)
{
	// Parse the HACKABLE_CODE_BEGIN/END pairs from the function. There may be multiple.
	MarkerMap markerMap = HackableCode::parseHackableMarkers(functionStart, hackableCodeInfoMap);
	
	std::vector<HackableCode*> extractedHackableCode = std::vector<HackableCode*>();

	// Bind the code info to each of the BEGIN/END markers to create a HackableCode object.
	for (const auto& marker : markerMap)
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

std::string HackableCode::removeComments(const std::string& code)
{
    std::string result;
    result.reserve(code.size());

    bool inComment = false;
    for (size_t i = 0; i < code.size(); ++i)
	{
        if (!inComment && i + 1 < code.size() && code[i] == '/' && code[i + 1] == '/')
		{
            inComment = true;
            i++; // Skip the second '/'
        }
		else if (inComment && code[i] == '\n')
		{
            inComment = false;
        }
		else if (!inComment)
		{
            result.push_back(code[i]);
        }
    }

    return result;
}
