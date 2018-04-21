#pragma once
#include "cocos2d.h"
#include "Objects/Hackables/HackableAttribute.h"

using namespace cocos2d;

class HackableData : public HackableAttribute
{
public:
	static HackableData * create(std::string name, void* dataAddress, const std::type_info* typeInfo, std::string iconBackResource, std::string iconResource);

	std::string variableName;
	void* dataPointer;
	HackUtils::DataType dataType;

private:
	HackableData(std::string name, void* dataAddress, const std::type_info* typeInfo, std::string iconBackResource, std::string iconResource);
	~HackableData();
};

