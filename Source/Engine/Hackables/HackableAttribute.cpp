#include "HackableAttribute.h"

#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Localization/LocalizedString.h"

HackableAttribute::HackableAttribute(std::string iconResource, LocalizedString* name, HackablePreview* hackablePreview)
{
	this->iconResource = iconResource;
	this->name = name;
	this->hackablePreview = hackablePreview;

	if (this->hackablePreview != nullptr)
	{
		this->hackablePreview->retain();
	}

	this->addChild(name); // Retain with event listening
}

HackableAttribute::~HackableAttribute()
{
	this->hackablePreview->release();
}

std::string HackableAttribute::getIconResource()
{
	return this->iconResource;
}

LocalizedString* HackableAttribute::getName()
{
	return this->name;
}

HackablePreview* HackableAttribute::getHackablePreview()
{
	return this->hackablePreview;
}
