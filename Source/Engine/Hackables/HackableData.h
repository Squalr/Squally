#pragma once
#include <string>

#include "Engine/Hackables/HackableAttribute.h"
#include "Engine/Utils/HackUtils.h"

class HackableCode;
class LocalizedString;

class HackableData : public HackableAttribute
{
public:
	static HackableData* create(void* dataAddress, int hackFlags, float duration, LocalizedString* variableName, const std::type_info& dataTypeInfo, std::string iconResource, HackablePreview* hackablePreview);

	void* getPointer() override;

protected:
	HackableData(void* dataAddress, int hackFlags,  float duration, LocalizedString* variableName, const std::type_info& dataTypeInfo, std::string iconResource, HackablePreview* hackablePreview);
	virtual ~HackableData();

	void restoreState() override;

private:
	typedef HackableAttribute super;

	void* dataPointer;
	HackUtils::DataType dataType;
};
