#pragma once
#include <string>

#include "Engine/Hackables/HackableAttribute.h"
#include "Engine/Utils/HackUtils.h"

class HackableCode;
class LocalizedString;

class HackableData : public HackableAttribute
{
public:
	static HackableData* create(void* dataAddress, LocalizedString* variableName, const std::type_info& dataTypeInfo, std::string iconResource);

	LocalizedString* variableName;
	void* dataPointer;
	HackUtils::DataType dataType;

private:
	HackableData(void* dataAddress, LocalizedString* variableName, const std::type_info& dataTypeInfo, std::string iconResource);
	virtual ~HackableData();
};
