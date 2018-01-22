#include "HackableData.h"

HackableData * HackableData::create(std::string name, void* dataAddress, const std::type_info* typeInfo)
{

	HackableData* hackableData = new HackableData(name, dataAddress, typeInfo);

	hackableData->autorelease();

	return hackableData;
}

HackableData::HackableData(std::string name, void* dataAddress, const std::type_info* typeInfo)
{
	this->variableName = name;
	this->dataPointer = dataAddress;
	this->dataType = typeInfo;
}

HackableData::~HackableData()
{
	delete(this->dataType);
}
