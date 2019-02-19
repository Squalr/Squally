#pragma once
#include <string>

#include "Engine/Hackables/HackableAttribute.h"
#include "Engine/Utils/HackUtils.h"

class HackableCode;
class LocalizedString;

class HackableData : public HackableAttribute
{
public:
	static HackableData* create(void* dataAddress, float duration, LocalizedString* variableName, const std::type_info& dataTypeInfo, std::string iconResource, HackablePreview* hackablePreview);

	void* getPointer() override;

protected:
	void restoreState() override;

private:
	typedef HackableAttribute super;
	HackableData(void* dataAddress, float duration, LocalizedString* variableName, const std::type_info& dataTypeInfo, std::string iconResource, HackablePreview* hackablePreview);
	virtual ~HackableData();

	void* dataPointer;
	HackUtils::DataType dataType;
};
