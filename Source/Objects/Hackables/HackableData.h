#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class HackableData : Node
{
public:
	static HackableData * create(void* dataAddress, std::type_info* typeInfo);

private:
	HackableData(void* dataAddress, std::type_info* typeInfo);
	~HackableData();

	void* dataPointer;
	std::type_info* dataType;
};

