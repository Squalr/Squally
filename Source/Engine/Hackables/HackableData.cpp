#include "HackableData.h"

#include "Engine/Hackables/HackableCode.h"

using namespace cocos2d;

HackableData* HackableData::create(std::string name, void* dataAddress, const std::type_info* typeInfo, std::string iconResource)
{
	HackableData* instance = new HackableData(name, dataAddress, typeInfo, iconResource);

	instance->autorelease();

	return instance;
}

HackableData::HackableData(std::string name, void* dataAddress, const std::type_info* typeInfo, std::string iconResource) : HackableAttribute(iconResource)
{
	this->variableName = name;
	this->dataPointer = dataAddress;
	this->dataType = HackUtils::stdTypeToDataType(typeInfo);

	this->codeList = std::vector<HackableCode*>();
	this->codeTable = std::set<void*>();
}

HackableData::~HackableData()
{
}

void HackableData::registerCode(HackableCode* hackableCode)
{
	// Check if already registered
	if (this->codeTable.find(hackableCode->getCodePointer()) != this->codeTable.end())
	{
		return;
	}

	hackableCode->retain();
	this->codeList.push_back(hackableCode);
	this->codeTable.insert(hackableCode->getCodePointer());
}
