#pragma once
#include <set>
#include <string>
#include <typeinfo>
#include <vector>

#include "Engine/Hackables/HackableAttribute.h"
#include "Engine/Utils/HackUtils.h"

class HackableCode;

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
	virtual ~HackableData();

	std::set<void*>* codeTable;
};

