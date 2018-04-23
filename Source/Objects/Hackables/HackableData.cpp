#include "HackableData.h"

HackableData * HackableData::create(std::string name, void* dataAddress, const std::type_info* typeInfo, std::string iconResource)
{

	HackableData* hackableData = new HackableData(name, dataAddress, typeInfo, iconResource);

	hackableData->autorelease();

	return hackableData;
}

HackableData::HackableData(std::string name, void* dataAddress, const std::type_info* typeInfo, std::string iconResource) : HackableAttribute(iconResource)
{
	this->variableName = name;
	this->dataPointer = dataAddress;
	this->dataType = HackUtils::stdTypeToDataType(typeInfo);

	this->codeList = new std::vector<HackableCode*>();
	this->codeTable = new std::set<void*>();
}

HackableData::~HackableData()
{
	delete(this->codeList);
	delete(this->codeTable);
}

void HackableData::registerCode(HackableCode* hackableCode)
{
	// Check if already registered
	if (this->codeTable->find(hackableCode->codePointer) != this->codeTable->end())
	{
		return;
	}

	hackableCode->retain();
	this->codeList->push_back(hackableCode);
	this->codeTable->insert(hackableCode->codePointer);
}

void HackableData::registerCode(void* startAddress, void* endAddress, std::string functionName, std::string iconResource)
{
	// Check if already registered
	if (this->codeTable->find(startAddress) != this->codeTable->end())
	{
		return;
	}

	HackableCode* hackableCode = HackableCode::create(functionName, startAddress, (unsigned int)endAddress - (unsigned int)startAddress, iconResource);
	hackableCode->retain();
	this->codeList->push_back(hackableCode);
	this->codeTable->insert(startAddress);
}
