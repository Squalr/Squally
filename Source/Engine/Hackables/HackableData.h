#pragma once
#include <string>

#include "Engine/Hackables/HackableAttribute.h"
#include "Engine/Utils/HackUtils.h"

class HackableCode;

class HackableData : public HackableAttribute
{
public:
	static HackableData* create(std::string name, void* dataAddress, const std::type_info* typeInfo, std::string iconResource);

	std::string variableName;
	void* dataPointer;
	HackUtils::DataType dataType;

private:
	HackableData(std::string name, void* dataAddress, const std::type_info* typeInfo, std::string iconResource);
	virtual ~HackableData();
};
