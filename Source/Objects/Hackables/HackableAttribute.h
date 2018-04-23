#pragma once
#include "cocos2d.h"
#include "Utils/HackUtils.h"

using namespace cocos2d;

class HackableAttribute : public Node
{
public:
	std::string iconResource;

protected:
	HackableAttribute(std::string iconResource);
	~HackableAttribute();
};

