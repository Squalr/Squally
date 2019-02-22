#include "Item.h"

#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"

using namespace cocos2d;

Item::Item(LocalizedString* name, std::string iconResource)
{
	this->name = name;
	this->iconResource = iconResource;

	if (this->name != nullptr)
	{
		this->addChild(this->name);
	}
}

Item::~Item()
{
}

void Item::onEnter()
{
	super::onEnter();
}

void Item::initializeListeners()
{
	super::initializeListeners();
}

cocos2d::ValueMap Item::serialize()
{
	ValueMap result = ValueMap();

	return result;
}

LocalizedString* Item::cloneName()
{
	return this->name == nullptr ? nullptr : this->name->clone();
}

std::string Item::getIconResource()
{
	return this->iconResource;
}