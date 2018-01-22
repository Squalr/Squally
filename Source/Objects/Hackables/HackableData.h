#pragma once
#include "cocos2d.h"
#include "Objects/Hackables/HackableAttribute.h"

using namespace cocos2d;

class HackableData : HackableAttribute
{
public:
	static HackableData * create(void* dataAddress, std::type_info* typeInfo);

private:
	HackableData(void* dataAddress, std::type_info* typeInfo);
	~HackableData();

	void* dataPointer;
	std::type_info* dataType;
};

