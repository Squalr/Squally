#include "HackableData.h"

HackableData * HackableData::create(std::string name, void* dataAddress, const std::type_info* typeInfo, std::string iconBackResource, std::string iconResource)
{

	HackableData* hackableData = new HackableData(name, dataAddress, typeInfo, iconBackResource, iconResource);

	hackableData->autorelease();

	return hackableData;
}

HackableData::HackableData(std::string name, void* dataAddress, const std::type_info* typeInfo, std::string iconBackResource, std::string iconResource) : HackableAttribute(iconBackResource, iconResource)
{
	this->variableName = name;
	this->dataPointer = dataAddress;
	this->dataType = HackUtils::stdTypeToDataType(typeInfo);
}

HackableData::~HackableData()
{
}
