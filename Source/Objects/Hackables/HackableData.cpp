#include "HackableData.h"

HackableData * HackableData::create(void* dataAddress, std::type_info* typeInfo)
{

	HackableData* hackableData = new HackableData(dataAddress, typeInfo);

	hackableData->autorelease();

	return hackableData;
}

HackableData::HackableData(void* dataAddress, std::type_info* typeInfo)
{
	this->dataPointer = dataAddress;
	this->dataType = typeInfo;
}

HackableData::~HackableData()
{
	delete(this->dataType);
}
