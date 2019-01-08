#pragma once
#include <string>

#include "Engine/SmartNode.h"

class LocalizedString;

class HackableAttribute : public SmartNode
{
public:
	std::string getIconResource();
	LocalizedString* getName();

protected:
	typedef cocos2d::Node super;
	HackableAttribute(std::string iconResource, LocalizedString* name);
	virtual ~HackableAttribute();

private:
	LocalizedString* name;
	std::string iconResource;
};
