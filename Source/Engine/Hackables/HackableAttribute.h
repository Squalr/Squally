#pragma once
#include <string>

#include "cocos/2d/CCNode.h"

class HackableAttribute : public cocos2d::Node
{
public:
	std::string iconResource;

protected:
	HackableAttribute(std::string iconResource);
	virtual ~HackableAttribute();
};
