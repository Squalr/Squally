#include "HackableData.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Localization/LocalizedString.h"

using namespace cocos2d;

HackableData* HackableData::create(void* dataAddress, int hackFlags, float duration, LocalizedString* variableName, const std::type_info& dataTypeInfo, std::string iconResource, HackablePreview* hackablePreview)
{
	HackableData* instance = new HackableData(dataAddress, hackFlags, duration, variableName, dataTypeInfo, iconResource, hackablePreview);

	instance->autorelease();

	return instance;
}

HackableData::HackableData(void* dataAddress, int hackFlags, float duration, LocalizedString* variableName, const std::type_info& dataTypeInfo, std::string iconResource, HackablePreview* hackablePreview) : HackableAttribute(hackFlags, duration, 0.0f, iconResource, variableName, hackablePreview)
{
	this->dataPointer = dataAddress;
	this->dataType = HackUtils::stdTypeToDataType(dataTypeInfo);
}

HackableData::~HackableData()
{
}

void* HackableData::getPointer()
{
	return this->dataPointer;
}

void HackableData::restoreState()
{
}
