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

void HackableData::registerCode(void* startAddress, void* endAddress, std::string functionName, std::string iconBackResource, std::string iconResource)
{
	// Check if already registered
	if (this->codeTable->find(startAddress) != this->codeTable->end())
	{
		return;
	}

	HackableCode* hackableCode = HackableCode::create(functionName, startAddress, (unsigned int)endAddress - (unsigned int)startAddress, iconBackResource, iconResource);
	hackableCode->retain();
	this->codeList->push_back(hackableCode);
	this->codeTable->insert(startAddress);
}
