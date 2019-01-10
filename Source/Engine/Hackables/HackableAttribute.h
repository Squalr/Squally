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
	HackableAttribute(std::string iconResource, LocalizedString* name);
	virtual ~HackableAttribute();

private:
	typedef SmartNode super;

	LocalizedString* name;
	std::string iconResource;
};
