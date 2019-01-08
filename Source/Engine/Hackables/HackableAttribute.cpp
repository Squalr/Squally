#include "HackableAttribute.h"

#include "Engine/Localization/LocalizedString.h"

HackableAttribute::HackableAttribute(std::string iconResource, LocalizedString* name)
{
	this->iconResource = iconResource;
	this->name = name;

	this->addChild(name); // Retain with event listening
}

HackableAttribute::~HackableAttribute()
{
}


std::string HackableAttribute::getIconResource()
{
	return this->iconResource;
}

LocalizedString* HackableAttribute::getName()
{
	return this->name->clone();
}
