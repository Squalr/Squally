#pragma once
#include "cocos2d.h"
#include "Objects/Hackables/HackableAttribute.h"
#include "Objects/Hackables/HackableCode.h"

using namespace cocos2d;

class HackableData : public HackableAttribute
{
public:
	static HackableData * create(std::string name, void* dataAddress, const std::type_info* typeInfo, std::string iconResource);

	void registerCode(HackableCode* hackableCode);
	void registerCode(void* startAddress, void* endAddress, std::string functionName, std::string iconResource);

	std::vector<HackableCode*>* codeList;

	std::string variableName;
	void* dataPointer;
	HackUtils::DataType dataType;

private:
	HackableData(std::string name, void* dataAddress, const std::type_info* typeInfo, std::string iconResource);
	~HackableData();

	std::set<void*>* codeTable;
};

