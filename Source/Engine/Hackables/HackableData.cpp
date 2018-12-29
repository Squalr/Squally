#include "HackableData.h"

#include "Engine/Hackables/HackableCode.h"

using namespace cocos2d;

HackableData* HackableData::create(std::string name, void* dataAddress, const std::type_info& dataTypeInfo, std::string iconResource)
{
	HackableData* instance = new HackableData(name, dataAddress, dataTypeInfo, iconResource);

	instance->autorelease();

	return instance;
}

HackableData::HackableData(std::string name, void* dataAddress, const std::type_info& dataTypeInfo, std::string iconResource) : HackableAttribute(iconResource)
{
	this->variableName = name;
	this->dataPointer = dataAddress;
	this->dataType = HackUtils::stdTypeToDataType(dataTypeInfo);
}

HackableData::~HackableData()
{
}
