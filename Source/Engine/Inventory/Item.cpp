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
	return ValueMap();
}

void Item::deserialize(ValueMap& valueMap)
{
}

LocalizedString* Item::cloneName()
{
	return this->name == nullptr ? nullptr : this->name->clone();
}

std::string Item::getIconResource()
{
	return this->iconResource;
}